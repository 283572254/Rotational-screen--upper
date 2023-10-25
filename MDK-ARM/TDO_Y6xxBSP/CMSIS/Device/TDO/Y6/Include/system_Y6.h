 

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup alpscale_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_Y6_H
#define __SYSTEM_Y6_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup Y6_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup Y6_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup Y6_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup Y6_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup Y6_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_Y6_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT TDO *****END OF FILE****/
