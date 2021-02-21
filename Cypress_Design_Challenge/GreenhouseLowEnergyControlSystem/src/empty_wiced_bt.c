// README
//
// This is the Bluetooth Low Energy version of my greenhouse control system.
//
// The project is based on the empty template provided for the CYW920819EVB-02 development kit
// which extends the default GATT profile with two additional services to read and write values on the Bluetooth device.
//
// Service one is a read-only service that shows real-time data from the sensors of the control system.
//
// Service two is a read and write service that allows users to set opperating parameters for the greenhouse control system to work towards.
// 
// My intent with this project was to use all the available IO provided by the Arduino headers to connect a range of sensors
// that give a reliable indication of greenhouse opperating conditions to the user. These values will also be used to automatically regulate the
// ventalation and irrigation within the greenhouse and maintain appropriate growing conditions for the plants inside.
//
// I recommend the devs build this sample code with all the snippets uncomented in order to fix any errors.

#include "app_bt_cfg.h"
#include "sparcommon.h"
#include "wiced_bt_dev.h"
#include "wiced_platform.h"
#include "wiced_bt_trace.h"
#include "wiced_hal_puart.h"
#include "wiced_bt_stack.h"
#include "GeneratedSource/cycfg_gatt_db.h"

/*******************************************************************
 * Function Prototypes
 ******************************************************************/
static wiced_bt_dev_status_t  app_bt_management_callback    ( wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data );
wiced_result_t app_set_advertisement_data(void);
wiced_bt_gatt_status_t app_gatt_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data );

/*******************************************************************
 * Main Code
 ******************************************************************/

void application_start(void)
{
    /* Select Debug UART setting to see debug traces on the appropriate port */
    wiced_set_debug_uart(  WICED_ROUTE_DEBUG_TO_PUART );

    WICED_BT_TRACE("**** App Start **** \n\r");

    /* Initialize Stack and Register Management Callback */
    wiced_bt_stack_init(app_bt_management_callback, &wiced_bt_cfg_settings, wiced_bt_cfg_buf_pools);
}

/* Bluetooth Management Event Handler */
wiced_result_t app_bt_management_callback( wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data )
{
    wiced_result_t status = WICED_BT_SUCCESS;
    wiced_bt_gatt_status_t gatt_status;

    switch (event)
    {
    case BTM_ENABLED_EVT:
        /* Bluetooth Controller and Host Stack Enabled */
        WICED_BT_TRACE("Bluetooth Enabled (%s)\n",
                ((WICED_BT_SUCCESS == p_event_data->enabled.status) ? "success" : "failure"));

        /* register for GATT callbacks if needed by your application */
        gatt_status = wiced_bt_gatt_register( app_gatt_callback );


        /* initialize GATT database created by Bluetooth Configurator here if needed by your application */
        gatt_status = wiced_bt_gatt_db_init(gatt_database, gatt_database_len);
        // WICED_BT_TRACE("GATT status:d\n", gatt_status);

        /* set advertisement data for your app */
        app_set_advertisement_data();

        /* start advertisement */
        // 	THIS FUNCTION NEEDED FIXING
        wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, BLE_ADDR_PUBLIC, NULL);

        break;

    // TODO - Handle Bluetooth Management Event
    case BTM_PAIRING_IO_CAPABILITIES_BLE_REQUEST_EVT: // IO capabilities request
         break;

     case BTM_PAIRING_COMPLETE_EVT: // Pairing Complete event
         break;

     case BTM_ENCRYPTION_STATUS_EVT: // Encryption Status Event
         break;

     case BTM_SECURITY_REQUEST_EVT: // security accesss
         break;

     case BTM_PAIRED_DEVICE_LINK_KEYS_UPDATE_EVT: // save link keys with app
         break;

      case  BTM_PAIRED_DEVICE_LINK_KEYS_REQUEST_EVT: // retrieval saved link keys
         break;

     case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT: // save keys to NVRAM
         break;

     case  BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT: // read keys from NVRAM
         break;

     case BTM_BLE_SCAN_STATE_CHANGED_EVT: // Scan State Change
         break;


    default:
        WICED_BT_TRACE("Unhandled Bluetooth Management Event: 0x%x (%d)\n", event, event);
        break;
    }

    return status;
}

