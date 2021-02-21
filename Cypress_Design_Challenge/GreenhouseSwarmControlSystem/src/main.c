#include "wiced_bt_ble.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_mesh_models.h"
#include "wiced_bt_trace.h"
#include "wiced_bt_mesh_app.h"

#include "wiced_bt_cfg.h"

#ifdef HCI_CONTROL
#include "wiced_transport.h"
#include "hci_control_api.h"
#endif

#include "led_control.h"
#include "wiced_platform.h"

#define MAIN_TIMER_MS 2000

#define MESH_DEFAULT_LEVEL_MAX      0x7FFF
#define MESH_DEFAULT_LEVEL_MIN      0x8000

/******************************************************
 *          Constants
 ******************************************************/
#define MESH_PID                0x3006
#define MESH_VID                0x0002
#define MESH_FWID               0x3006000101010001
#define MESH_CACHE_REPLAY_SIZE  0x0008

// This sample shows simple use of vendor data messages.  Vendor model
// can define any opcodes it wants.
#define MESH_VENDOR_OPCODE1             1
#define MESH_VENDOR_OPCODE2             2

#define MESH_VENDOR_COMPANY_ID          0x131   // Cypress Company ID
#define MESH_VENDOR_MODEL_ID            1       // ToDo.  This need to be modified

/******************************************************
 *          Variables Definitions
 ******************************************************/
uint8_t mesh_mfr_name[WICED_BT_MESH_PROPERTY_LEN_DEVICE_MANUFACTURER_NAME] = { 'C', 'y', 'p', 'r', 'e', 's', 's', 0 };
uint8_t mesh_model_num[WICED_BT_MESH_PROPERTY_LEN_DEVICE_MODEL_NUMBER]     = { '1', '2', '3', '4', 0, 0, 0, 0 };
uint8_t mesh_system_id[8]                                                  = { 0xbb, 0xb8, 0xa1, 0x80, 0x5f, 0x9f, 0x91, 0x71 };

/******************************************************
 *          Function Prototypes
 ******************************************************/

static void main_initilise(wiced_bool_t is_provisioned);
static void main_timer_handler(TIMER_PARAM_TYPE arg);
static void mesh_vendor_server_send_data(wiced_bt_mesh_event_t *p_event, uint16_t opcode, uint8_t *p_data, uint16_t data_len);
wiced_bool_t josh_mesh_server_message_handler(wiced_bt_mesh_event_t *p_event, uint8_t *p_data, uint16_t data_len);

/******************************************************
 *          Global Variable Declarations
 ******************************************************/

int testing_variable = 0; // Use this as a simple testing variable
extern wiced_bt_cfg_settings_t wiced_bt_cfg_settings;
wiced_timer_t main_timer; // dispatch timer that controls the main functions of the device periodically.

/******************************************************
 *          BT Core Configuration
 ******************************************************/

wiced_bt_mesh_core_config_model_t   mesh_element1_models[] =
{
    WICED_BT_MESH_DEVICE,
	{ MESH_VENDOR_COMPANY_ID, MESH_VENDOR_MODEL_ID, josh_mesh_server_message_handler, NULL, NULL },
};

#define MESH_APP_NUM_MODELS  (sizeof(mesh_element1_models) / sizeof(wiced_bt_mesh_core_config_model_t))

#define MESH_LEVEL_SERVER_ELEMENT_INDEX   0

