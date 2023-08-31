/*
 * Author: Jake Goodwin
 * Date: 2023
 * Description:
 */
#include "gy521_driver.h"
#include <stdint.h>


typedef struct{
    uint16_t x;
    uint16_t y;
    uint16_t z;
}gyro_values_struct;

typedef struct{
    uint16_t x;
    uint16_t y;
    uint16_t z;
}accel_values_struct;

typedef struct{
    _Bool (*init)(uint8_t slv_addr); 
}methods_struct;

typedef struct{
    uint8_t slave_address;
    gyro_values_struct gyro;
    accel_values_struct accel;
    methods_struct methods;
}gy521_module_struct;


_Bool init_gy521(uint8_t slave_address) {
    if(slave_address != TWI_GY521_ADDR1 && slave_address != TWI_GY521_ADDR2) {
        return 0;
    }

    return 1;
}

_Bool module_test(gy521_module_struct *m)
{
    _Bool ret = m->methods.init(TWI_GY521_ADDR1);
    return ret;
}


/* returns 1 */  
uint8_t test_function(void)
{
    return 1;
}
