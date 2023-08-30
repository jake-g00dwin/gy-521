/*
 * Author: Jake Goodwin
 * Date: 2023
 * Description: 
 */

#include "main.h"



int main(void)
{
    printf("Hello World\n");
    uint8_t state = get_led_state();
    printf("led state: %d", state);
    return 0;
}