wiced_bt_mesh_core_config_element_t mesh_elements[] =
{
    {
        .location = MESH_ELEM_LOC_MAIN,                                 // location description as defined in the GATT Bluetooth Namespace Descriptors section of the Bluetooth SIG Assigned Numbers
        .default_transition_time = MESH_DEFAULT_TRANSITION_TIME_IN_MS,  // Default transition time for models of the element in milliseconds
        .onpowerup_state = WICED_BT_MESH_ON_POWER_UP_STATE_RESTORE,     // Default element behavior on power up
        .default_level = 0,                                             // Default value of the variable controlled on this element (for example power, lightness, temperature, hue...)
        .range_min = 1,                                                 // Minimum value of the variable controlled on this element (for example power, lightness, temperature, hue...)
        .range_max = 0xffff,                                            // Maximum value of the variable controlled on this element (for example power, lightness, temperature, hue...)
        .move_rollover = 0,                                             // If true when level gets to range_max during move operation, it switches to min, otherwise move stops.
        .properties_num = 0,                                            // Number of properties in the array models
        .properties = NULL,                                             // Array of properties in the element.
        .sensors_num = 0,                                               // Number of sensors in the sensor array
        .sensors = NULL,                                                // Array of sensors of that element
        .models_num = MESH_APP_NUM_MODELS,                              // Number of models in the array models
        .models = mesh_element1_models,                                 // Array of models located in that element. Model data is defined by structure wiced_bt_mesh_core_config_model_t
    },
};

wiced_bt_mesh_core_config_t  mesh_config =
{
    .company_id         = MESH_COMPANY_ID_CYPRESS,                  // Company identifier assigned by the Bluetooth SIG
    .product_id         = MESH_PID,                                 // Vendor-assigned product identifier
    .vendor_id          = MESH_VID,                                 // Vendor-assigned product version identifier
    .firmware_id        = MESH_FWID,                                // Vendor-assigned firmware version identifier
    .replay_cache_size  = MESH_CACHE_REPLAY_SIZE,                   // Number of replay protection entries, i.e. maximum number of mesh devices that can send application messages to this device.
#if defined(LOW_POWER_NODE) && (LOW_POWER_NODE == 1)
    .features           = WICED_BT_MESH_CORE_FEATURE_BIT_LOW_POWER, // A bit field indicating the device features. In Low Power mode no Relay, no Proxy and no Friend
    .friend_cfg         =                                           // Empty Configuration of the Friend Feature
    {
        .receive_window = 0,                                        // Receive Window value in milliseconds supported by the Friend node.
        .cache_buf_len  = 0,                                        // Length of the buffer for the cache
        .max_lpn_num    = 0                                         // Max number of Low Power Nodes with established friendship. Must be > 0 if Friend feature is supported.
    },
    .low_power          =                                           // Configuration of the Low Power Feature
    {
        .rssi_factor           = 2,                                 // contribution of the RSSI measured by the Friend node used in Friend Offer Delay calculations.
        .receive_window_factor = 2,                                 // contribution of the supported Receive Window used in Friend Offer Delay calculations.
        .min_cache_size_log    = 3,                                 // minimum number of messages that the Friend node can store in its Friend Cache.
        .receive_delay         = 100,                               // Receive delay in 1 ms units to be requested by the Low Power node.
        .poll_timeout          = 36000                              // Poll timeout in 100ms units to be requested by the Low Power node.
    },
#else
    .features = WICED_BT_MESH_CORE_FEATURE_BIT_FRIEND | WICED_BT_MESH_CORE_FEATURE_BIT_RELAY | WICED_BT_MESH_CORE_FEATURE_BIT_GATT_PROXY_SERVER,   // Supports Friend, Relay and GATT Proxy
    .friend_cfg         =                                           // Configuration of the Friend Feature(Receive Window in Ms, messages cache)
    {
        .receive_window        = 200,
        .cache_buf_len         = 300,                               // Length of the buffer for the cache
        .max_lpn_num           = 4                                  // Max number of Low Power Nodes with established friendship. Must be > 0 if Friend feature is supported.
    },
    .low_power          =                                           // Configuration of the Low Power Feature
    {
        .rssi_factor           = 0,                                 // contribution of the RSSI measured by the Friend node used in Friend Offer Delay calculations.
        .receive_window_factor = 0,                                 // contribution of the supported Receive Window used in Friend Offer Delay calculations.
        .min_cache_size_log    = 0,                                 // minimum number of messages that the Friend node can store in its Friend Cache.
        .receive_delay         = 0,                                 // Receive delay in 1 ms units to be requested by the Low Power node.
        .poll_timeout          = 0                                  // Poll timeout in 100ms units to be requested by the Low Power node.
    },
#endif
    .gatt_client_only          = WICED_FALSE,                       // Can connect to mesh over GATT or ADV
    .elements_num  = (uint8_t)(sizeof(mesh_elements) / sizeof(mesh_elements[0])),   // number of elements on this device
    .elements      = mesh_elements                                  // Array of elements for this device
};


