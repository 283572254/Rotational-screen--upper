#include "mallocInterface.h"
#include <string.h>
#include <stdlib.h>

const MALLOC_DESCRIPTOR Malloc_Des={
	/*�ڴ�����ӿ� 		------ ������ʹ��stdlib�ӿ�*/
	malloc,
	/*�ڴ��ͷŽӿ� 		------ ������ʹ��stdlib�ӿ�*/
	free,
	/*�ڴ���������ӿ� ------ ������ʹ��stdlib�ӿ�*/
	realloc,
	/*�ڴ����ӿ� 		------ ������ʹ��string�ӿ�*/
	memset,
	/*�ڴ濽���ӿ� 		------ ������ʹ��string�ӿ�*/
	memcpy
};
