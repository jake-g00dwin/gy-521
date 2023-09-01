/*
 * Author: Jake Goodwin
 * Date: 2023
 * Description:
 */
#include "gy521_driver.h"
#include <stdint.h>

/*Stuff for cmocka*/
#if UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size,
                          const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif // UNIT_TESTING

#define     NUM_ACCEL_REGS  6
#define     NUM_GYRO_REGS   6

/*
 * ############################
 * REGISTER MAP 
 * ############################
 */ 

enum gy521_map {
    accel_xouth = 0x3B,
    accel_xoutl,
    accel_youth,
    accel_youtl,
    accel_zouth,
    accel_zoutl,
    temp_outh,
    temp_outl,
    gyro_xouth,
    gyro_xoutl,
    gyro_youth,
    gyro_youtl,
    gyro_zouth,
    gyro_zoutl,
    fifo_couth = 0x72,
    fifo_contl,
    fifo_r_w,
    who_am_i,
};

/*
 * ############################
 * Structures 
 * ############################
 */ 



struct gy521_module{
    uint8_t slave_address;
    gyro_values_struct gyro;
    accel_values_struct accel;
};

/*
 * ############################
 * Helper/Private Functions
 * ############################
 */ 
    
uint8_t read_register(gy521_module *m, enum gy521_map reg)
{
    /*Load the data var with athe address of the register to read*/
    uint8_t data = reg;

    /*Indicate we want to read a value from the slave.*/
    gy521_twi_rx(m->slave_address, &data, 1);

    /*The value should now be in the data var*/
    return data;
}

void write_register(gy521_module *m, enum gy521_map reg, uint8_t data)
{
    gy521_twi_tx(m->slave_address, (uint8_t *) &reg, data);
}


/*
 * ############################
 * Function Definitions
 * ############################
 */

gy521_module* gy521_new(void)
{
    gy521_module *m = (gy521_module *)malloc(sizeof(gy521_module));
    m->slave_address = 0x0;
    return m;
}


void gy521_free(gy521_module *m)
{
    free(m);
}


_Bool gy521_init(gy521_module *m, uint8_t slave_address) {
    /*Check to make sure it's a valid address for this module*/
    if((slave_address != TWI_GY521_ADDR1) && (slave_address != TWI_GY521_ADDR2)) { 
        m->slave_address = 0x0;
        return 0;
    }

    /*Set the slave address of the module*/
    m->slave_address = slave_address;

    /*Make sure TWI is working and read the who_am_i register*/
    uint8_t data = read_register(m, who_am_i);
    
    if(data != m->slave_address) {
        return 0;
    }

    return 1;
}


void gy521_update_accel(gy521_module *m)
{
    /*We shift the High byte over by 8 for a u16*/
    m->accel.x = read_register(m, accel_xouth) <<8;
    m->accel.x |= read_register(m, accel_xoutl);
    m->accel.y = read_register(m, accel_youth) <<8;
    m->accel.y |= read_register(m, accel_youtl);
    m->accel.z = read_register(m, accel_zouth) <<8;
    m->accel.z |= read_register(m, accel_zoutl);
}

void gy521_update_gyro(gy521_module *m)
{
    /*We shift the High byte over by 8 for a u16*/
    m->gyro.x = read_register(m, gyro_xouth) <<8;
    m->gyro.x |= read_register(m, gyro_xoutl);
    m->gyro.y = read_register(m, gyro_youth) <<8;
    m->gyro.y |= read_register(m, gyro_youtl);
    m->gyro.z = read_register(m, gyro_zouth) <<8;
    m->gyro.z |= read_register(m, gyro_zoutl);
}


struct accel_values gy521_get_accel(struct gy521_module* m)
{
    struct accel_values s;
    s.x = m->accel.x;
    s.y = m->accel.y;
    s.z = m->accel.z;
    return s;
}


struct gyro_values gy521_get_gyro(struct gy521_module* m)
{
    struct gyro_values s;
    s.x = m->gyro.x;
    s.y = m->gyro.y;
    s.z = m->gyro.z;
    return s;
}
