
#ifndef __LED_CONTROL__H
#define __LED_CONTROL__H

#ifdef __cplusplus
extern "C" {
#endif

#define LED_CONTROL_TYPE_ONOFF   0
#define LED_CONTROL_TYPE_LEVEL   1
#define LED_CONTROL_TYPE_COLOR   2

/*
 * Initialise LED control of a specific type
 */
void led_control_init(uint8_t control_type);

/*
 * Set LED brightness level 0 to 100%
 */
void led_control_set_brighness_level(uint8_t brightness_level);

/*
 * Turn LED on or off
 */
void led_control_set_onoff(uint8_t onoff_value);

/*
 * Toggle LED on or off (extended function)
*/
void led_control_toggle_onoff();

#ifdef __cplusplus
}
#endif

#endif
