#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>
#include "gy521_driver.h"


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

/* Fake Object for TWI_TX*/
void fake_twi_tx(uint8_t slave_addr, uint8_t *data, uint8_t size)
{

}

/* Tests the donothing function */ 
static void test_gy521_init(void **state) { 

    _Bool result = init_gy521(0); 
    assert_false(result);

    result = init_gy521(1);
    assert_false(result);

    result = init_gy521((uint8_t) TWI_GY521_ADDR1);
    assert_true(result);
 
}

static void test_gy521_module_methods(void **state) {
    gy521_module *module = malloc(sizeof(gy521_module));
    assert_true(module_test(*module)); 
}



int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_gy521_init),
        cmocka_unit_test(test_gy521_module_methods),
    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
