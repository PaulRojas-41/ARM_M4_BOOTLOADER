/*
 * drv_flash_operations.h
 *
 *  Created on: May 24, 2026
 *      Author: Paul Rojas
 */

#ifndef INC_DRV_FLASH_OPS_H_
#define INC_DRV_FLASH_OPS_H_

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

/* External macros */

#define APPL_NB_OF_PAGE 3U
#define APPL_SHIFT_PAGE 4U

#define FLASH_KEY1               0x45670123U
#define FLASH_KEY2               0xCDEF89ABU

/* External objects */


/* External methods */

void drv_erase_flash(uint8_t fls_sector);
void drv_write_flash();
void wait_flash_op();
void drv_unlock_flash();
void drv_lock_flash();


#endif /* INC_DRV_FLASH_OPS_H_ */
