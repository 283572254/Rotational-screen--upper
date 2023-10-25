#include "flashInterface.h"
#include "Y6_xip_write.h"

const FLASH_DESCRIPTOR Flash_Des={
	/*addr flash physical address count erase number This project is the number of sectors 4K bytes per sector*/
	XIP_EraseFlash_Block_4K,
	/*buf The data buffer to be written addr The physical address of the flash to be written.                 
	count the number of bytes written, the interface is not responsible for erasing */
	XIP_WriteFlash_NoCheck,
	
	loadData8FromQspi0
};