// Set advertisement data for your application
wiced_result_t app_set_advertisement_data(void)
{

    wiced_bt_ble_advert_elem_t  adv_elem[3];
    wiced_result_t              result;
    uint8_t         num_elem                = 0;
    uint8_t         flag                    = BTM_BLE_GENERAL_DISCOVERABLE_FLAG | BTM_BLE_BREDR_NOT_SUPPORTED;


    adv_elem[num_elem].advert_type          = BTM_BLE_ADVERT_TYPE_FLAG;
    adv_elem[num_elem].len                  = sizeof(uint8_t);
    adv_elem[num_elem].p_data               = &flag;
    num_elem++;

    adv_elem[num_elem].advert_type          = BTM_BLE_ADVERT_TYPE_NAME_COMPLETE;
    adv_elem[num_elem].len                  = strlen((const char *) wiced_bt_cfg_settings.device_name);
    adv_elem[num_elem].p_data               = (uint8_t *) wiced_bt_cfg_settings.device_name;
    num_elem++;

    result = wiced_bt_ble_set_raw_advertisement_data(num_elem, adv_elem);

    return result;
}

// Handle GATT event callbacks if needed by your app.
wiced_bt_gatt_status_t app_gatt_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data )
{
	// 	THIS FUNCTION NEEDED FIXING
	WICED_BT_TRACE("GATT callback\r\n");
    // Set default GATT status.
    wiced_bt_gatt_status_t status = WICED_BT_GATT_SUCCESS;
    // Get GATT callback attribute.
    wiced_bt_gatt_attribute_request_t *p_attr_req = &p_data->attribute_request;
    // Get connection status.
    wiced_bt_gatt_connection_status_t *p_conn_status = &p_data->connection_status;

    switch( event )
    {
        case GATT_CONNECTION_STATUS_EVT:
        {
        	WICED_BT_TRACE("GATT Connection Event\r\n");
            if (p_conn_status->connected) 
            {
                // Device has connected.
            }
            else 
            {
                // Device has disconnected.
            }
        }
            break;

        case GATT_ATTRIBUTE_REQUEST_EVT:
        {
        	WICED_BT_TRACE("GATT Attribute Request Event\r\n");
            switch (p_attr_req->request_type)
            {
            case GATTS_REQ_TYPE_READ: // read request
                    // This will used to read the current greenhouse climate conditions using the environmnetal sensors connected to the BLE device.
                    // Get using the first Bluetooth GATT service.
                    // If this was was a read-only service a Bluetooth beacon could also be used. 

            	////////////////////////////////////////////////////////////////////////////////////

                // Debug traces using putty.
            	WICED_BT_TRACE("Read Event\r\n");
                // Show requested handle from connected device.
            	WICED_BT_TRACE("Handle %d \r\n", p_data->attribute_request.data.handle); 
                    
                // If the read request is equal to the greenhouse temperature GATT characteristic value.
            	if (p_data->attribute_request.data.handle == HDLC_GREENHOUSE_VALUES_VALUE_TEMPERATURE_VALUE)
            	{
                    // Trace to show if temperature was selected for reading.
            		WICED_BT_TRACE("Temperature Read Request Received");
                    // Get temperature value pointer.
					uint8_t *p_attr = (uint8_t *)app_greenhouse_values_value_temperature;
                    // Send Notification to connected Android app via BT stack and show latest temperature value.
                    // Trace shows GATT Status of message to be sent.
					WICED_BT_TRACE("GATT status: %d \r\n", wiced_bt_gatt_send_notification( p_data->connection_status.conn_id, HDLC_GREENHOUSE_VALUES_VALUE_TEMPERATURE, app_greenhouse_values_value_temperature_len, p_attr ));
					//
					// ERROR 255: Value Out of Range.
                    // The debug wasn't working so I couldn't figure out what was in error here.
                    // I ran out of time trying to fix it.
                    //
            	}
               break;

               ////////////////////////////////////////////////////////////////////////////////////

            case GATTS_REQ_TYPE_WRITE: // write request
            	WICED_BT_TRACE("Write Event\r\n");
                    // This will be used to set target values for the greenhouse control system to work towards.
                    // Set using the second Bluetooth GATT service.
               break;

            case GATTS_REQ_TYPE_CONF: // confirm request
            	WICED_BT_TRACE("Confirm Event\r\n");
               break;
            }
        }
            break;

        default:
        	WICED_BT_TRACE("GATT Default Event\r\n");
            break;
    }

    return status;
}
