#include "mallocInterface.h"
#include <string.h>
#include <stdlib.h>

const MALLOC_DESCRIPTOR Malloc_Des={
	/*内存申请接口 		------ 本工程使用stdlib接口*/
	malloc,
	/*内存释放接口 		------ 本工程使用stdlib接口*/
	free,
	/*内存重新申请接口 ------ 本工程使用stdlib接口*/
	realloc,
	/*内存填充接口 		------ 本工程使用string接口*/
	memset,
	/*内存拷贝接口 		------ 本工程使用string接口*/
	memcpy
};
