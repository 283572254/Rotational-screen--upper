#ifndef __Y6_UTILITY_DMA_H
#define __Y6_UTILITY_DMA_H

#include "Y6_dma.h"

int DMA_MemCopy(void *dst, void *src, int size);
int DMA_MemSet(void *dst, uint32_t comm, int width, int size);


#endif //__Y6_UTILITY_DMA_H