/******************************************************
 *          Debug Setup
 ******************************************************/
// https://community.cypress.com/message/204572#204572
// debugging functions do not work for me so I use a putty terminal instead.

const wiced_transport_cfg_t transport_cfg =
{
		.type = WICED_TRANSPORT_UART,
#ifdef HCI_UART_BAUDRATE
		.cfg.uart_cfg = {.mode = WICED_TRANSPORT_UART_HCI_MODE, . baud_rate = HCI_UART_BAUDRATE},
#else
		.cfg.uart_cfg = {.mode = WICED_TRANSPORT_UART_HCI_MODE, . baud_rate = 115200},
#endif
		.rx_buff_pool_cfg = {.buffer_size = 1024, .buffer_count = 2},
		.p_status_handler = NULL,
		.p_data_handler = NULL,//mesh_application_proc_rx_cmd,
		.p_tx_complete_cback = NULL
};

//
//
//

/******************************************************
 *          Main Functions
 ******************************************************/

// README
// This is the main code file for my implementation of a decentralised swarm style control system
// using the Cypress Semiconductor WICED Bluetooth Mesh API.

// The aim of this project was to make use of the on-board sensors of the CYBT-213043-MESH to create a
// mesh network of interacting data nodes with no central controller. To do this I have used the vendor
// specific server models and attempted to define my own messages to send sensor data out on the provisioned network.

// As part of this goal I wanted to have extended access to the message and event data in order to create my own
// data structures and messages while being able to cache historic data from each node address on the network.

// I have spend at least six weeks pursuing this and in my experience I found the Bluetooth Mesh protocol
// and the Cypress WICED framework to be restricting beyond the rigid model definitions. I am currently using the
// vendor specific models which gives a bit more freedom but while attempting to define my own messages,
// I could not gain clean access to the arguments I required to run the messaging functions from the backend
// and was not able to continue.

// See *wiced_bt_mesh_create_event(), I cannot find a local reference to the app key argument anywhere?


wiced_bt_mesh_app_func_table_t wiced_bt_mesh_app_func_table =
{
	main_initilise,         // application initialisation
    NULL,                   // Default SDK platform button processing
    NULL,                   // GATT connection status
    NULL,                   // attention processing
    NULL,                   // notify period set
    NULL,   				// WICED HCI command
    NULL,                   // LPN sleep
    NULL                    // factory reset
};

void main_initilise(wiced_bool_t is_provisioned)
{
	// putty debug setup
	wiced_transport_init(&transport_cfg);
	wiced_set_debug_uart(WICED_ROUTE_DEBUG_TO_WICED_UART);
	WICED_BT_TRACE("Test \r\n");

	// mesh setup
	wiced_bt_cfg_settings.device_name = (uint8_t *)"Swarm_Node"; // Swarm_Node
    wiced_bt_cfg_settings.gatt_cfg.appearance = APPEARANCE_GENERIC_TAG;

    if (!is_provisioned)
    {
        wiced_bt_ble_advert_elem_t  adv_elem[3];
        uint8_t                     buf[2];
        uint8_t                     num_elem = 0;
        adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_NAME_COMPLETE;
        adv_elem[num_elem].len = (uint16_t)strlen((const char*)wiced_bt_cfg_settings.device_name);
        adv_elem[num_elem].p_data = wiced_bt_cfg_settings.device_name;
        num_elem++;

        adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_APPEARANCE;
        adv_elem[num_elem].len = 2;
        buf[0] = (uint8_t)wiced_bt_cfg_settings.gatt_cfg.appearance;
        buf[1] = (uint8_t)(wiced_bt_cfg_settings.gatt_cfg.appearance >> 8);
        adv_elem[num_elem].p_data = buf;
        num_elem++;

        wiced_bt_mesh_set_raw_scan_response_data(num_elem, adv_elem);
        return; // if its not provisioned don't start main code
    }

    // setup LED for output and debugging
    led_control_init(LED_CONTROL_TYPE_ONOFF);
    // set LED to on when provisioned
    led_control_set_onoff(1);

    // initialise timer
    wiced_init_timer(&main_timer, main_timer_handler, 0, WICED_MILLI_SECONDS_TIMER);
    // start periodic message timer
    wiced_start_timer(&main_timer, MAIN_TIMER_MS); // start timer (ms)
}

