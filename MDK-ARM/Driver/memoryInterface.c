#include "memoryInterface.h"
#include <string.h>
#include <stdlib.h>

const MEMORY_DESCRIPTOR Memory_Des={
	/*Memory Request Interface 		------ This project uses the stdlib interface*/
	malloc,
	/*Memory release interface 		*/
	free,
	/*Memory reapplication interface */
	realloc,
	/*Memory fill interface 		*/
	memset,
	/*Memory Copy Interface 		*/
	memcpy
};
