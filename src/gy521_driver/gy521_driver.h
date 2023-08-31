/*
 * Author: Jake Goodwin
 * Date: 2023
 * Description:
 */

#ifndef GY521_DRIVER_H
#define GY521_DRIVER_H

#include <stdint.h>

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
//typedef struct gy521_module_struct *gy521_module;
typedef struct gy521_module_struct *gy521_module;

/*
 * ############################
 * Function Prototypes
 * ############################
 */ 

/*Function pointers for the TX and RX fuctionality*/
extern void twi_tx(uint8_t *data, uint8_t size);
extern void twi_rx(uint8_t *data, uint8_t size);

_Bool init_gy521(uint8_t slave_address);



_Bool module_test(struct gy521_module_struct *m);
uint8_t test_function(void);



#endif /* GY521_DRIVER_H */   