// https://www.bluetooth.com/bluetooth-technology/topology-options/le-mesh/mesh-glossary/
// good overview
// https://www.bluetooth.com/blog/the-fundamental-concepts-of-bluetooth-mesh-networking-part-2/
// gives group addresses

// initialise app key
uint16_t capturedappkey = 0xffff;
// define message data
uint8_t josh_data[1];

void main_timer_handler(TIMER_PARAM_TYPE arg)
{
	// define update message to be send periodically on the network.
	wiced_bt_mesh_event_t JoshEvent =  *wiced_bt_mesh_create_event(0 /* element index */, MESH_VENDOR_COMPANY_ID, MESH_VENDOR_MODEL_ID, 0xFFFF /* dst send to all nodes */, capturedappkey /* app key idx*/);
    
    //
    // I CANNOT FIND A LOCAL REFERENCE TO THE PROVISIONED APP KEY ANYWHERE? 
    // I CAN ONLY FIND IT THROUGH RECEIVED CLIENT AND PROVISIONER MESSAGES.
    //

	// for ease of debug this message toggles between 1 and 0
	if(josh_data[0] == 0)
	{
		josh_data[0] = 1;
	}
	else
	{
		josh_data[0] = 0;
	}

	// define data length
	uint16_t josh_data_len = 1;

	// use subroutine to send data and message.
	mesh_vendor_server_send_data(&JoshEvent, MESH_VENDOR_OPCODE2, josh_data, josh_data_len);

	// restart the WICED timer.
	wiced_start_timer(&main_timer, MAIN_TIMER_MS); // restart timer (ms)
}

/*
* Send Vendor Data status message to the Client
*/
void mesh_vendor_server_send_data(wiced_bt_mesh_event_t *p_event, uint16_t opcode, uint8_t *p_data, uint16_t data_len)
{
	// update default opcode for vendor specific code
	p_event->opcode = opcode;
	// use parameters to send data on the network
	wiced_result_t debugtx = wiced_bt_mesh_core_send(p_event, p_data, data_len, NULL);

	// I am able to see messages sent using the Android provisioner app but only for a short time
	// but I do not receive these messages on other nodes running the same program.
}

wiced_bool_t josh_mesh_server_message_handler(wiced_bt_mesh_event_t *p_event, uint8_t *p_data, uint16_t data_len)
{
	WICED_BT_TRACE("Message handler triggered \r\n");

	// Filter any reflected messages
    if (p_event->src == wiced_bt_mesh_core_get_local_addr())
    {
    	return WICED_TRUE;
    }
    // Filter for messages directed at this node address
    if (p_event->dst == wiced_bt_mesh_core_get_local_addr())
    {
    	WICED_BT_TRACE("Message received \r\n");
    	// update app key from initial provisioner message
    	capturedappkey = p_event->app_key_idx;
    	WICED_BT_TRACE("Message app key: %d \r\n", p_event->app_key_idx);
    	// show message was received by toggling the LED, extended led_control.h file
    	led_control_toggle_onoff();
    	// delay for ease of debugging series of messages with the LED.
    	wiced_rtos_delay_milliseconds(1000);
    }

    return WICED_TRUE;
}

