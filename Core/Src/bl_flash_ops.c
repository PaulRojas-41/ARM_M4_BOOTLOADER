/*
 * appl_flash_operations.c
 *
 *  Created on: May 19, 2026
 *      Author: Paul Rojas
 */

#include <bl_flash_ops.h>
#include "drv_ll_flash.h"


void appl_erase_flash(uint32_t fls_sector_address, uint32_t pages)
{
	//uint32_t *ptr_to_flash = (uint32_t *)fls_sector_address;


	/*
	if(pages = 1)
	{
		for(int j = j; j < 4; j++)
			ptr_to_flash[j] = 0xFFFFFFFF;
	}
	else
	{
		/* Move through sectors
		for(int j = 0; j < pages; j++)
		{
			for(int i = 0; i < 4; i++)
			{
				ptr_to_flash[i]= 0xFFFFFFFF;
			}

			ptr_to_flash = ptr_to_flash + APPL_SHIFT_PAGE;
		}
	} */
}

void appl_write_flash(uint32_t fls_sector_address, uint32_t *fls_ota_data, uint32_t pages)
{
	uint32_t *ptr_to_flash = (uint32_t *)fls_sector_address; //header copy

	/* HW initialization */
	wait_flash_op();
	drv_write_flash();

	if(pages = 1)
	{
		for(int i = 0; i < 4; i++)
			ptr_to_flash[i] = fls_ota_data[i];
	}
	else
	{
		/* Move through sectors */
		for(int j = 0; j < pages; j++)
		{
			for(int i = 0; i < 4; i++)
			{
				ptr_to_flash[i]= fls_ota_data[i];
			}

			ptr_to_flash = ptr_to_flash + APPL_SHIFT_PAGE;
		}
	}

	wait_flash_op();
	FLASH->CR &=~(1 << 0); // deactivates the write to flash operation
}

void *appl_read_flash(uint32_t fls_sector_address, uint32_t *fls_data)
{
	uint32_t *get_header = (uint32_t *)fls_sector_address;

	for(int i = 0; i < sizeof(fls_data); i++)
		fls_data[i] = *(get_header + i);
}

void appl_unlock_flash()
{
	drv_unlock_flash();
}

void appl_lock_flash()
{
	drv_lock_flash();
}
