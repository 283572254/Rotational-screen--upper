 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_RCC_H
#define __Y6_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */ 

#define PRESET_BIT_ROM         0
#define PRESET_BIT_RAM0        1
#define PRESET_BIT_RAM1        2
#define PRESET_BIT_GPIO        3
#define PRESET_BIT_DMA         4
#define PRESET_BIT_UART0       5
#define PRESET_BIT_UART1       6
#define PRESET_BIT_I2C0        7
#define PRESET_BIT_OTP         8
#define PRESET_BIT_ADC0        9
#define PRESET_BIT_ADC1        10
#define PRESET_BIT_IOCON       11
#define PRESET_BIT_WDT         12
#define PRESET_BIT_QSPI0       13
#define PRESET_BIT_QSPI1       14
#define PRESET_BIT_QSPI2       15
#define PRESET_BIT_CMP         16
#define PRESET_BIT_TIM1        17
#define PRESET_BIT_TIM15       18
#define PRESET_BIT_TIM16       19
#define PRESET_BIT_TIM17       20
#define PRESET_BIT_RTC         21
#define PRESET_BIT_USB         22
//#define PRESET_BIT_QSPI3     23
#define PRESET_BIT_TIM4        24
#define PRESET_BIT_LED         25
#define PRESET_BIT_BITCOPY     26
#define PRESET_BIT_UART2       27

#define AHBCLK_BIT_ROM         0
#define AHBCLK_BIT_RAM0        1
#define AHBCLK_BIT_RAM1        2
#define AHBCLK_BIT_GPIO        3
#define AHBCLK_BIT_DMA         4
#define AHBCLK_BIT_UART0       5
#define AHBCLK_BIT_UART1       6
#define AHBCLK_BIT_I2C0        7
#define AHBCLK_BIT_OTP         8
#define AHBCLK_BIT_ADC0        9
#define AHBCLK_BIT_ADC1        10
#define AHBCLK_BIT_IOCON       11
#define AHBCLK_BIT_WDT         12
#define AHBCLK_BIT_QSPI0       13
#define AHBCLK_BIT_QSPI1       14
#define AHBCLK_BIT_QSPI2       15
#define AHBCLK_BIT_CMP         16
#define AHBCLK_BIT_TIM1        17
#define AHBCLK_BIT_TIM15       18
#define AHBCLK_BIT_TIM16       19
#define AHBCLK_BIT_TIM17       20
#define AHBCLK_BIT_RTC         21
#define AHBCLK_BIT_USB         22
//#define AHBCLK_BIT_QSPI3     23
#define AHBCLK_BIT_TIM4        24
#define AHBCLK_BIT_LED         25
#define AHBCLK_BIT_BITCOPY     26
#define AHBCLK_BIT_UART2       27


/** @defgroup MAINCLK_SOURCE 
  * @{
  */
#define RCC_MAINCLK_SOURCE_12MIRC            0
#define RCC_MAINCLK_SOURCE_SYSPLL            1
#define RCC_MAINCLK_SOURCE_12MOSC            2
#define RCC_MAINCLK_SOURCE_10KIRC            3

#define IS_RCC_MAINCLK_SOURCE(SOURCE)      (((SOURCE) == RCC_MAINCLK_SOURCE_12MIRC) || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_SYSPLL) || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_12MOSC) || \
                                            ((SOURCE) == RCC_MAINCLK_SOURCE_10KIRC))

/**
  * @}
  */

/** @defgroup UARTCLK_SOURCE 
  * @{
  */
#define RCC_UARTCLK_SOURCE_12MIRC            0
#define RCC_UARTCLK_SOURCE_SYSPLL            1
#define RCC_UARTCLK_SOURCE_12MOSC            2
#define RCC_UARTCLK_SOURCE_10KIRC            3

#define IS_RCC_UARTCLK_SOURCE(SOURCE)      (((SOURCE) == RCC_UARTCLK_SOURCE_12MIRC) || \
                                            ((SOURCE) == RCC_UARTCLK_SOURCE_SYSPLL) || \
                                            ((SOURCE) == RCC_UARTCLK_SOURCE_12MOSC) || \
                                            ((SOURCE) == RCC_UARTCLK_SOURCE_10KIRC))

/**
  * @}
  */

/** @defgroup OUTCLK_SOURCE 
  * @{
  */
#define RCC_OUTCLK_SOURCE_12MIRC             0
#define RCC_OUTCLK_SOURCE_SYSPLL             1
#define RCC_OUTCLK_SOURCE_10KIRC             2
#define RCC_OUTCLK_SOURCE_12MOSC             3
#define RCC_OUTCLK_SOURCE_32KOSC             4
#define RCC_OUTCLK_SOURCE_USBPLL             5

