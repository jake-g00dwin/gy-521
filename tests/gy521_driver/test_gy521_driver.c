#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>
#include "gy521_driver.h"

#define WRITE_BIT   (1<<7)

uint8_t fake_twi_addr = 0x0;
uint8_t fake_twi_data[16] = {0x0};


/* Fake Object for TWI_TX*/
void fake_twi_tx(uint8_t slave_addr, uint8_t *data, uint8_t size)
{
    fake_twi_addr = slave_addr; 
}

/* Fake Object for TWI_RX*/
void fake_twi_rx(uint8_t slave_addr, uint8_t *data, uint8_t size)
{
    fake_twi_addr = slave_addr;
    for(int i = 0; i < size; i++) {
        *data++ = fake_twi_data[i];
    }
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

    /*Now give it the correct response*/
    fake_twi_data[0] = TWI_GY521_ADDR1;
    assert_true(gy521_init(m, TWI_GY521_ADDR1));
    assert_true(TWI_GY521_ADDR1 == fake_twi_addr); 


    fake_twi_data[0] = TWI_GY521_ADDR2;
    assert_true(gy521_init(m, TWI_GY521_ADDR2));
    assert_true(TWI_GY521_ADDR2 == fake_twi_addr); 

    gy521_free(m);
 
}


static void test_gy521_update(void **sate)
{
    assert_false(1);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_gy521_init),
        cmocka_unit_test(test_gy521_update),

    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
