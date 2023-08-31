add_subdirectory(led_driver)
add_subdirectory(gy521_driver)


add_executable(main
    main.c
)

target_link_libraries(main
    led_driver
    gy521_driver
)
