/*
 * drv_flash_operations.c
 *
 *  Created on: May 24, 2026
 *      Author: Paul Rojas
 */

#include "drv_ll_flash.h"


void drv_erase_flash(uint8_t fls_sector)
{
	/* Before each op r/w/e we need to UNLOCK the flash memory
	 * Enable the erase operation
	 * Sector to be erased indicated in REG: SNB[3:0]: Sector number 2 starts from 0x0800 8000
	 * Trigger the erase op
	 * Wait until BUSY bit is cleared by HW
	 * Clear bits of enable erase op and number of sectors */

	while((FLASH->SR & (1 << 16)));
	FLASH->CR |= (1 << 1);
	FLASH->CR |= (fls_sector << 3);
	FLASH->CR |= (1 << 16);
	while((FLASH->SR & (1 << 16)));
	FLASH->CR &=~(1 << 1);
	FLASH->CR &= ~(1 << 3);

}

void drv_write_flash()
{
	/* Before each op r/w/e we need to UNLOCK the flash memory
		 * Wait until BUSY bit is cleared by HW
		 * Trigger the write operation
		 * Select data format to write
		 * Clear bits of enable erase op and number of sectors */
	FLASH->CR |= (1 << 0);
	FLASH->CR &=~(0x3 << 8);
	FLASH->CR |= (0x2 << 8);
}

void wait_flash_op()
{
	while(FLASH->SR & (1 << 16));
}


void drv_unlock_flash()
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

void drv_lock_flash()
{
    FLASH->CR |= FLASH_CR_LOCK;
}
