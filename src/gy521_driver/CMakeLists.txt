add_library(gy521_driver STATIC
    gy521_driver.c
)

target_include_directories(gy521_driver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
