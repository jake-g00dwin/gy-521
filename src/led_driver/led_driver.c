#include "led_driver.h"

uint8_t internal_led_state = 0x00;
uint8_t *led_state = &internal_led_state;

void init_led_driver(void)
{
    led_state = &internal_led_state;
}

uint8_t get_led_state(void)
{
    return *led_state;
}

void set_led_state(uint8_t state)
{
    *led_state = state;
}


