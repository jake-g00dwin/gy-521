#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>
#include "gy521_driver.h"

#define WRITE_BIT   (1<<7)

typedef struct reg_addr{
    uint8_t dev_addr;
    uint8_t addr;
    uint8_t value;
}reg_addr;

reg_addr reg_addr_arr[16] = {{0x0, 0x0, 0x0}};
uint8_t idx = 0;

/* Fake Object for TWI_TX*/
void fake_twi_tx(uint8_t slave_addr, uint8_t *data, uint8_t size)
{
    /*Save the slave address passed*/
    reg_addr_arr[0].dev_addr = slave_addr;

    /*Now write all the passed data*/
    for(; idx < size; idx++) {
        reg_addr_arr[idx].addr = *(data);
        reg_addr_arr[idx].value = *(++data);
    } 
    /*Post increment the global index*/
    idx++;
}

/* Fake Object for TWI_RX*/
void fake_twi_rx(uint8_t slave_addr, uint8_t *data, uint8_t size)
{
    /*Save the slave address passed*/
    reg_addr_arr[0].dev_addr = slave_addr;
    
    /*Read the registers requested*/
    for(uint8_t i = 0; i < size; i++) {
        /*Wridxte the register read address*/
        reg_addr_arr[i + idx].addr = *(data + i);
        
        /*Read the response value into the pased data ptr*/
        *(data + i) = reg_addr_arr[i + idx].value;
    }
    /*Post increment the global index*/
    idx++;
}



/*Setup the fake twi*/
void (*gy521_twi_tx)(uint8_t, uint8_t*, uint8_t) = &fake_twi_tx;
void (*gy521_twi_rx)(uint8_t, uint8_t*, uint8_t) = &fake_twi_rx;

/* Tests the donothing function */ 
static void test_gy521_init(void **state) { 
    gy521_module *m = gy521_new();
    assert_false(gy521_init(m, 0x0));
    assert_false(gy521_init(m, 0x67));
    assert_false(gy521_init(m, 0x6A));

    /*Check for it's confirmation of the right twi device*/
    assert_false(gy521_init(m, TWI_GY521_ADDR1));

    /*Fill the address and the value registers with correct response value*/
    /*The zero element get's read on init of the module*/
    reg_addr_arr[0].addr = TWI_GY521_ADDR1;
    reg_addr_arr[0].value = TWI_GY521_ADDR1;
    idx = 0;

    /*Check that it worked*/
    assert_true(gy521_init(m, TWI_GY521_ADDR1));
    assert_true(TWI_GY521_ADDR1 == reg_addr_arr[0].dev_addr); 


    reg_addr_arr[0].addr = TWI_GY521_ADDR2;
    reg_addr_arr[0].value = TWI_GY521_ADDR2;
    idx = 0;

    assert_true(gy521_init(m, TWI_GY521_ADDR2));
    assert_true(TWI_GY521_ADDR2 == reg_addr_arr[0].dev_addr); 

    gy521_free(m);
 
}


static void test_gy521_update_accel(void **sate)
{
    /*check it reads the accel registers*/
    gy521_module *m = gy521_new();
    reg_addr_arr[0].addr = TWI_GY521_ADDR1;
    gy521_init(m, TWI_GY521_ADDR1);
    
    /*Setup the fake accel values.*/
    for(uint8_t i = 0; i < 6; i++) {
        reg_addr_arr[i].value = i * 8;
    }
  
    /*Zero the global index for the TWI*/ 
    idx = 0;  
    gy521_update_accel(m); 

    /*Ensure the correct registers are read*/
    _Bool is_correct = 1;
    assert_true(is_correct);
    for(uint8_t i = 0; i < 6; i++){
        /*The starting address of the registers is 59 and goes to 64*/ 
        if((59 + i) != reg_addr_arr[i].addr) {
            is_correct = 0;
        }
    }
    assert_true(is_correct);     

    /*Check that the values are assembled correctly*/
    struct accel_values accel = gy521_get_accel(m);

    /*Make sure to bitshift by 8 and recomine the two u8 into a single u16*/
    assert_true(accel.x == ((reg_addr_arr[0].value<<8) | reg_addr_arr[1].value));
    assert_true(accel.y == ((reg_addr_arr[2].value<<8) | reg_addr_arr[3].value));
    assert_true(accel.z == ((reg_addr_arr[4].value<<8) | reg_addr_arr[5].value));

    gy521_free(m);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_gy521_init),
        cmocka_unit_test(test_gy521_update_accel),
    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
