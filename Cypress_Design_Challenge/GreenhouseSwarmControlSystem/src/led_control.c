
#include "sparcommon.h"

#include "wiced_hal_pwm.h"
#include "wiced_hal_gpio.h"
#include "wiced_hal_aclk.h"
#include "wiced_bt_trace.h"
#include "wiced_platform.h"
#include "led_control.h"

/******************************************************************************
 *                                Constants
 ******************************************************************************/
#define PWM_CHANNEL         PWM0

#define PWM_INP_CLK_IN_HZ   (512*1000)
#define PWM_FREQ_IN_HZ      (10000)

/******************************************************************************
 *                          Function Declarations
 ******************************************************************************/

/******************************************************************************
 *                                Variables Definitions
 ******************************************************************************/
#if ( !defined(CYW20719B1) && !defined(CYW20819A1) && !defined(CYW20735B1) )
#define WICED_GPIO_PIN_LED_2 1
#endif
wiced_bt_gpio_numbers_t led_pin = WICED_GPIO_PIN_LED_2;

/******************************************************************************
 *                          Function Definitions
 ******************************************************************************/

/*
 * Initialise LED control
 */
void led_control_init(uint8_t control_type)
{
    pwm_config_t pwm_config;

    if (control_type == LED_CONTROL_TYPE_ONOFF)
        return;

    else if (control_type == LED_CONTROL_TYPE_LEVEL)
    {
        /* configure PWM */
#ifdef CYW20719B1
        wiced_hal_pwm_configure_pin(led_pin, PWM_CHANNEL);
#endif

#if ( defined(CYW20819A1) || defined(CYW20735B1) )
        wiced_hal_gpio_select_function(WICED_GPIO_PIN_LED_2, WICED_PWM0);
#endif
        wiced_hal_aclk_enable(PWM_INP_CLK_IN_HZ, ACLK1, ACLK_FREQ_24_MHZ);
        wiced_hal_pwm_get_params(PWM_INP_CLK_IN_HZ, 0, PWM_FREQ_IN_HZ, &pwm_config);
        wiced_hal_pwm_start(PWM_CHANNEL, PMU_CLK, pwm_config.toggle_count, pwm_config.init_count, 1);
    }
    else if (control_type == LED_CONTROL_TYPE_COLOR)
    {
        // TBD
    }
}

/*
 * Set LED brightness level 0 to 100%
 */
void led_control_set_brighness_level(uint8_t brightness_level)
{
    pwm_config_t pwm_config;

    WICED_BT_TRACE("set brightness:%d\n", brightness_level);

    // ToDo.  For some reason, setting brightness to 100% does not work well on 20719B1 platform. For now just use 99% instead of 100.
    if (brightness_level == 100)
        brightness_level = 99;

    wiced_hal_pwm_get_params(PWM_INP_CLK_IN_HZ, brightness_level, PWM_FREQ_IN_HZ, &pwm_config);
    wiced_hal_pwm_change_values(PWM_CHANNEL, pwm_config.toggle_count, pwm_config.init_count);
}

/*
 * Turn LED on or off
 */
void led_control_set_onoff(uint8_t onoff_value)
{
    WICED_BT_TRACE("set onoff:%d\n", onoff_value);

    if (onoff_value == 1)           // led is on
    {
        wiced_hal_gpio_configure_pin(led_pin, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
    }
    else if (onoff_value == 0)      // led is off
    {
        wiced_hal_gpio_configure_pin(led_pin, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
    }
}

/*
 * Toggle LED on or off (extended function)
*/
void led_control_toggle_onoff()
{
	if((wiced_hal_gpio_get_pin_output(led_pin)) == GPIO_PIN_OUTPUT_HIGH)
	{
		wiced_hal_gpio_configure_pin(led_pin, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
	}
	else
	{
		wiced_hal_gpio_configure_pin(led_pin, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
	}
}
