add_library(led_driver STATIC
    led_driver.c
)

target_include_directories(led_driver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