#define IS_RCC_OUTCLK_SOURCE(SOURCE)       (((SOURCE) == RCC_OUTCLK_SOURCE_12MIRC) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_SYSPLL) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_10KIRC) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_12MOSC) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_32KOSC) || \
                                            ((SOURCE) == RCC_OUTCLK_SOURCE_USBPLL))


/**
  * @}
  */

/** @defgroup WDTCLK_SOURCE 
  * @{
  */
#define RCC_WDTCLK_SOURCE_12MIRC             0
#define RCC_WDTCLK_SOURCE_SYSPLL             1
#define RCC_WDTCLK_SOURCE_12MOSC             2
#define RCC_WDTCLK_SOURCE_10KIRC             3

#define IS_RCC_WDTCLK_SOURCE(SOURCE)       (((SOURCE) == RCC_WDTCLK_SOURCE_12MIRC) || \
                                            ((SOURCE) == RCC_WDTCLK_SOURCE_SYSPLL) || \
                                            ((SOURCE) == RCC_WDTCLK_SOURCE_12MOSC) || \
                                            ((SOURCE) == RCC_WDTCLK_SOURCE_10KIRC))

/**
  * @}
  */

/** @defgroup SYSPLL_VAL 
  * @{
  */
#define RCC_SYSPLL_VAL_120                   0
#define RCC_SYSPLL_VAL_132                   1
#define RCC_SYSPLL_VAL_144                   2
#define RCC_SYSPLL_VAL_156                   3
#define RCC_SYSPLL_VAL_168                   4
#define RCC_SYSPLL_VAL_180                   5
#define RCC_SYSPLL_VAL_192                   6
#define RCC_SYSPLL_VAL_204                   7
#define RCC_SYSPLL_VAL_216                   8
#define RCC_SYSPLL_VAL_228                   9
#define RCC_SYSPLL_VAL_240                   10

#define IS_RCC_SYSPLL_VAL(VAL)             (((VAL) == RCC_SYSPLL_VAL_120) || \
                                            ((VAL) == RCC_SYSPLL_VAL_132) || \
                                            ((VAL) == RCC_SYSPLL_VAL_144) || \
                                            ((VAL) == RCC_SYSPLL_VAL_156) || \
                                            ((VAL) == RCC_SYSPLL_VAL_168) || \
                                            ((VAL) == RCC_SYSPLL_VAL_180) || \
                                            ((VAL) == RCC_SYSPLL_VAL_192) || \
                                            ((VAL) == RCC_SYSPLL_VAL_204) || \
                                            ((VAL) == RCC_SYSPLL_VAL_216) || \
                                            ((VAL) == RCC_SYSPLL_VAL_228) || \
                                            ((VAL) == RCC_SYSPLL_VAL_240))

/**
  * @}
  */


/** @defgroup CAPPIO_PinNum 
  * @{
  */
#define RCC_PinNum_0                         0
#define RCC_PinNum_1                         1
#define RCC_PinNum_2                         2
#define RCC_PinNum_3                         3
#define RCC_PinNum_4                         4
#define RCC_PinNum_5                         5
#define RCC_PinNum_6                         6
#define RCC_PinNum_7                         7
#define IS_RCC_CAPPIO_PinNum(NUM)           (((NUM) < 8))

/**
  * @}
  */

/** @addtogroup CAPPIO_PortNum
  * @{
  */
#define RCC_PortNum_0                        0
#define RCC_PortNum_1                        1
#define IS_RCC_CAPPIO_PortNum(NUM)          (((NUM) < 2))
/**
  * @}
  */
/** @defgroup APRP_PinNum 
  * @{
  */
#define RCC_GPIO0_PIN0                       0
#define RCC_GPIO0_PIN1                       1
#define RCC_GPIO0_PIN2                       2
#define RCC_GPIO0_PIN3                       3
#define RCC_GPIO0_PIN4                       4
#define RCC_GPIO0_PIN5                       5
#define RCC_GPIO0_PIN6                       6
#define RCC_GPIO0_PIN7                       7

#define RCC_GPIO1_PIN0                       8
#define RCC_GPIO1_PIN1                       9
#define RCC_GPIO1_PIN2                       10
#define RCC_GPIO1_PIN3                       11
#define RCC_GPIO1_PIN4                       12
#define RCC_GPIO1_PIN5                       13
#define RCC_GPIO1_PIN6                       14
#define RCC_GPIO1_PIN7                       15

