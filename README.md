# gy-521 Driver

The gy-521 module is usally interfaced with via TWI/I2C. The actual chip that
is used in the module is the mpu6050 ic.

This driver doesn't make any assumptions about the platform it will run
on beyond that it supports "stdlib.h" and "inttypes.h".

The interface handles all the register and bitshift operations in the 
the backgorund. The module uses getters and setters to abstract the
actual data. This prevents the end user from trying to directly use the 
structures data when it is volatile and may be setup to update in a ISR.

## PINs

- VCC: 3.3v
- GND: ground or 0v
- SCL: TWI clock
- SDA: TWI data
- XDA:
- XCL:
- AD0: changes the TWI address when pulled high.
- INT: interrupt pin


## Running and building the project
The project uses CMake along with cmocka for unit testing.

```sh
# change into the build dir
cd ./build

# generate the make files and make everything.
cmake ../ -DUNIT_TESTING=ON; make all;

# Run the tests
ctest

```

## RoadMap

- add in functions for interrupt driven updates.
- add functions for configuration of module.
- add functions to save configurations in memory.
- add functions to load saved configs




