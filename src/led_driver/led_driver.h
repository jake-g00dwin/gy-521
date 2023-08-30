#ifndef LED_DRIVER
#define LED_DRIVER

#include <inttypes.h>
//extern volatile uint8_t *led_state;


uint8_t get_led_state(void);
void set_led_state(uint8_t state);
void init_led_driver(void);

#endif
