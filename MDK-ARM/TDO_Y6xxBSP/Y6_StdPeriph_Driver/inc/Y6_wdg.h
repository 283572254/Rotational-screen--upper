 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_WDG_H
#define __Y6_WDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"


/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDG
  * @{
  */

/** @defgroup WDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Exported_Constants
  * @{
  */

/** @defgroup WDG_SetMode
  * @{
  */

#define WDG_SETMODE_DEBUG     ((uint32_t)0x00000000)
#define WDG_SETMODE_IT        ((uint32_t)0x00000001)
#define WDG_SETMODE_RESET     ((uint32_t)0x00000003)
#define IS_WDG_MODE(MODE) (((MODE) == WDG_SETMODE_DEBUG) || \
							   ((MODE) == WDG_SETMODE_IT) || \
                               ((MODE) == WDG_SETMODE_RESET))							   

/**
  * @}
  */


/** @defgroup WDG_Flag 
  * @{
  */

#define WDG_FLAG_WDTOF               ((uint32_t)0x00000004)
#define WDG_FLAG_WDINT               ((uint32_t)0x00000008)
#define IS_WDG_FLAG(FLAG) (((FLAG) == WDG_FLAG_WDTOF) || ((FLAG) == WDG_FLAG_WDINT))

#define IS_WDG_RELOAD(RELOAD) ((RELOAD) >= 0x000000FF)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup WDG_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Exported_Functions
  * @{
  */
  
void WDT_CLKSET(FunctionalState NewState);
void WDT_Reset(void);
void WDG_SetMode(uint32_t Mode);
void WDG_SetReload(uint32_t Reload);
void WDG_ReloadCounter(void);
FlagStatus WDG_GetFlagStatus(uint32_t WDG_FLAG);
void WDG_ClearTimeOutFlag(void);
void WDG_ClearITFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_WDG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/