#define IS_RCC_GPIOX_PINY(PIN)             (((PIN) == RCC_GPIO0_PIN0) || ((PIN) == RCC_GPIO0_PIN1) || \
                                            ((PIN) == RCC_GPIO0_PIN2) || ((PIN) == RCC_GPIO0_PIN3) || \
                                            ((PIN) == RCC_GPIO0_PIN4) || ((PIN) == RCC_GPIO0_PIN5) || \
                                            ((PIN) == RCC_GPIO0_PIN6) || ((PIN) == RCC_GPIO0_PIN7) || \
                                            ((PIN) == RCC_GPIO1_PIN0) || ((PIN) == RCC_GPIO1_PIN1) || \
                                            ((PIN) == RCC_GPIO1_PIN2) || ((PIN) == RCC_GPIO1_PIN3) || \
                                            ((PIN) == RCC_GPIO1_PIN4) || ((PIN) == RCC_GPIO1_PIN5) || \
                                            ((PIN) == RCC_GPIO1_PIN6) || ((PIN) == RCC_GPIO1_PIN7))
/**
  * @}
  */

/** @defgroup APRP_MODE 
  * @{
  */
#define RCC_APRP_MODE_RisingEdge             0x1
#define RCC_APRP_MODE_FallingEdge            0x0
#define IS_RCC_APRP_MODE(MODE)              (((MODE) == RCC_APRP_MODE_RisingEdge) || ((MODE) == RCC_APRP_MODE_FallingEdge))

/**
  * @}
  */

/** @defgroup PDCFG_MOD 
  * @{
  */
#define RCC_PDCFG_EXT12M                     0x0001
#define RCC_PDCFG_10KIRC                     0x0002
#define RCC_PDCFG_ADC0                       0x0004
// #define RCC_PDCFG_ADC1                    0x0008
#define RCC_PDCFG_SYSPLL                     0x0010
#define RCC_PDCFG_BOD                        0x0020
#define RCC_PDCFG_BOR                        0x0040
#define RCC_PDCFG_RTC                        0x0080
#define RCC_PDCFG_12MIRC                     0x0100
//#define RCC_PDCFG_CMP0                     0x0200
//#define RCC_PDCFG_CMP1                     0x0400
#define RCC_PDCFG_USB                        0x0800
#define RCC_PDCFG_32KOSC                     0x1000
#define IS_RCC_PDCFG_ANALOG_BLOCK(MODULE)  (((MODULE) & 0x1FFF) != 0)

/**
  * @}
  */

/** @defgroup PDCFG_MODE 
  * @{
  */
#define RCC_PDCFG_POWER_ON                   0
#define RCC_PDCFG_POWER_DOWN                 1
#define IS_RCC_PDCFG_MODE(MODE)             (((MODE) == RCC_PDCFG_POWER_ON) || ((MODE) == RCC_PDCFG_POWER_DOWN))
/**
  * @}
  */

/** @defgroup SYSRST_FLAG 
  * @{
  */
#define RCC_SYSRSTSTATE_POR                  0x01
#define RCC_SYSRSTSTATE_EXERSTN              0x02
#define RCC_SYSRSTSTATE_WDT                  0x04
#define RCC_SYSRSTSTATE_BOD                  0x08
#define RCC_SYSRSTSTATE_SYSRST               0x10
#define IS_RCC_SYSRST_FLAG(FLAG)           (((FLAG) == RCC_SYSRSTSTATE_POR)     || \
                                            ((FLAG) == RCC_SYSRSTSTATE_EXERSTN) || \
                                            ((FLAG) == RCC_SYSRSTSTATE_WDT)     || \
                                            ((FLAG) == RCC_SYSRSTSTATE_BOD)     || \
                                            ((FLAG) == RCC_SYSRSTSTATE_SYSRST))
 /**
  * @}
  */

/** @addtogroup PCON
  * @{
  */
#define RCC_DPDEN                            0x0002
#define RCC_SLEEPFLAG                        0x0100
#define RCC_DPDFLAG                          0x0800
#define IS_RCC_PCON_FLAG(FLAG)             (((FLAG) == RCC_DPDEN)     || \
                                            ((FLAG) == RCC_SLEEPFLAG) || \
                                            ((FLAG) == RCC_DPDFLAG))

#define LOW_POWER_SLEEP_MODE                 0
#define LOW_POWER_POWER_DOWN_MODE            1
#define IS_LOW_POWER_MODE(mode)            (((mode) == LOW_POWER_SLEEP_MODE) || ((mode) == LOW_POWER_POWER_DOWN_MODE))
/**
  * @}
  */


/** @defgroup SYSTICK_CAL 
  * @{
  */
#define IS_RCC_SYSTICK_CAL(CAL)            (((CAL) & 0xFC000000) == 0)

/**
  * @}
  */

/** @defgroup BODINT_VAL
  * @{
  */
#define RCC_BODINT_VAL_2_56                  0x00000000
#define RCC_BODINT_VAL_2_65                  0x00008000
#define RCC_BODINT_VAL_2_74                  0x00010000
#define RCC_BODINT_VAL_2_84                  0x00018000
#define IS_RCC_BODINT_VAL(VAL)             (((VAL) == RCC_BODINT_VAL_2_56) || \
                                            ((VAL) == RCC_BODINT_VAL_2_65) || \
                                            ((VAL) == RCC_BODINT_VAL_2_74) || \
                                            ((VAL) == RCC_BODINT_VAL_2_84))    

