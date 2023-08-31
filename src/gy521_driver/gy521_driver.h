/*
 * Author: Jake Goodwin
 * Date: 2023
 * Description:
 */

#ifndef GY521_DRIVER_H
#define GY521_DRIVER_H

#include <stdint.h>
#include <stdlib.h>

/*
 * ############################
 * Defines
 * ############################
 */

#define     STARTUP_DELAY 30 //in ms
#define     TWI_GY521_ADDR1 0x68    //ADO Logic Low
#define     TWI_GY521_ADDR2 0x69    //ADO Logic High

/*
 * ############################
 * Types/Structures 
 * ############################
 */ 
typedef struct gy521_module gy521_module;

/*
 * ############################
 * Function Prototypes
 * ############################
 */ 


/*Function pointers for the TX and RX fuctionality*/

extern void (*gy521_twi_tx)(uint8_t, uint8_t*, uint8_t);
extern void (*gy521_twi_rx)(uint8_t, uint8_t*, uint8_t);


struct gy521_module* gy521_new(void);
_Bool gy521_init(struct gy521_module *m, uint8_t slave_address);
_Bool gy521_update_gyro(struct gy521_module* m);
_Bool gy521_update_accel(struct gy521_module* m);
void gy521_free(struct gy521_module *m);


#endif /* GY521_DRIVER_H */   
