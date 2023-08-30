# The led_driver module tests
list(APPEND TEST_LIBS "${CMOCKA_LIBRARIES}")
list(APPEND TEST_LIBS led_driver)

list(APPEND TEST_DIRS "${CMOCKA_INCLUDE_DIRS}")
list(APPEND TEST_DIRS "${MyProject_SOURCE_DIR}/src")

add_cmocka_test(test_led_driver
                SOURCES test_led_driver.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${TEST_LIBS}")
add_cmocka_test_environment(test_led_driver)
target_include_directories(test_led_driver PUBLIC "${TEST_DIRS}")
