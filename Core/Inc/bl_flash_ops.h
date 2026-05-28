/*
 * appl_flash_operations.h
 *
 *  Created on: May 19, 2026
 *      Author: Paul Rojas
 */

#ifndef INC_BL_FLASH_OPS_H_
#define INC_BL_FLASH_OPS_H_

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

/* External macros */

#define APPL_NB_OF_PAGE 3U
#define APPL_SHIFT_PAGE 4U

/* External objects */


/* External methods */

void appl_erase_flash(uint32_t fls_sector_address, uint32_t pages);
void appl_write_flash(uint32_t fls_sector_address, uint32_t *fls_ota_data, uint32_t pages);
void *appl_read_flash(uint32_t fls_sector_address, uint32_t *fls_data);
void appl_unlock_flash();
void appl_lock_flash();


#endif /* INC_BL_FLASH_OPS_H_ */