#define RCC_BODCTRL_CLEAR_Mask               0xFFFE7FFF
//bit2
#define RCC_BODRSTENA_SET_Mask               0x00000004
#define RCC_BODRSTENA_RESET_Mask             0xFFFFFFFB

/**
  * @}
  */

/** @defgroup Peripheral_CLK 
  * @{
  */
#define RCC_CLOCKFREQ_SYSAHBCLK              0x080
#define RCC_CLOCKFREQ_UART0CLK               0x090
#define RCC_CLOCKFREQ_UART1CLK               0x094
#define RCC_CLOCKFREQ_UART2CLK               0x098
#define RCC_CLOCKFREQ_SYSTICKCLK             0x0A0
#define RCC_CLOCKFREQ_QSPI0CLK               0x0A4
#define RCC_CLOCKFREQ_QSPI1CLK               0x0A8
#define RCC_CLOCKFREQ_QSPI2CLK               0x0AC
#define RCC_CLOCKFREQ_WDTCLK                 0x0B4
#define RCC_CLOCKFREQ_CLKOUTCLK              0x0B8
#define RCC_CLOCKFREQ_USBCLK                 0x0BC
#define RCC_CLOCKFREQ_ADCCLK                 0x0C0
#define RCC_CLOCKFREQ_PWMCLK                 0x0D0

#define IS_RCC_Peripheral_CLK(CLK)         (((CLK) == RCC_CLOCKFREQ_SYSAHBCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_UART0CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_UART1CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_UART2CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_SYSTICKCLK) || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI0CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI1CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI2CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_WDTCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_CLKOUTCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_USBCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_ADCCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_PWMCLK))

#define IS_RCC_CLKDIV_PER(CLK)             (((CLK) == RCC_CLOCKFREQ_SYSAHBCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_UART0CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_UART1CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_UART2CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_SYSTICKCLK) || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI0CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI1CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_QSPI2CLK)   || \
                                            ((CLK) == RCC_CLOCKFREQ_WDTCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_CLKOUTCLK)  || \
                                            ((CLK) == RCC_CLOCKFREQ_USBCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_ADCCLK)     || \
                                            ((CLK) == RCC_CLOCKFREQ_PWMCLK))



void RCC_SetPRESETCTRL(uint32_t PRESETCTRL, FunctionalState NewState);
void RCC_SetAHBCLK(uint32_t AHBCLK, FunctionalState NewState);
void RCC_ResetAHBCLK(uint32_t AHBCLK);
void RCC_SETCLKDivider(uint32_t RCC_Peripheral, uint8_t RCC_CLKDIV);
void RCC_SetSystickCal(uint32_t SystickCalibration);

void RCC_SYSPLLConfig( uint32_t RCC_SYSPLL);
void RCC_MAINCLKSel(uint8_t RCC_MAINCLKSource);
void RCC_OUTCLKSel(uint8_t RCC_OUTCLKSource);
void RCC_UARTCLKSel(uint8_t RCC_UARTCLKSource);
void RCC_WDTCLKSel(uint8_t RCC_WDTCLKSource);

uint32_t RCC_GetClocksFreq(uint32_t RCC_Clocks);

void RCC_APRPConfig(uint32_t RCC_GPIOxPINy, uint32_t RCC_APRP_MODE);
void RCC_ERPCmd(uint32_t RCC_GPIOxPINy, FunctionalState NewState);
void RCC_RSRPCmd(uint32_t RCC_GPIOxPINy);
FlagStatus RCC_GETSRP(uint32_t RCC_GPIOxPINy);

void RCC_BODConfig(uint8_t BODINTVal, FunctionalState NewState);
FlagStatus RCC_CAPPIO(uint32_t RCC_PortNum, uint32_t RCC_PinNum);

FlagStatus RCC_GetSYSRSTFlagStatus(uint16_t RCC_FLAG);
void RCC_ClearSYSRSTFlag(uint16_t RCC_FLAG);

FlagStatus RCC_GetPCONFlagStatus(uint16_t RCC_FLAG);
void RCC_ClearPCONFlag(uint16_t RCC_FLAG);
void RCC_LowPowerCmd(uint8_t LOW_POWER_MODE);

void RCC_PDRUNConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE);
void RCC_PDAWAKEConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE);
void RCC_PDSLEEPConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE);

void RCC_ConfRandomSeed(uint32_t seed);
uint32_t RCC_GetRandomData(void);

typedef enum {SM_SLEEP = 0, SM_DEEPSLEEP = 1, SM_POWERDOWN = 2} SleepMode;
void goSleep(SleepMode mode);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_RCC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2012 TDO *****END OF FILE****/

