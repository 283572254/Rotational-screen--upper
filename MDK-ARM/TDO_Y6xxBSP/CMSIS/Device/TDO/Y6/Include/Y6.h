

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup alpscale
  * @{
  */
    
#ifndef __Y6_H
#define __Y6_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/** @addtogroup Library_configuration_section
  * @{
  */
  

#if !defined  USE_STDPERIPH_DRIVER
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
  /*#define USE_STDPERIPH_DRIVER*/
#endif /* USE_STDPERIPH_DRIVER */

//#define EXECUTE_ON_FPGA

/**
 * @brief Y6 Standard Peripheral Library version number V1.0.1
   */
#define __Y6_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __Y6_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __Y6_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __Y6_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __Y6_STDPERIPH_VERSION        ((__Y6_STDPERIPH_VERSION_MAIN << 24)\
                                         |(__Y6_STDPERIPH_VERSION_SUB1 << 16)\
                                         |(__Y6_STDPERIPH_VERSION_SUB2 << 8)\
                                         |(__Y6_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Y6 Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
#define __CM0_REV                 0 /*!< Core Revision r0p0                            */
#define __MPU_PRESENT             0 /*!< ALPSCALE do not provide MPU                  */
#define __NVIC_PRIO_BITS          2 /*!< ALPSCALE uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used  */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                        */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                          */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                      */

/******  Y6 specific Interrupt Numbers ************************************************************/
  WKT_IRQn                    = 0,      /*!< PIO0_0  Wakeup Interrupt                                */
  TIM1_IRQn                   = 1,      /*!< PIO0_1  Wakeup Interrupt                                */
  TIM15_IRQn                  = 2,      /*!< PIO0_2  Wakeup Interrupt                                */
  TIM16_IRQn                  = 3,      /*!< PIO0_3  Wakeup Interrupt                                */
  TIM17_IRQn                  = 4,      /*!< PIO0_4  Wakeup Interrupt                                */
  RTC_IRQn                    = 5,      /*!< PIO0_5  Wakeup Interrupts                               */
  USB0_IRQn                   = 6,      /*!< PIO0_6  Wakeup Interrupts                               */
  USB0_DMA_IRQn               = 7,      /*!< PIO0_7  Wakeup Interrupts                               */
  TIM4_IRQn                   = 8,      /*!< FLASH Interrupt                                         */
  UART0_IRQn                  = 9,      /*!< UART0 Interrupt                                         */
  UART1_IRQn                  = 10,     /*!< UART1 Interrupts                                        */
  I2C0_IRQn                   = 11,     /*!< I2C0 Interrupts                                         */
  UART2_IRQn                  = 12,     /*!< UART2 Interrupts                                        */
  QSPI0_IRQn                  = 13,     /*!< QSPI0 Interrupts                                         */
  QSPI1_IRQn                  = 14,     /*!< QSPI1 Interrupt                                        */
  QSPI2_IRQn                  = 15,     /*!< QSPI2 Interrupt                                        */
  DMA_IRQn                    = 16,     /*!< DMA Interrupts                                          */
  GPIO0_IRQn                  = 17,     /*!< GPIO0 Interrupt                                         */
  GPIO1_IRQn                  = 18,     /*!< GPIO0 Interrupt                                         */
  ADC0_IRQn                   = 19,     /*!< ADC0 Interrupt                                          */
  BOD_IRQn                    = 21,     /*!< BOD  Interrupt                                          */
  BOR_IRQn                    = 22,     /*!< BOR Interrupt                                           */
  CMP_IRQn                    = 23,     /*!< CMP Interrupt                                           */
  LED_IRQn                    = 26,     /*!< LED Interrupt                                         */
  BITCOPY_IRQn                = 27,     /*!< BITCOPY Interrupt                                         */
} IRQn_Type;

/**
  * @}
  */

#include "core_cm0.h"
#include "system_Y6.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */  

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** @addtogroup Peripheral_registers_structures
  * @{
  */   

/** 
  * @brief UART
  */

typedef struct
{
  __IO uint32_t CTRL0;
  __IO uint32_t CTRL0_SET;
  __IO uint32_t CTRL0_CLR;
  __IO uint32_t CTRL0_TOG;
  __IO uint32_t CTRL1;
  __IO uint32_t CTRL1_SET;
  __IO uint32_t CTRL1_CLR;
  __IO uint32_t CTRL1_TOG;
  __IO uint32_t CTRL2;
  __IO uint32_t CTRL2_SET;
  __IO uint32_t CTRL2_CLR;
  __IO uint32_t CTRL2_TOG;
  __IO uint32_t LINECTRL;
  __IO uint32_t LINECTRL_SET;
  __IO uint32_t LINECTRL_CLR;
  __IO uint32_t LINECTRL_TOG;
  __IO uint32_t INTR;
  __IO uint32_t INTR_SET;
  __IO uint32_t INTR_CLR;
  __IO uint32_t INTR_TOG;
  __IO uint32_t DATA;
  uint32_t RESERVED0[3];
  __IO uint32_t STAT;
  uint32_t RESERVED1[3];
  __IO uint32_t DEBUG;
  uint32_t RESERVED2[3];
  __IO uint8_t  ILPR;
  uint8_t  RESERVED3;
  uint16_t RESERVED4;
  uint32_t RESERVED5[3];
  __IO uint8_t  RS485CTRL;
  uint8_t  RESERVED6;
  uint16_t RESERVED7;
  __IO uint8_t  RS485CTRL_SET;
  uint8_t  RESERVED8;
  uint16_t RESERVED9;
  __IO uint8_t  RS485CTRL_CLR;
  uint8_t  RESERVED10;
  uint16_t RESERVED11;
  __IO uint8_t  RS485CTRL_TOG;
  uint8_t  RESERVED12;
  uint16_t RESERVED13;
  __IO uint8_t  RS485ADRMATCH;
  uint8_t  RESERVED14;
  uint16_t RESERVED15;
  uint32_t RESERVED16[3];
  __IO uint8_t  RS485DLY;
  uint8_t  RESERVED17;
  uint16_t RESERVED18;
  uint32_t RESERVED19[3];
  __IO uint16_t AUTOBAUD;
  uint16_t RESERVED20;
  __IO uint16_t AUTOBAUD_SET;
  uint16_t RESERVED21;
  __IO uint16_t AUTOBAUD_CLR;
  uint16_t RESERVED22;
  __IO uint16_t AUTOBAUD_TOG;
  uint16_t RESERVED23;
  __IO uint32_t CTRL3;
  __IO uint32_t CTRL3_SET;
  __IO uint32_t CTRL3_CLR;
  __IO uint32_t CTRL3_TOG;
  __IO uint16_t ISO7816_CTRL;
  uint16_t RESERVED24;
  __IO uint16_t ISO7816_CTRL_SET;
  uint16_t RESERVED25;
  __IO uint16_t ISO7816_CTRL_CLR;
  uint16_t RESERVED26;
  __IO uint16_t ISO7816_CTRL_TOG;
  uint16_t RESERVED27;
  __IO uint8_t  IS07816_ERR_CNT;
  uint8_t  RESERVED28;
  uint16_t RESERVED29;
  uint32_t RESERVED30[3];
  __IO uint8_t  IS07816_STATUS;
  uint8_t  RESERVED31;
  uint16_t RESERVED32;
  uint32_t RESERVED33[3];
} UART_TypeDef;

typedef struct
{
  __IO uint32_t CON;                //0X00
  __IO uint32_t TAR;                //0X04
  __IO uint32_t SAR;                //0X08
  __IO uint32_t HS_MADDR;          //0X0C
  __IO uint32_t DATA_CMD;          //0X10
  __IO uint32_t SS_SCL_HCNT;       //0X14
  __IO uint32_t SS_SCL_LCNT;       //0X18
  __IO uint32_t FS_SCL_HCNT;       //0X1C
  __IO uint32_t FS_SCL_LCNT;       //0X20
  __IO uint32_t HS_SCL_HCNT;       //0X24
  __IO uint32_t HS_SCL_LCNT;       //0X28
  __IO uint32_t INTR_STAT;         //0X2C
  __IO uint32_t INTR_MASK;         //0X30
  __IO uint32_t RAW_INTR_STAT;     //0X34
  __IO uint32_t RX_TL;              //0X38
  __IO uint32_t TX_TL;              //0X3C
  __IO uint32_t CLR_INTR;           //0X40
  __IO uint32_t CLR_RX_UNDER;      //0X44
  __IO uint32_t CLR_RX_OVER;       //0X48
  __IO uint32_t CLR_TX_OVER;       //0X4C
  __IO uint32_t CLR_RD_REQ;        //0X50
  __IO uint32_t CLR_TX_ABRT;       //0X54
  __IO uint32_t CLR_RX_DONE;       //0X58
  __IO uint32_t CLR_ACTIVITY;      //0X5C
  __IO uint32_t CLR_STOP_DET;      //0X60
  __IO uint32_t CLR_START_DET;     //0X64
  __IO uint32_t CLR_GEN_CALL;      //0X68
  __IO uint32_t ENABLE;             //0X6C
  __IO uint32_t STAT;               //0X70
  __IO uint32_t TXFLR;              //0X74
  __IO uint32_t RXFLR;              //0X78
  uint32_t RESERVED;           //0X7C
  __IO uint32_t TX_ABRT_SOURCE;    //0X80
  __IO uint32_t SLV_DATA_NACK_ONLY;//0X84
  __IO uint32_t DMA_CR;             //0X88
  __IO uint32_t DMA_TDLR;           //0X8C
  __IO uint32_t DMA_RDLR;           //0X90
  __IO uint32_t SDA_SETUP;          //0X94
  __IO uint32_t ACK_GENERAL_CALL;  //0X98
  __IO uint32_t ENABLE_STATUS;	   //0X9C
}I2C_TypeDef;

/** 
  * @brief WKT
  */
typedef struct
{
  __IO uint32_t CTRL;    
  __IO uint32_t COUNT; 
  uint32_t RESERVED0[2];     
  __IO uint32_t GEN0; 
  __IO uint32_t GEN1; 
  __IO uint32_t GEN2; 
  __IO uint32_t GEN3; 
} WKT_TypeDef;

/** 
  * @brief Independent WATCHDOG
  */
typedef struct
{
  __IO uint32_t WDMOD;
  __IO uint32_t WDTC;
  __IO uint32_t WDFEED;
  __IO uint32_t WDTV;
}WDG_TypeDef;

#define WDG_BASE             (0x4000E000)
#define WDG                  ((WDG_TypeDef *) WDG_BASE)


/** 
  * @brief Reset and Clock Control
  */
typedef struct
{
  __IO uint32_t PRESETCTRL0;//0x00
  __IO uint32_t PRESETCTRL0_SET;
  __IO uint32_t PRESETCTRL0_CLR;
  __IO uint32_t PRESETCTRL0_TOG;
  __IO uint32_t AHBCLKCTRL0;//0x10
  __IO uint32_t AHBCLKCTRL0_SET;
  __IO uint32_t AHBCLKCTRL0_CLR;
  __IO uint32_t AHBCLKCTRL0_TOG;
  uint32_t RESERVED0;//0x20
  __IO uint32_t ADDRESS_REMAP;	//0x24
  __IO uint32_t OSC12_CTRL;
  __IO uint32_t OSC10_CTRL;
  __IO uint32_t SYSPLLCTRL;//0x30
  __IO uint32_t SYSPLLSTAT;
  __IO uint32_t LDO_CTRL;  //add 0x48
  __IO uint32_t USBCTRL;   //add 0x3C
  __IO uint32_t SYSRSTSTAT;//0x40
  uint32_t RESERVED3[3];
  __IO uint32_t MAINCLKSEL;//0x50
  __IO uint32_t MAINCLKUEN;
  __IO uint32_t UARTCLKSEL;
  __IO uint32_t UARTCLKUEN;
  uint32_t RESERVED6[2];//0x60
  __IO uint32_t WDTCLKSEL;
  __IO uint32_t WDTCLKUEN;
  __IO uint32_t OUTCLKSEL;//0x70
  __IO uint32_t OUTCLKUEN;
  uint32_t RESERVED8[2];
  __IO uint32_t SYSAHBCLKDIV;//0x80
  uint32_t RESERVED10[3];
  __IO uint32_t UART0CLKDIV;//0x90
  __IO uint32_t UART1CLKDIV;
  __IO uint32_t UART2CLKDIV;
  uint32_t RESERVED1;
  __IO uint32_t SYSTICKCLKDIV;//0xa0
  __IO uint32_t QUADSPI0CLKDIV;
  __IO uint32_t QUADSPI1CLKDIV;
  __IO uint32_t QUADSPI2CLKDIV;
  uint32_t RESERVED7;
  __IO uint32_t WDTCLKDIV;  //0xb4
  __IO uint32_t OUTCLKDIV;  //0xb8
  __IO uint32_t USBCLKDIV;  //0xbc
  __IO uint32_t ADCCLKDIV;  //0xC0
  uint32_t RESERVED91[3];
  __IO uint32_t PWMCLKDIV;  //0xD0
  uint32_t RESERVED13[11];
  __IO uint32_t ANASTATUS;//0x100
  uint32_t RESERVED32[3];
  __IO uint32_t PIOPORCAP0;//0x110
  uint32_t RESERVED35[3];
  __IO uint32_t SYSTICKCAL;//0x120
  uint32_t RESERVED38[3];
  __IO uint32_t BODCTRL;//0x130
  uint32_t RESERVED41[19];
  __IO uint32_t STARTAPRP0;//0x180
  __IO uint32_t STARTERP0;
  __IO uint32_t STARTRSRP0;
  __IO uint32_t STARTSRP0;
  uint32_t RESERVED60[28];
  __IO uint32_t PDSLEEPCFG;//0x200
  __IO uint32_t PDAWAKECFG;
  __IO uint32_t PDRUNCFG;
  uint32_t RESERVED88[5];
  __IO uint32_t DEVICEID;//0x220
  uint32_t RESERVED93[3];
  __IO uint32_t DMA_CH_SEL;//0x230
  uint32_t RESERVED96[19];
  __IO uint32_t PCON; //0x280
  uint32_t RESERVED114[3];
  __IO uint32_t RTC_ANA_CTRL; //0x290
  uint32_t RESERVED117[35];
  __IO uint32_t PRNG_DATA; //0x320
  __IO uint32_t PRNG_STATUS; //0x324
  __IO uint32_t PRNG_DEBUG_EN; //0x328
  __IO uint32_t PRNG_DEBUG_SEED; //0x32c
  __IO uint32_t DEBUG_MODE; //0x330
  __IO uint32_t ADDRESS_REMAP1;	//0x334
} RCC_TypeDef;


/** 
  * @brief General Purpose I/O
  */

typedef struct
{
  __IO uint32_t DT;
  __IO uint32_t DT_SET;
  __IO uint32_t DT_CLR;
  __IO uint32_t DT_TOG;
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t DIR;
  __IO uint32_t DIR_SET;
  __IO uint32_t DIR_CLR;
  __IO uint32_t DIR_TOG;
  __IO uint32_t IS;
  __IO uint32_t IS_SET;
  __IO uint32_t IS_CLR;
  __IO uint32_t IS_TOG;
  __IO uint32_t IBE;
  __IO uint32_t IBE_SET;
  __IO uint32_t IBE_CLR;
  __IO uint32_t IBE_TOG;
  __IO uint32_t IEV;
  __IO uint32_t IEV_SET;
  __IO uint32_t IEV_CLR;
  __IO uint32_t IEV_TOG;
  __IO uint32_t IE;
  __IO uint32_t IE_SET;
  __IO uint32_t IE_CLR;
  __IO uint32_t IE_TOG;
  __IO uint32_t IRS;
  __IO uint32_t IRS_SET;
  __IO uint32_t IRS_CLR;
  __IO uint32_t IRS_TOG;
  __IO uint32_t MIS;
  __IO uint32_t MIS_SET;
  __IO uint32_t MIS_CLR;
  __IO uint32_t MIS_TOG;
  __IO uint32_t IC;
  __IO uint32_t IC_SET;
  __IO uint32_t IC_CLR;
  __IO uint32_t IC_TOG;
  __IO uint32_t DATAMASK;
  __IO uint32_t DATAMASK_SET;
  __IO uint32_t DATAMASK_CLR;
  __IO uint32_t DATAMASK_TOG;
} GPIO_IT_TypeDef;

typedef struct
{				
  __IO uint32_t CON; 	
}IOCON_TypeDef;

typedef struct{
  __IO uint32_t ANA_ADJ;        //0x00
  __IO uint32_t SN;             //0x04
  __IO uint32_t RESERVE[62];        
  __IO uint32_t STATUS;         //0x100
}OTP_TypeDef;
/**
  * @brief ADC Interface
  */
typedef struct
{
  __IO uint32_t CTRL0;           //0X00
  __IO uint32_t CTRL0_SET;       //0X04
  __IO uint32_t CTRL0_CLR;       //0X08
  __IO uint32_t CTRL0_TOG;       //0X0C
  __IO uint32_t CTRL1;           //0X10
  __IO uint32_t CTRL1_SET;       //0X14
  __IO uint32_t CTRL1_CLR;       //0X18
  __IO uint32_t CTRL1_TOG;       //0X1C
  __IO uint32_t RESERVE0;        //0X20
  __IO uint32_t RESERVE1;        //0X24
  __IO uint32_t RESERVE2;        //0X28
  __IO uint32_t RESERVE3;        //0X2C
  __IO uint32_t CTRL3;           //0X30
  __IO uint32_t CTRL3_SET;       //0X34
  __IO uint32_t CTRL3_CLR;       //0X38
  __IO uint32_t CTRL3_TOG;       //0X3C
  __IO uint32_t STATUS;          //0X40
  __IO uint32_t STATUS_SET;   //0X44
  __IO uint32_t STATUS_CLR;   //0X48
  __IO uint32_t STATUS_TOG;   //0X4C
  __IO uint32_t CH0;          //0X50
  __IO uint32_t CH0_SET;       //0X54
  __IO uint32_t CH0_CLR;       //0X58
  __IO uint32_t CH0_TOG;       //0X5C
  __IO uint32_t CH1;          //0X60
  __IO uint32_t CH1_SET;       //0X64
  __IO uint32_t CH1_CLR;       //0X68
  __IO uint32_t CH1_TOG;       //0X6C
  __IO uint32_t CH2;          //0X70
  __IO uint32_t CH2_SET;       //0X74
  __IO uint32_t CH2_CLR;       //0X78
  __IO uint32_t CH2_TOG;       //0X7C
  __IO uint32_t CH3;          //0X80
  __IO uint32_t CH3_SET;       //0X84
  __IO uint32_t CH3_CLR;       //0X88
  __IO uint32_t CH3_TOG;       //0X8C
  __IO uint32_t CH4;          //0X90
  __IO uint32_t CH4_SET;       //0X94
  __IO uint32_t CH4_CLR;       //0X98
  __IO uint32_t CH4_TOG;       //0X9C
  __IO uint32_t CH5;          //0XA0
  __IO uint32_t CH5_SET;       //0XA4
  __IO uint32_t CH5_CLR;       //0XA8
  __IO uint32_t CH5_TOG;       //0XAC
  __IO uint32_t CH6;          //0XB0
  __IO uint32_t CH6_SET;       //0XB4
  __IO uint32_t CH6_CLR;       //0XB8
  __IO uint32_t CH6_TOG;       //0XBC
  __IO uint32_t CH7;          //0XC0
  __IO uint32_t CH7_SET;       //0XC4
  __IO uint32_t CH7_CLR;       //0XC8
  __IO uint32_t CH7_TOG;       //0XCC
  __IO uint32_t RESERVE_D0;       //0XD0
  __IO uint32_t RESERVE_D4;       //0XD4
  __IO uint32_t RESERVE_D8;       //0XD8
  __IO uint32_t RESERVE_DC;       //0XDC
  __IO uint32_t RESERVE_E0;       //0XE0
  __IO uint32_t RESERVE_E4;       //0XE4
  __IO uint32_t RESERVE_E8;       //0XE8
  __IO uint32_t RESERVE_EC;       //0XEC
  __IO uint32_t RESERVE_F0;       //0XF0
  __IO uint32_t RESERVE_F4;       //0XF4
  __IO uint32_t RESERVE_F8;       //0XF8
  __IO uint32_t RESERVE_FC;       //0XFC
  __IO uint32_t RESERVE_100;       //0X100
  __IO uint32_t RESERVE_104;       //0X104
  __IO uint32_t RESERVE_108;       //0X108
  __IO uint32_t RESERVE_10C;       //0X10C
  __IO uint32_t DEBUG0;          //0X110
  __IO uint32_t DEBUG0_SET;       //0X114
  __IO uint32_t DEBUG0_CLR;       //0X118
  __IO uint32_t DEBUG0_TOG;       //0X11C
  __IO uint32_t DEBUG1;          //0X120
  __IO uint32_t DEBUG1_SET;       //0X124
  __IO uint32_t DEBUG1_CLR;       //0X128
  __IO uint32_t DEBUG1_TOG;       //0X12C
  __IO uint32_t CONVERSION;          //0x130
  __IO uint32_t CONVERSION_SET;      //0x134
  __IO uint32_t CONVERSION_CLR;      //0x138
  __IO uint32_t CONVERSION_TOG;      //0x13C
  __IO uint32_t RESERVE4;         //0x140
  __IO uint32_t RESERVE5;         //0x144
  __IO uint32_t RESERVE6;         //0x148
  __IO uint32_t RESERVE7;         //0x14C
  __IO uint32_t RESERVE8;         //0x150
  __IO uint32_t RESERVE9;         //0x154
  __IO uint32_t RESERVE10;        //0x158
  __IO uint32_t RESERVE11;        //0x15C
  __IO uint32_t CTRL5;            //0x160
  __IO uint32_t CTRL5_SET;        //0x164
  __IO uint32_t CTRL5_CLR;        //0x168
  __IO uint32_t CTRL5_TOG;        //0x16C
  __IO uint32_t CH8;
  __IO uint32_t CH8_SET;
  __IO uint32_t CH8_CLR;
  __IO uint32_t CH8_TOG;
  __IO uint32_t CH9;
  __IO uint32_t CH9_SET;
  __IO uint32_t CH9_CLR;
  __IO uint32_t CH9_TOG;
}ADC_TypeDef;

/** 
  * @brief Direct Memory Access Interface
  */
typedef struct
{
  __IO uint32_t SAR0;               //0x000
  uint32_t RESERVED1;          //0x004
  __IO uint32_t DAR0;               //0x008
  uint32_t RESERVED2;          //0x00c
  __IO uint32_t LLP0;              //0x010
  uint32_t RESERVED3;         //0x014
  __IO uint32_t CTL0_L;            //0x018
  __IO uint32_t CTL0_H;            //0x01c
  __IO uint32_t SSTAT0;            //0x020
  uint32_t RESERVED4;         //0x024
  __IO uint32_t DSTAT0;            //0x028
  uint32_t RESERVED5;         //0x02c	
  __IO uint32_t SSTATAR0;         //0x030
  uint32_t RESERVED6;         //0x034
  __IO uint32_t DSTATAR0;         //0x038
  uint32_t RESERVED7;         //0x03c
  __IO uint32_t CFG0_L;           //0x040
  __IO uint32_t CFG0_H;           //0x044
  __IO uint32_t SGR0;              //0x048
  uint32_t RESERVED8;         //0x04c
  __IO uint32_t DSR0;              //0x050
  uint32_t RESERVED9;         //0x054
  __IO uint32_t SAR1;               //0x058
  uint32_t RESERVED10;          //0x05c
  __IO uint32_t DAR1;               //0x060
  uint32_t RESERVED11;          //0x064
  __IO uint32_t LLP1;              //0x068
  uint32_t RESERVED12;         //0x06c
  __IO uint32_t CTL1_L;            //0x070
  __IO uint32_t CTL1_H;            //0x074
  __IO uint32_t SSTAT1;            //0x078
  uint32_t RESERVED13;         //0x07c
  __IO uint32_t DSTAT1;            //0x080
  uint32_t RESERVED14;         //0x084	
  __IO uint32_t SSTATAR1;         //0x088
  uint32_t RESERVED15;         //0x08c
  __IO uint32_t DSTATAR1;         //0x090
  uint32_t RESERVED16;         //0x094
  __IO uint32_t CFG1_L;           //0x098
  __IO uint32_t CFG1_H;           //0x09c
  __IO uint32_t SGR1;              //0x0a0
  uint32_t RESERVED17;         //0x0a4
  __IO uint32_t DSR1;              //0x0a8
  uint32_t RESERVED18;         //0x0ac
  __IO uint32_t SAR2;               //0x0b0
  uint32_t RESERVED19;          //0x0b4
  __IO uint32_t DAR2;               //0x0b8
  uint32_t RESERVED20;          //0x0bc
  __IO uint32_t LLP2;              //0x0c0
  uint32_t RESERVED21;         //0x0c4
  __IO uint32_t CTL2_L;            //0x0c8
  __IO uint32_t CTL2_H;            //0x0cc
  __IO uint32_t SSTAT2;            //0x0d0
  uint32_t RESERVED22;         //0x0d4
  __IO uint32_t DSTAT2;            //0x0d8
  uint32_t RESERVED23;         //0x0dc	
  __IO uint32_t SSTATAR2;         //0x0e0
  uint32_t RESERVED24;         //0x0e4
  __IO uint32_t DSTATAR2;         //0x0e8
  uint32_t RESERVED25;         //0x0ec
  __IO uint32_t CFG2_L;           //0x0f0
  __IO uint32_t CFG2_H;           //0x0f4
  __IO uint32_t SGR2;              //0x0f8
  uint32_t RESERVED26;         //0x0fc
  __IO uint32_t DSR2;              //0x100
  uint32_t RESERVED27;         //0x104	
  __IO uint32_t SAR3;               //0x108
  uint32_t RESERVED28;          //0x10c
  __IO uint32_t DAR3;               //0x110
  uint32_t RESERVED29;          //0x114
  __IO uint32_t LLP3;              //0x118
  uint32_t RESERVED30;         //0x11c
  __IO uint32_t CTL3_L;            //0x120
  __IO uint32_t CTL3_H;            //0x124
  __IO uint32_t SSTAT;            //0x128
  uint32_t RESERVED31;         //0x12c
  __IO uint32_t DSTAT;            //0x130
  uint32_t RESERVED32;         //0x134	
  __IO uint32_t SSTATAR3;         //0x138
  uint32_t RESERVED33;         //0x13c
  __IO uint32_t DSTATAR3;         //0x140
  uint32_t RESERVED34;         //0x144
  __IO uint32_t CFG3_L;           //0x148
  __IO uint32_t CFG3_H;           //0x14c
  __IO uint32_t SGR3;              //0x150
  uint32_t RESERVED35;         //0x154
  __IO uint32_t DSR3;              //0x158
  uint32_t RESERVED36;         //0x15c
  __IO uint32_t SAR4;               //0x160
  uint32_t RESERVED37;          //0x164
  __IO uint32_t DAR4;               //0x168
  uint32_t RESERVED38;          //0x16c
  __IO uint32_t LLP4;              //0x170
  uint32_t RESERVED39;         //0x174
  __IO uint32_t CTL4_L;            //0x178
  __IO uint32_t CTL4_H;            //0x17c
  __IO uint32_t SSTAT4;            //0x180
  uint32_t RESERVED40;         //0x184
  __IO uint32_t DSTAT4;            //0x188
  uint32_t RESERVED41;         //0x18c	
  __IO uint32_t SSTATAR4;         //0x190
  uint32_t RESERVED42;         //0x194
  __IO uint32_t DSTATAR4;         //0x198
  uint32_t RESERVED43;         //0x19c
  __IO uint32_t CFG4_L;           //0x1a0
  __IO uint32_t CFG4_H;           //0x1a4
  __IO uint32_t SGR4;              //0x1a8
  uint32_t RESERVED44;         //0x1ac
  __IO uint32_t DSR4;              //0x1b0
  uint32_t RESERVED45;         //0x1b4	
  __IO uint32_t SAR5;               //0x1b8
  uint32_t RESERVED46;          //0x1bc
  __IO uint32_t DAR5;               //0x1c0
  uint32_t RESERVED47;          //0x1c4
  __IO uint32_t LLP5;              //0x1c8
  uint32_t RESERVED48;         //0x1cc
  __IO uint32_t CTL5_L;            //0x1d0
  __IO uint32_t CTL5_H;            //0x1d4
  __IO uint32_t SSTAT5;            //0x1d8
  uint32_t RESERVED49;         //0x1dc
  __IO uint32_t DSTAT5;            //0x1e0
  uint32_t RESERVED50;         //0x1e4	
  __IO uint32_t SSTATAR5;         //0x1e8
  uint32_t RESERVED51;         //0x1ec
  __IO uint32_t DSTATAR5;         //0x1f0
  uint32_t RESERVED52;         //0x1f4
  __IO uint32_t CFG5_L;           //0x1f8
  __IO uint32_t CFG5_H;           //0x1fc
  __IO uint32_t SGR5;              //0x200
  uint32_t RESERVED53;         //0x204
  __IO uint32_t DSR5;              //0x208
  uint32_t RESERVED54;         //0x20c	
  __IO uint32_t SAR6;               //0x210
  uint32_t RESERVED55;          //0x214
  __IO uint32_t DAR6;               //0x218
  uint32_t RESERVED56;          //0x21c
  __IO uint32_t LLP6;              //0x220
  uint32_t RESERVED57;         //0x224
  __IO uint32_t CTL6_L;            //0x228
  __IO uint32_t CTL6_H;            //0x22c
  __IO uint32_t SSTAT6;            //0x230
  uint32_t RESERVED58;         //0x234
  __IO uint32_t DSTAT6;            //0x238
  uint32_t RESERVED59;         //0x23c	
  __IO uint32_t SSTATAR6;         //0x240
  uint32_t RESERVED60;         //0x244
  __IO uint32_t DSTATAR6;         //0x248
  uint32_t RESERVED61;         //0x24c
  __IO uint32_t CFG6_L;           //0x250
  __IO uint32_t CFG6_H;           //0x254
  __IO uint32_t SGR6;              //0x258
  uint32_t RESERVED62;         //0x25c
  __IO uint32_t DSR6;              //0x260
  uint32_t RESERVED63;         //0x264	
  __IO uint32_t SAR7;               //0x268
  uint32_t RESERVED64;          //0x26c
  __IO uint32_t DAR7;               //0x270
  uint32_t RESERVED65;          //0x274
  __IO uint32_t LLP7;              //0x278
  uint32_t RESERVED66;         //0x27c
  __IO uint32_t CTL7_L;            //0x280
  __IO uint32_t CTL7_H;            //0x284
  __IO uint32_t SSTAT7;            //0x288
  uint32_t RESERVED67;         //0x28c
  __IO uint32_t DSTAT7;            //0x290
  uint32_t RESERVED68;         //0x294	
  __IO uint32_t SSTATAR7;         //0x298
  uint32_t RESERVED69;         //0x29c
  __IO uint32_t DSTATAR7;         //0x2a0
  uint32_t RESERVED70;         //0x2a4
  __IO uint32_t CFG7_L;           //0x2a8
  __IO uint32_t CFG7_H;           //0x2ac
  __IO uint32_t SGR7;              //0x2b0
  uint32_t RESERVED71;         //0x2b4
  __IO uint32_t DSR7;              //0x2b8
  uint32_t RESERVED72;         //0x2bc	
  __IO uint32_t RawTfr;           //0x2c0
  uint32_t RESERVED73;         //0x2c4
  __IO uint32_t RawBlock;         //0x2c8
  uint32_t RESERVED74;         //0x2cc
  __IO uint32_t RawSrcTran;       //0x2d0
  uint32_t RESERVED75;         //0x2d4
  __IO uint32_t RawDstTran;       //0x2d8
  uint32_t RESERVED76;         //0x2dc
  __IO uint32_t RawErr;           //0x2e0
  uint32_t RESERVED77;         //0x2e4
  __IO uint32_t StatusTfr;        //0x2e8
  uint32_t RESERVED78;         //0x2ec
  __IO uint32_t StatusBlock;      //0x2f0
  uint32_t RESERVED79;         //0x2f4
  __IO uint32_t StatusSrcTran;    //0x2f8
  uint32_t RESERVED80;         //0x2fc
  __IO uint32_t StatusDstTran;    //0x300
  uint32_t RESERVED81;         //0x304
  __IO uint32_t StatusErr;        //0x308  
  uint32_t RESERVED811;     //0x30c
  __IO uint32_t MaskTfr;           //0x310
  uint32_t RESERVED82;         //0x314
  __IO uint32_t MaskBlock;         //0x318
  uint32_t RESERVED83;         //0x31c
  __IO uint32_t MaskSrcTran;       //0x320
  uint32_t RESERVED84;         //0x324
  __IO uint32_t MaskDstTran;       //0x328
  uint32_t RESERVED85;         //0x32c
  __IO uint32_t MaskErr;           //0x330
  uint32_t RESERVED86;         //0x334	
  __IO uint32_t ClearTfr;        //0x338
  uint32_t RESERVED87;         //0x33c
  __IO uint32_t ClearBlock;      //0x340
  uint32_t RESERVED88;         //0x344
  __IO uint32_t ClearSrcTran;    //0x348
  uint32_t RESERVED89;         //0x34c
  __IO uint32_t ClearDstTran;    //0x350
  uint32_t RESERVED90;         //0x354
  __IO uint32_t ClearErr;        //0x358   
  uint32_t RESERVED91;         //0x35c  
  __IO uint32_t StatusInt;        //0x360
  uint32_t RESERVED92;         //0x364
  __IO uint32_t ReqSrcReg;        //0x368
  uint32_t RESERVED93;         //0x36c
  __IO uint32_t ReqDstReg;        //0x370
  uint32_t RESERVED94;         //0x374
  __IO uint32_t SglReqSrcReg;    //0x378
  uint32_t RESERVED95;       //0x37c
  __IO uint32_t SglReqDstReg;     //0x380
  uint32_t RESERVED96;       //0x384
  __IO uint32_t LstSrcReg;        //0x388
  uint32_t RESERVED97;       //0x38c    
  __IO uint32_t LstDstReg;        //0x390
  uint32_t RESERVED98;       //0x394
  __IO uint32_t DmaCfgReg;        //0x398
  uint32_t RESERVED99;       //0x39c    
  __IO uint32_t ChEnReg;          //0x3a0
  uint32_t RESERVED100;      //0x3a4
}DMA_TypeDef;

typedef struct
{
  __IO uint32_t SAR;               //0x000
  uint32_t RESERVED1;          //0x004
  __IO uint32_t DAR;               //0x008
  uint32_t RESERVED2;          //0x00c
  __IO uint32_t LLP;              //0x010
  uint32_t RESERVED3;         //0x014
  __IO uint32_t CTL_L;            //0x018
  __IO uint32_t CTL_H;            //0x01c
  __IO uint32_t SSTAT;            //0x020
  uint32_t RESERVED4;         //0x024
  __IO uint32_t DSTAT;            //0x028
  uint32_t RESERVED5;         //0x02c	
  __IO uint32_t SSTATAR;         //0x030
  uint32_t RESERVED6;         //0x034
  __IO uint32_t DSTATAR;         //0x038
  uint32_t RESERVED7;         //0x03c
  __IO uint32_t CFG_L;           //0x040
  __IO uint32_t CFG_H;           //0x044
  __IO uint32_t SGR;              //0x048
  uint32_t RESERVED8;         //0x04c
  __IO uint32_t DSR;              //0x050
  uint32_t RESERVED9;         //0x054
}DMAChannel_TypeDef;

/** 
  * @brief IOCON Interface
  */
typedef struct
{
  __IO uint32_t PIN0;
  __IO uint32_t PIN1;
  __IO uint32_t PIN2;
  __IO uint32_t PIN3;
  __IO uint32_t PIN4;
  __IO uint32_t PIN5;
  __IO uint32_t PIN6;
  __IO uint32_t PIN7;
  __IO uint32_t PIN8;
  __IO uint32_t PIN9;
  __IO uint32_t PIN10;
  __IO uint32_t PIN11;
  __IO uint32_t PIN12;
  __IO uint32_t PIN13;
  __IO uint32_t PIN14;
  __IO uint32_t PIN15;
  __IO uint32_t PIN16;
  __IO uint32_t PIN17;
  __IO uint32_t PIN18;
  __IO uint32_t PIN19;
  __IO uint32_t PIN20;
  __IO uint32_t PIN21;
  __IO uint32_t PIN22;
  __IO uint32_t PIN23;
  __IO uint32_t PIN24;
  __IO uint32_t PIN25;
  __IO uint32_t PIN26;
  __IO uint32_t PIN27;
  __IO uint32_t PIN28;
  __IO uint32_t PIN29;
  __IO uint32_t PIN30;
  __IO uint32_t PIN31;
}PIO_TypeDef;

/** 
  * @brief QSPI Interface
  */
typedef struct
{
  __IO uint32_t CTRL0;
  __IO uint32_t CTRL0_SET;
  __IO uint32_t CTRL0_CLR;
  __IO uint32_t CTRL0_TOG;
  __IO uint32_t CTRL1;
  __IO uint32_t CTRL1_SET;
  __IO uint32_t CTRL1_CLR;
  __IO uint32_t CTRL1_TOG;
  __IO uint32_t CMD;
  uint32_t RESERVED0[3];
  __IO uint32_t TIMING;
  uint32_t RESERVED1[3];
  __IO uint32_t DATA;
  uint32_t RESERVED2[3];
  __IO uint32_t STATUS;
  uint32_t RESERVED3[3];
  __IO uint32_t DEBUG;
  uint32_t RESERVED4[3];
  __IO uint32_t XFER;
  uint32_t RESERVED5[3];
  __IO uint32_t CTRL2;
  uint32_t RESERVED6[3];
  __IO uint32_t DUMMY;
  uint32_t	RESERVED7[3];          
  __IO uint32_t START_ADDR;
  uint32_t	RESERVED8[3];          
  __IO uint32_t XIP_READ_CMD;
  uint32_t	RESERVED9[3];          
  __IO uint32_t ADD_BYTE_LEN;
  uint32_t	RESERVED10[3];          
  __IO uint32_t BUSY_DLY;
  uint32_t	RESERVED11[3];          
}QSPI_TypeDef;

/** 
  * @brief TIM Interface
  */
typedef struct
{
  __IO uint32_t CR1;
  //  uint16_t  RESERVED0;
  __IO uint16_t CR2;
  uint16_t RESERVED1;
  __IO uint16_t SMCR;
  uint16_t RESERVED2;
  __IO uint16_t DIER;
  uint16_t RESERVED3;
  __IO uint16_t SR;
  uint16_t RESERVED4;
  __IO uint16_t EGR;
  uint16_t RESERVED5;
  __IO uint16_t CCMR1;
  uint16_t RESERVED6;
  __IO uint16_t CCMR2;
  uint16_t RESERVED7;
  __IO uint16_t CCER;
  uint16_t RESERVED8;
  __IO uint16_t CNT;
  uint16_t RESERVED9;
  __IO uint16_t PSC;
  uint16_t RESERVED10;
  __IO uint16_t ARR;
  uint16_t RESERVED11;
  __IO uint16_t RCR;
  uint16_t RESERVED12;
  __IO uint16_t CCR1;
  uint16_t RESERVED13;
  __IO uint16_t CCR2;
  uint16_t RESERVED14;
  __IO uint16_t CCR3;
  uint16_t RESERVED15;
  __IO uint16_t CCR4;
  uint16_t RESERVED16;
  __IO uint16_t BDTR;
  uint16_t RESERVED17;
  __IO uint16_t DCR;
  uint16_t RESERVED18;
  __IO uint16_t DMAR;
  uint16_t RESERVED19;
  __IO uint32_t CP;
} TIM_TypeDef;

/** 
  * @brief RTC Interface
  */
typedef struct
{
  __IO uint32_t CTRL;
  __IO uint32_t LOAD;
  __IO uint32_t CNT;
  __IO uint32_t ALARM;
  __IO uint32_t STAT;
} RTC_TypeDef;


typedef struct
{
  __IO uint32_t CONTROL;         //00
  __IO uint32_t STATUS;          //04
  __IO uint32_t PIC0_CTRL;       //08
  __IO uint32_t PIC0_ADR;        //0C
  __IO uint32_t PIC1_CTRL;       //10
  __IO uint32_t PIC1_ADR;        //14
  __IO uint32_t ROW;             //18
  __IO uint32_t COL_CLK;         //1C
  __IO uint32_t DELAY0;          //20
  __IO uint32_t DELAY1;          //24
  __IO uint32_t PWM_CTRL;        //28
  __IO uint32_t GL_PWM_CTRL[12]; //2C~58
  __IO uint32_t SCAN_GREY[9];    //5C~7C
  __IO uint32_t SCAN_NUM;		     //80
  __IO uint32_t TBL_CFG;    //84
  __IO uint32_t SW_Rreg;    //88
  uint32_t RESERVED[5];          //88~9C
  __IO uint32_t GP[16];          //A0~DC
  uint32_t RESERVED1[8];         //E0~FC
  __IO uint32_t R_REG[32];       //100~17C
  __IO uint32_t C_REG[16];       //180~1BC
}LED_TypeDef;

typedef struct
{
  __IO uint32_t CONTROL;         //00
  __IO uint32_t STATUS;          //04
  __IO uint32_t CB_START;        //08
  __IO uint32_t CB_END;          //0C
  __IO uint32_t BASE_ADDR;       //10
  __IO uint32_t TIMER;           //14
  __IO uint32_t CUR_CMD;          //18
}BITCOPY_TypeDef;

typedef struct
{
  __IO uint32_t CTRL0;
  __IO uint32_t CTRL0_SET;
  __IO uint32_t CTRL0_CLR;
  __IO uint32_t CTRL0_TOG;
  __IO uint32_t CTRL1;
  __IO uint32_t CTRL1_SET;
  __IO uint32_t CTRL1_CLR;
  __IO uint32_t CTRL1_TOG;
  __IO uint32_t STATUS;
  __IO uint32_t STATUS_SET;
  __IO uint32_t STATUS_CLR;
  __IO uint32_t STATUS_TOG;
}CMP_TypeDef;
/**
  * @}
  */
  /** @addtogroup Peripheral_memory_map
  * @{
  */
/*!< Peripheral memory map */
#define PERIPH_BASE                         ((uint32_t)0x40000000)   /*!< Peripheral base address in the alias region */
#define APB0PERIPH_BASE                     (PERIPH_BASE)

#define UART0_BASE                          (APB0PERIPH_BASE + 0x2000)
#define UART1_BASE                          (APB0PERIPH_BASE + 0x3000)
#define UART2_BASE                          (APB0PERIPH_BASE + 0x6000)

#define OTP_BASE                            (APB0PERIPH_BASE + 0x5000)

#define ADC0_BASE                           (APB0PERIPH_BASE + 0x8000)

#define CMP_BASE                            (APB0PERIPH_BASE + 0x9000)

#define DMA_BASE                            (APB0PERIPH_BASE + 0x50000)	

#define RCC_BASE                            (APB0PERIPH_BASE)

#define GPIO_BASE                           (APB0PERIPH_BASE + 0x20000)
#define GPIO0_BASE                          (GPIO_BASE)
#define GPIO0_IT_BASE                       (GPIO_BASE + 0x8000)
#define GPIO1_BASE                          (GPIO_BASE + 0x10000)
#define GPIO1_IT_BASE                       (GPIO_BASE + 0x18000)

#define QSPI0_BASE                          (APB0PERIPH_BASE + 0x10000)
#define QSPI1_BASE                          (APB0PERIPH_BASE + 0x11000)
#define QSPI2_BASE                          (APB0PERIPH_BASE + 0x12000)

#define WKT_BASE                            (APB0PERIPH_BASE + 0xC800)

#define IOCON_BASE                          (PERIPH_BASE + 0x1000)
#define IOCON_PIO0_BASE                     (IOCON_BASE)
#define IOCON_PIO1_BASE                     (IOCON_BASE + 0x80)

#define TIM_BASE                            (PERIPH_BASE + 0xA000)
#define TIM1_BASE                           (TIM_BASE)
#define TIM4_BASE                           (TIM_BASE + 0x0800)
#define TIM15_BASE                          (TIM_BASE + 0x1000)
#define TIM16_BASE                          (TIM_BASE + 0x2000)
#define TIM17_BASE                          (TIM_BASE + 0x2800)

#define RTC_BASE                            (APB0PERIPH_BASE + 0xF000)

#define USB_BASE                            (PERIPH_BASE + 0x60000)

#define I2C0_BASE                           (APB0PERIPH_BASE + 0x4000)

#define LED_BASE                            (APB0PERIPH_BASE+0xD000)

#define BITCOPY_BASE                        (APB0PERIPH_BASE+0xD800)

#define HW_IOCON_SCKLOC	                    0x400012c0
/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  
#define UART0                               ((UART_TypeDef *) UART0_BASE)
#define UART1                               ((UART_TypeDef *) UART1_BASE)
#define UART2                               ((UART_TypeDef *) UART2_BASE)

#define PIO0                                ((PIO_TypeDef *) IOCON_PIO0_BASE)
#define PIO1                                ((PIO_TypeDef *) IOCON_PIO1_BASE)

#define RCC                                 ((RCC_TypeDef *) RCC_BASE)

#define GPIO0                               ((GPIO_TypeDef *) GPIO0_BASE)
#define GPIO1                               ((GPIO_TypeDef *) GPIO1_BASE)

#define OTP                                 ((OTP_TypeDef *) OTP_BASE)

#define ADC0                                ((ADC_TypeDef *) ADC0_BASE)

#define CMP                                 ((CMP_TypeDef*) CMP_BASE)

#define DMA                                 ((DMA_TypeDef *) DMA_BASE)
#define DMAChannel0                         ((DMAChannel_TypeDef *) DMA_BASE)
#define DMAChannel1                         ((DMAChannel_TypeDef *) (DMA_BASE+0x58))
#define DMAChannel2                         ((DMAChannel_TypeDef *) (DMA_BASE+0x58*2))
#define DMAChannel3                         ((DMAChannel_TypeDef *) (DMA_BASE+0x58*3))

#define GPIO0_IT                            ((GPIO_IT_TypeDef *) GPIO0_IT_BASE)
#define GPIO1_IT                            ((GPIO_IT_TypeDef *) GPIO1_IT_BASE)

#define WKT                                 ((WKT_TypeDef *) WKT_BASE)

#define TIM1                                ((TIM_TypeDef *) TIM1_BASE)
#define TIM4                                ((TIM_TypeDef *) TIM4_BASE)
#define TIM15                               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16                               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17                               ((TIM_TypeDef *) TIM17_BASE)

#define QSPI0                               ((QSPI_TypeDef *) QSPI0_BASE)
#define QSPI1                               ((QSPI_TypeDef *) QSPI1_BASE)
#define QSPI2                               ((QSPI_TypeDef *) QSPI2_BASE)

#define RTC                                 ((RTC_TypeDef *) RTC_BASE)

#define I2C0                                ((I2C_TypeDef *) I2C0_BASE)

#define LED                                 ((LED_TypeDef *) LED_BASE)

#define BITCOPY                             ((BITCOPY_TypeDef*) BITCOPY_BASE)

//#define USB0                                ((USB_TypeDef*)USB_BASE)

 /**
  * @}
  */ 


 /**
  * @}
  */ 

#ifdef USE_STDPERIPH_DRIVER
  #include "Y6_conf.h"
#endif

/******************************************************************************/
/*                                                                            */
/*         Universal Asynchronous Receiver Transmitter            			  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for HW_UARTAPP_CTRL0 register  *******************/
#define  UART_CTRL0_XFER_COUNT              ((uint32_t)0x0000FFFF)        /*!<Number of bytes to receive. */
#define  UART_CTRL0_RXTIMEOUT               ((uint32_t)0x00FF0000)        /*!<Receive Timeout Counter Value: */
#define  UART_CTRL0_RXTO_ENABLE             ((uint32_t)0x01000000)        /*!<RXTIMEOUT Enable */
#define  UART_CTRL0_RX_SOURCE               ((uint32_t)0x02000000)        /*!<Source of Receive Data */
#define  UART_CTRL0_RUN                     ((uint32_t)0x10000000)        /*!<Tell the UART to execute the RX DMA Command. */
#define  UART_CTRL0_CLKGATE                 ((uint32_t)0x40000000)        /*!<Gates of clock */
#define  UART_CTRL0_SFTRST                  ((uint32_t)0x80000000)        /*!<Set to zero for normal operation,set to one to reset entire block */

/*******************  Bit definition for HW_UARTAPP_CTRL1 register  *******************/
#define  UART_CTRL1_XFER_COUNT         	    ((uint32_t)0x0000FFFF)            /*!<Number of bytes to transmit. */
#define  UART_CTRL1_RUN                     ((uint32_t)0x10000000)            /*!<Tell the UART to execute the TX DMA Command. */

/******************  Bit definition for HW_UARTAPP_CTRL2 register  *******************/
#define  UART_CTRL2_UARTEN                  ((uint32_t)0x00000001)            /*!<UART Enable. */
#define  UART_CTRL2_SIREN                   ((uint32_t)0x00000002)            /*!<SIR Enable. */
#define  UART_CTRL2_SIRLP                   ((uint32_t)0x00000004)            /*!<IrDA SIR Low Power Mode. */
#define  UART_CTRL2_LBE                     ((uint32_t)0x00000080)            /*!<Loop Back Enable. */
#define  UART_CTRL2_TXE                     ((uint32_t)0x00000100)            /*!<Transmit Enable. */
#define  UART_CTRL2_RXE                     ((uint32_t)0x00000200)            /*!<Receive Enable. */
#define  UART_CTRL2_DTR                     ((uint32_t)0x00000400)            /*!<Data Transmit Ready.*/
#define  UART_CTRL2_RTS                     ((uint32_t)0x00000800)            /*!<Request To Send. */
#define  UART_CTRL2_OUT1                    ((uint32_t)0x00001000)            /*!<This bit is the complement of the UART Out1 (nUARTOut1) modem status output. */
#define  UART_CTRL2_OUT2                    ((uint32_t)0x00002000)            /*!<This bit is the complement of the UART Out2 (nUARTOut2) modem status output. */
#define  UART_CTRL2_RTSEN                   ((uint32_t)0x00004000)            /*!<RTS Hardware Flow Control Enable. */
#define  UART_CTRL2_CTSEN                   ((uint32_t)0x00008000)            /*!<CTS Hardware Flow Control Enable.*/
#define  UART_CTRL2_TXIFLSEL                ((uint32_t)0x000F0000)            /*!<Transmit Interrupt FIFO Level Select. */
#define  UART_CTRL2_TXIFLSEL_0              ((uint32_t)0x00010000)            /*!<Transmit Interrupt FIFO Level Select. */
#define  UART_CTRL2_TXIFLSEL_1              ((uint32_t)0x00020000)            /*!<Transmit Interrupt FIFO Level Select. */
#define  UART_CTRL2_TXIFLSEL_2              ((uint32_t)0x00040000)            /*!<Transmit Interrupt FIFO Level Select. */
#define  UART_CTRL2_RXIFLSEL                ((uint32_t)0x00F00000)            /*!<Receive Interrupt FIFO Level Select. */
#define  UART_CTRL2_RXIFLSEL_0              ((uint32_t)0x00100000)            /*!<Receive Interrupt FIFO Level Select. */
#define  UART_CTRL2_RXIFLSEL_1              ((uint32_t)0x00200000)            /*!<Receive Interrupt FIFO Level Select. */
#define  UART_CTRL2_RXIFLSEL_2              ((uint32_t)0x00400000)            /*!<Receive Interrupt FIFO Level Select. */
#define  UART_CTRL2_RXDMAE                  ((uint32_t)0x01000000)            /*!<Receive DMA Enable.*/
#define  UART_CTRL2_TXDMAE                  ((uint32_t)0x02000000)            /*!<Transmit DMA Enable. */
#define  UART_CTRL2_DMAONERROR              ((uint32_t)0x04000000)            /*!<DMA On Error. */

/******************  Bit definition for HW_UARTAPP_LINECTRL register  *******************/
#define  UART_LINECTRL_BRK                  ((uint32_t)0x00000001)            /*!<Send Break */
#define  UART_LINECTRL_PEN                  ((uint32_t)0x00000002)            /*!<Parity Enable. */
#define  UART_LINECTRL_EPS                  ((uint32_t)0x00000004)            /*!<Even Parity Select. */
#define  UART_LINECTRL_STP2                 ((uint32_t)0x00000008)            /*!<Even Parity Select. */
#define  UART_LINECTRL_FEN                  ((uint32_t)0x00000010)            /*!<Enable FIFOs. */
#define  UART_LINECTRL_WLEN                 ((uint32_t)0x00000060)            /*!<Word length [1:0]. */
#define  UART_LINECTRL_WLEN_0               ((uint32_t)0x00000020)            /*!<Word length [1:0]. */
#define  UART_LINECTRL_WLEN_1               ((uint32_t)0x00000040)            /*!<Word length [1:0]. */
#define  UART_LINECTRL_SPS                  ((uint32_t)0x00000080)            /*!<Stick Parity Select. */
#define  UART_LINECTRL_BAUD_DIVFRA          ((uint32_t)0x00003F00)            /*!<Baud Rate Fraction [5:0]. */
#define  UART_LINECTRL_BAUD_DIVINT          ((uint32_t)0xFFFF0000)            /*!<Baud Rate Integer [15:0]. */

/******************  Bit definition for HW_UARTAPP_INTR register  *******************/
#define  UART_INTR_RIMIS                    ((uint32_t)0x00000001)            /*!<nUARTRI Modem Interrupt Status. */
#define  UART_INTR_CTSMIS                   ((uint32_t)0x00000002)            /*!<nUARTCTS Modem Interrupt Status. */
#define  UART_INTR_DCDMIS                   ((uint32_t)0x00000004)            /*!<nUARTDCD Modem Interrupt Status. */
#define  UART_INTR_DSRMIS                   ((uint32_t)0x00000008)            /*!<nUARTDSR Modem Interrupt Status. */
#define  UART_INTR_RXIS                     ((uint32_t)0x00000010)            /*!<nUARTDSR Modem Interrupt Status. */
#define  UART_INTR_TXIS                     ((uint32_t)0x00000020)            /*!<Transmit Interrupt Status. */
#define  UART_INTR_RTIS                     ((uint32_t)0x00000040)            /*!<Receive Timeout Interrupt Status. */
#define  UART_INTR_FEIS                     ((uint32_t)0x00000080)            /*!<Framing Error Interrupt Status. */
#define  UART_INTR_PEIS                     ((uint32_t)0x00000100)            /*!<Parity Error Interrupt Status. */
#define  UART_INTR_BEIS                     ((uint32_t)0x00000200)            /*!<Break Error Interrupt Status. */
#define  UART_INTR_OEIS                	    ((uint32_t)0x00000400)            /*!<Break Error Interrupt Status. */
#define  UART_INTR_TFEIS                    ((uint32_t)0x00000800)            /*!<Tx FIFO EMPTY Raw Interrupt status*/
#define  UART_INTR_ABEO                     ((uint32_t)0x00001000)            /*!<Auto Buadrate End Interrupt Status. */
#define  UART_INTR_ABTO                     ((uint32_t)0x00002000)            /*!<Auto Buadrate TimeOut Interrupt Status. */
#define  UART_INTR_RIMIEN                   ((uint32_t)0x00010000)            /*!<nUARTRI Modem Interrupt Enable. */
#define  UART_INTR_CTSMIEN                  ((uint32_t)0x00020000)            /*!<nUARTCTS Modem Interrupt Enable.*/
#define  UART_INTR_DCDMIEN                  ((uint32_t)0x00040000)            /*!<nUARTDCD Modem Interrupt Enable. */
#define  UART_INTR_DSRMIEN                  ((uint32_t)0x00080000)            /*!<nUARTDSR Modem Interrupt Enable. */
#define  UART_INTR_RXIEN                    ((uint32_t)0x00100000)            /*!<Receive Interrupt Enable. */
#define  UART_INTR_TXIEN                    ((uint32_t)0x00200000)            /*!<Transmit Interrupt Enable. */
#define  UART_INTR_RTIEN                    ((uint32_t)0x00400000)            /*!<Receive Timeout Interrupt Enable. */
#define  UART_INTR_FEIEN                    ((uint32_t)0x00800000)            /*!<Framing Error Interrupt Enable.*/
#define  UART_INTR_PEIEN                    ((uint32_t)0x01000000)            /*!<Parity Error Interrupt Enable.*/
#define  UART_INTR_BEIEN                    ((uint32_t)0x02000000)            /*!<Break Error Interrupt Enable. */
#define  UART_INTR_OEIEN                    ((uint32_t)0x04000000)            /*!<Overrun Error Interrupt Enable. */
#define  UART_INTR_TFEIEN                   ((uint32_t)0x08000000)            /*!<Overrun Error Interrupt Enable.*/
#define  UART_INTR_ABEOEN                   ((uint32_t)0x10000000)            /*!<Auto Buadrate End Interrupt Enable.*/
#define  UART_INTR_ABTOEN                   ((uint32_t)0x20000000)            /*!<Auto Buadrate TimeOut Interrupt Enable.*/

/******************  Bit definition for HW_UARTAPP_DATA register  *******************/
#define  UART_DATA                          ((uint32_t)0xFFFFFFFF)            /*!<The status register contains the receive data flags and valid bits. */

/******************  Bit definition for HW_UARTAPP_STAT register  ******************/
#define  UART_STAT_RXCOUNT                  ((uint32_t)0x0000FFFF)            /*!<Number of bytes received during a Receive DMA command. */
#define  UART_STAT_FERR                     ((uint32_t)0x00010000)            /*!<Framing Error. */
#define  UART_STAT_PERR                     ((uint32_t)0x00020000)            /*!<Parity Error. */
#define  UART_STAT_BERR                     ((uint32_t)0x00040000)            /*!<Break Error. */
#define  UART_STAT_OERR                     ((uint32_t)0x00080000)            /*!<Overrun Error.*/
#define  UART_STAT_RXBYTE_INVALID           ((uint32_t)0x00F00000)            /*!<The invalid state of the last read of Receive Data. */
#define  UART_STAT_RXFE                     ((uint32_t)0x01000000)            /*!<Receive FIFO Empty. */
#define  UART_STAT_TXFF                     ((uint32_t)0x02000000)            /*!<Receive FIFO Empty. */
#define  UART_STAT_RXFF                     ((uint32_t)0x04000000)            /*!<Receive FIFO Full. */
#define  UART_STAT_TXFE                     ((uint32_t)0x08000000)            /*!<Transmit FIFO Empty. */
#define  UART_STAT_CTS                      ((uint32_t)0x10000000)            /*!<Clear To Send. */
#define  UART_STAT_BUSY                     ((uint32_t)0x20000000)            /*!<UART Busy. */
#define  UART_STAT_HISPEED                  ((uint32_t)0x40000000)            /*!<indicates that the high-speed function is present. */
#define  UART_STAT_PRESENT                  ((uint32_t)0x80000000)            /*!<indicates that the Application UART function is present. */

/******************  Bit definition for HW_UARTAPP_DEBUG register  ******************/
#define  UART_DEBUG_RXDMARQ                 ((uint32_t)0x00000001)            /*!<UART Receive DMA Request Status. */
#define  UART_DEBUG_TXDMARQ                 ((uint32_t)0x00000002)            /*!<UART Transmit DMA Request Status. */
#define  UART_DEBUG_RXCMDEND                ((uint32_t)0x00000004)            /*!<UART Receive DMA Command End Status. */
#define  UART_DEBUG_TXCMDEND                ((uint32_t)0x00000008)            /*!<UART Transmit DMA Command End Status. */
#define  UART_DEBUG_RXDMARUN                ((uint32_t)0x00000010)            /*!<UART Receive DMA Command Run Status. */
#define  UART_DEBUG_TXDMARUN                ((uint32_t)0x00000020)            /*!<UART Transmit DMA Command Run Status. */

/******************  Bit definition for HW_UARTAPP_ILPR register  ******************/
#define  UART_ILPDVSR                       ((uint32_t)0x000000FF)            /*!<The baud rate divisor of the IRDA_LowPower */

/******************  Bit definition for HW_UARTAPP_RS485CTRL register  ******************/
#define  UART_RS485CTRL_NMMEN               ((uint32_t)0x00000001)            /*!<Multidrop Mode. */
#define  UART_RS485CTRL_RXDIS               ((uint32_t)0x00000002)            /*!<Enable receiver. */
#define  UART_RS485CTRL_AADEN               ((uint32_t)0x00000004)            /*!<Auto Address Detect. */
#define  UART_RS485CTRL_SEL                 ((uint32_t)0x00000008)            /*!<Direction control select. */
#define  UART_RS485CTRL_DCTRL               ((uint32_t)0x00000010)            /*!<Auto Direction Control. */
#define  UART_RS485CTRL_ONIV                ((uint32_t)0x00000020)            /*!<reverses the polarity of the direction control signal. */

/******************  Bit definition for HW_UARTAPP_RS485ADRMATCH register  ******************/
#define  UART_ADRMATCH                      ((uint32_t)0x000000FF)            /*!<Contains the address match value. */

/******************  Bit definition for HW_UARTAPP_RS485DLY register  ******************/
#define  UART_DLY                           ((uint32_t)0x000000FF)            /*!<Contains the direction control (RTS or DTR) delay value. */

/******************  Bit definition for HW_UARTAPP_AUTOBAUD register  ******************/
#define  UART_AUTOBAUD_START                ((uint32_t)0x00000001)            /*!<Start auto baudrate. */
#define  UART_AUTOBAUD_MODE                 ((uint32_t)0x00000002)            /*!<Auto-baud mode select. */
#define  UART_AUTOBAUD_AUTORESTART          ((uint32_t)0x00000004)            /*!<Auto Restart. */
#define  UART_AUTOBAUD_ABEOIntClr           ((uint32_t)0x00000100)            /*!<End of auto-baud interrupt clear bit. */
#define  UART_AUTOBAUD_ABTOIntClr           ((uint32_t)0x00000200)            /*!<End of auto-baud interrupt clear bit. */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_DATA register  *******************/
#define GPIO_DATA_BIT0                        ((uint32_t)0x00000001)            /*!< Pin data, bit 0 */
#define GPIO_DATA_BIT1                        ((uint32_t)0x00000002)            /*!< Pin data, bit 1 */
#define GPIO_DATA_BIT2                        ((uint32_t)0x00000004)            /*!< Pin data, bit 2 */
#define GPIO_DATA_BIT3                        ((uint32_t)0x00000008)            /*!< Pin data, bit 3 */
#define GPIO_DATA_BIT4                        ((uint32_t)0x00000010)            /*!< Pin data, bit 4 */
#define GPIO_DATA_BIT5                        ((uint32_t)0x00000020)            /*!< Pin data, bit 5 */
#define GPIO_DATA_BIT6                        ((uint32_t)0x00000040)            /*!< Pin data, bit 6 */
#define GPIO_DATA_BIT7                        ((uint32_t)0x00000080)            /*!< Pin data, bit 7 */
#define GPIO_DATA_BIT8                        ((uint32_t)0x00000100)            /*!< Pin data, bit 8 */
#define GPIO_DATA_BIT9                        ((uint32_t)0x00000200)            /*!< Pin data, bit 9 */
#define GPIO_DATA_BIT10                       ((uint32_t)0x00000400)            /*!< Pin data, bit 10 */
#define GPIO_DATA_BIT11                       ((uint32_t)0x00000800)            /*!< Pin data, bit 11 */
#define GPIO_DATA_BIT12                       ((uint32_t)0x00001000)            /*!< Pin data, bit 12 */
#define GPIO_DATA_BIT13                       ((uint32_t)0x00002000)            /*!< Pin data, bit 13 */
#define GPIO_DATA_BIT14                       ((uint32_t)0x00004000)            /*!< Pin data, bit 14 */
#define GPIO_DATA_BIT15                       ((uint32_t)0x00008000)            /*!< Pin data, bit 15 */
#define GPIO_DATA_BIT16                       ((uint32_t)0x00010000)            /*!< Pin data, bit 16 */
#define GPIO_DATA_BIT17                       ((uint32_t)0x00020000)            /*!< Pin data, bit 17 */
#define GPIO_DATA_BIT18                       ((uint32_t)0x00040000)            /*!< Pin data, bit 18 */
#define GPIO_DATA_BIT19                       ((uint32_t)0x00080000)            /*!< Pin data, bit 19 */
#define GPIO_DATA_BIT20                       ((uint32_t)0x00100000)            /*!< Pin data, bit 20 */
#define GPIO_DATA_BIT21                       ((uint32_t)0x00200000)            /*!< Pin data, bit 21 */
#define GPIO_DATA_BIT22                       ((uint32_t)0x00400000)            /*!< Pin data, bit 22 */
#define GPIO_DATA_BIT23                       ((uint32_t)0x00800000)            /*!< Pin data, bit 23 */
#define GPIO_DATA_BIT24                       ((uint32_t)0x01000000)            /*!< Pin data, bit 24 */
#define GPIO_DATA_BIT25                       ((uint32_t)0x02000000)            /*!< Pin data, bit 25 */
#define GPIO_DATA_BIT26                       ((uint32_t)0x04000000)            /*!< Pin data, bit 26 */
#define GPIO_DATA_BIT27                       ((uint32_t)0x08000000)            /*!< Pin data, bit 27 */
#define GPIO_DATA_BIT28                       ((uint32_t)0x10000000)            /*!< Pin data, bit 28 */
#define GPIO_DATA_BIT29                       ((uint32_t)0x20000000)            /*!< Pin data, bit 29 */
#define GPIO_DATA_BIT30                       ((uint32_t)0x40000000)            /*!< Pin data, bit 30 */
#define GPIO_DATA_BIT31                       ((uint32_t)0x80000000)            /*!< Pin data, bit 31 */

/*******************  Bit definition for GPIO_DIR register  *******************/
#define GPIO_DIR_BIT0                        ((uint32_t)0x00000001)            /*!< Pin dir, bit 0 */
#define GPIO_DIR_BIT1                        ((uint32_t)0x00000002)            /*!< Pin dir, bit 1 */
#define GPIO_DIR_BIT2                        ((uint32_t)0x00000004)            /*!< Pin dir, bit 2 */
#define GPIO_DIR_BIT3                        ((uint32_t)0x00000008)            /*!< Pin dir, bit 3 */
#define GPIO_DIR_BIT4                        ((uint32_t)0x00000010)            /*!< Pin dir, bit 4 */
#define GPIO_DIR_BIT5                        ((uint32_t)0x00000020)            /*!< Pin dir, bit 5 */
#define GPIO_DIR_BIT6                        ((uint32_t)0x00000040)            /*!< Pin dir, bit 6 */
#define GPIO_DIR_BIT7                        ((uint32_t)0x00000080)            /*!< Pin dir, bit 7 */
#define GPIO_DIR_BIT8                        ((uint32_t)0x00000100)            /*!< Pin dir, bit 8 */
#define GPIO_DIR_BIT9                        ((uint32_t)0x00000200)            /*!< Pin dir, bit 9 */
#define GPIO_DIR_BIT10                       ((uint32_t)0x00000400)            /*!< Pin dir, bit 10 */
#define GPIO_DIR_BIT11                       ((uint32_t)0x00000800)            /*!< Pin dir, bit 11 */
#define GPIO_DIR_BIT12                       ((uint32_t)0x00001000)            /*!< Pin dir, bit 12 */
#define GPIO_DIR_BIT13                       ((uint32_t)0x00002000)            /*!< Pin dir, bit 13 */
#define GPIO_DIR_BIT14                       ((uint32_t)0x00004000)            /*!< Pin dir, bit 14 */
#define GPIO_DIR_BIT15                       ((uint32_t)0x00008000)            /*!< Pin dir, bit 15 */
#define GPIO_DIR_BIT16                       ((uint32_t)0x00010000)            /*!< Pin dir, bit 16 */
#define GPIO_DIR_BIT17                       ((uint32_t)0x00020000)            /*!< Pin dir, bit 17 */
#define GPIO_DIR_BIT18                       ((uint32_t)0x00040000)            /*!< Pin dir, bit 18 */
#define GPIO_DIR_BIT19                       ((uint32_t)0x00080000)            /*!< Pin dir, bit 19 */
#define GPIO_DIR_BIT20                       ((uint32_t)0x00100000)            /*!< Pin dir, bit 20 */
#define GPIO_DIR_BIT21                       ((uint32_t)0x00200000)            /*!< Pin dir, bit 21 */
#define GPIO_DIR_BIT22                       ((uint32_t)0x00400000)            /*!< Pin dir, bit 22 */
#define GPIO_DIR_BIT23                       ((uint32_t)0x00800000)            /*!< Pin dir, bit 23 */
#define GPIO_DIR_BIT24                       ((uint32_t)0x01000000)            /*!< Pin dir, bit 24 */
#define GPIO_DIR_BIT25                       ((uint32_t)0x02000000)            /*!< Pin dir, bit 25 */
#define GPIO_DIR_BIT26                       ((uint32_t)0x04000000)            /*!< Pin dir, bit 26 */
#define GPIO_DIR_BIT27                       ((uint32_t)0x08000000)            /*!< Pin dir, bit 27 */
#define GPIO_DIR_BIT28                       ((uint32_t)0x10000000)            /*!< Pin dir, bit 28 */
#define GPIO_DIR_BIT29                       ((uint32_t)0x20000000)            /*!< Pin dir, bit 29 */
#define GPIO_DIR_BIT30                       ((uint32_t)0x40000000)            /*!< Pin dir, bit 30 */
#define GPIO_DIR_BIT31                       ((uint32_t)0x80000000)            /*!< Pin dir, bit 31 */

/*******************  Bit definition for GPIO_IS register  *******************/
#define GPIO_IS_BIT0                        ((uint32_t)0x00000001)            /*!< Pin is, bit 0 */
#define GPIO_IS_BIT1                        ((uint32_t)0x00000002)            /*!< Pin is, bit 1 */
#define GPIO_IS_BIT2                        ((uint32_t)0x00000004)            /*!< Pin is, bit 2 */
#define GPIO_IS_BIT3                        ((uint32_t)0x00000008)            /*!< Pin is, bit 3 */
#define GPIO_IS_BIT4                        ((uint32_t)0x00000010)            /*!< Pin is, bit 4 */
#define GPIO_IS_BIT5                        ((uint32_t)0x00000020)            /*!< Pin is, bit 5 */
#define GPIO_IS_BIT6                        ((uint32_t)0x00000040)            /*!< Pin is, bit 6 */
#define GPIO_IS_BIT7                        ((uint32_t)0x00000080)            /*!< Pin is, bit 7 */
#define GPIO_IS_BIT8                        ((uint32_t)0x00000100)            /*!< Pin is, bit 8 */
#define GPIO_IS_BIT9                        ((uint32_t)0x00000200)            /*!< Pin is, bit 9 */
#define GPIO_IS_BIT10                       ((uint32_t)0x00000400)            /*!< Pin is, bit 10 */
#define GPIO_IS_BIT11                       ((uint32_t)0x00000800)            /*!< Pin is, bit 11 */
#define GPIO_IS_BIT12                       ((uint32_t)0x00001000)            /*!< Pin is, bit 12 */
#define GPIO_IS_BIT13                       ((uint32_t)0x00002000)            /*!< Pin is, bit 13 */
#define GPIO_IS_BIT14                       ((uint32_t)0x00004000)            /*!< Pin is, bit 14 */
#define GPIO_IS_BIT15                       ((uint32_t)0x00008000)            /*!< Pin is, bit 15 */
#define GPIO_IS_BIT16                       ((uint32_t)0x00010000)            /*!< Pin is, bit 16 */
#define GPIO_IS_BIT17                       ((uint32_t)0x00020000)            /*!< Pin is, bit 17 */
#define GPIO_IS_BIT18                       ((uint32_t)0x00040000)            /*!< Pin is, bit 18 */
#define GPIO_IS_BIT19                       ((uint32_t)0x00080000)            /*!< Pin is, bit 19 */
#define GPIO_IS_BIT20                       ((uint32_t)0x00100000)            /*!< Pin is, bit 20 */
#define GPIO_IS_BIT21                       ((uint32_t)0x00200000)            /*!< Pin is, bit 21 */
#define GPIO_IS_BIT22                       ((uint32_t)0x00400000)            /*!< Pin is, bit 22 */
#define GPIO_IS_BIT23                       ((uint32_t)0x00800000)            /*!< Pin is, bit 23 */
#define GPIO_IS_BIT24                       ((uint32_t)0x01000000)            /*!< Pin is, bit 24 */
#define GPIO_IS_BIT25                       ((uint32_t)0x02000000)            /*!< Pin is, bit 25 */
#define GPIO_IS_BIT26                       ((uint32_t)0x04000000)            /*!< Pin is, bit 26 */
#define GPIO_IS_BIT27                       ((uint32_t)0x08000000)            /*!< Pin is, bit 27 */
#define GPIO_IS_BIT28                       ((uint32_t)0x10000000)            /*!< Pin is, bit 28 */
#define GPIO_IS_BIT29                       ((uint32_t)0x20000000)            /*!< Pin is, bit 29 */
#define GPIO_IS_BIT30                       ((uint32_t)0x40000000)            /*!< Pin is, bit 30 */
#define GPIO_IS_BIT31                       ((uint32_t)0x80000000)            /*!< Pin is, bit 31 */

/*******************  Bit definition for GPIO_IBE register  *******************/
#define GPIO_IBE_BIT0                        ((uint32_t)0x00000001)            /*!< Pin ibe, bit 0 */
#define GPIO_IBE_BIT1                        ((uint32_t)0x00000002)            /*!< Pin ibe, bit 1 */
#define GPIO_IBE_BIT2                        ((uint32_t)0x00000004)            /*!< Pin ibe, bit 2 */
#define GPIO_IBE_BIT3                        ((uint32_t)0x00000008)            /*!< Pin ibe, bit 3 */
#define GPIO_IBE_BIT4                        ((uint32_t)0x00000010)            /*!< Pin ibe, bit 4 */
#define GPIO_IBE_BIT5                        ((uint32_t)0x00000020)            /*!< Pin ibe, bit 5 */
#define GPIO_IBE_BIT6                        ((uint32_t)0x00000040)            /*!< Pin ibe, bit 6 */
#define GPIO_IBE_BIT7                        ((uint32_t)0x00000080)            /*!< Pin ibe, bit 7 */
#define GPIO_IBE_BIT8                        ((uint32_t)0x00000100)            /*!< Pin ibe, bit 8 */
#define GPIO_IBE_BIT9                        ((uint32_t)0x00000200)            /*!< Pin ibe, bit 9 */
#define GPIO_IBE_BIT10                       ((uint32_t)0x00000400)            /*!< Pin ibe, bit 10 */
#define GPIO_IBE_BIT11                       ((uint32_t)0x00000800)            /*!< Pin ibe, bit 11 */
#define GPIO_IBE_BIT12                       ((uint32_t)0x00001000)            /*!< Pin ibe, bit 12 */
#define GPIO_IBE_BIT13                       ((uint32_t)0x00002000)            /*!< Pin ibe, bit 13 */
#define GPIO_IBE_BIT14                       ((uint32_t)0x00004000)            /*!< Pin ibe, bit 14 */
#define GPIO_IBE_BIT15                       ((uint32_t)0x00008000)            /*!< Pin ibe, bit 15 */
#define GPIO_IBE_BIT16                       ((uint32_t)0x00010000)            /*!< Pin ibe, bit 16 */
#define GPIO_IBE_BIT17                       ((uint32_t)0x00020000)            /*!< Pin ibe, bit 17 */
#define GPIO_IBE_BIT18                       ((uint32_t)0x00040000)            /*!< Pin ibe, bit 18 */
#define GPIO_IBE_BIT19                       ((uint32_t)0x00080000)            /*!< Pin ibe, bit 19 */
#define GPIO_IBE_BIT20                       ((uint32_t)0x00100000)            /*!< Pin ibe, bit 20 */
#define GPIO_IBE_BIT21                       ((uint32_t)0x00200000)            /*!< Pin ibe, bit 21 */
#define GPIO_IBE_BIT22                       ((uint32_t)0x00400000)            /*!< Pin ibe, bit 22 */
#define GPIO_IBE_BIT23                       ((uint32_t)0x00800000)            /*!< Pin ibe, bit 23 */
#define GPIO_IBE_BIT24                       ((uint32_t)0x01000000)            /*!< Pin ibe, bit 24 */
#define GPIO_IBE_BIT25                       ((uint32_t)0x02000000)            /*!< Pin ibe, bit 25 */
#define GPIO_IBE_BIT26                       ((uint32_t)0x04000000)            /*!< Pin ibe, bit 26 */
#define GPIO_IBE_BIT27                       ((uint32_t)0x08000000)            /*!< Pin ibe, bit 27 */
#define GPIO_IBE_BIT28                       ((uint32_t)0x10000000)            /*!< Pin ibe, bit 28 */
#define GPIO_IBE_BIT29                       ((uint32_t)0x20000000)            /*!< Pin ibe, bit 29 */
#define GPIO_IBE_BIT30                       ((uint32_t)0x40000000)            /*!< Pin ibe, bit 30 */
#define GPIO_IBE_BIT31                       ((uint32_t)0x80000000)            /*!< Pin ibe, bit 31 */

/*******************  Bit definition for GPIO_IEV register  *******************/
#define GPIO_IEV_BIT0                        ((uint32_t)0x00000001)            /*!< Pin iev, bit 0 */
#define GPIO_IEV_BIT1                        ((uint32_t)0x00000002)            /*!< Pin iev, bit 1 */
#define GPIO_IEV_BIT2                        ((uint32_t)0x00000004)            /*!< Pin iev, bit 2 */
#define GPIO_IEV_BIT3                        ((uint32_t)0x00000008)            /*!< Pin iev, bit 3 */
#define GPIO_IEV_BIT4                        ((uint32_t)0x00000010)            /*!< Pin iev, bit 4 */
#define GPIO_IEV_BIT5                        ((uint32_t)0x00000020)            /*!< Pin iev, bit 5 */
#define GPIO_IEV_BIT6                        ((uint32_t)0x00000040)            /*!< Pin iev, bit 6 */
#define GPIO_IEV_BIT7                        ((uint32_t)0x00000080)            /*!< Pin iev, bit 7 */
#define GPIO_IEV_BIT8                        ((uint32_t)0x00000100)            /*!< Pin iev, bit 8 */
#define GPIO_IEV_BIT9                        ((uint32_t)0x00000200)            /*!< Pin iev, bit 9 */
#define GPIO_IEV_BIT10                       ((uint32_t)0x00000400)            /*!< Pin iev, bit 10 */
#define GPIO_IEV_BIT11                       ((uint32_t)0x00000800)            /*!< Pin iev, bit 11 */
#define GPIO_IEV_BIT12                       ((uint32_t)0x00001000)            /*!< Pin iev, bit 12 */
#define GPIO_IEV_BIT13                       ((uint32_t)0x00002000)            /*!< Pin iev, bit 13 */
#define GPIO_IEV_BIT14                       ((uint32_t)0x00004000)            /*!< Pin iev, bit 14 */
#define GPIO_IEV_BIT15                       ((uint32_t)0x00008000)            /*!< Pin iev, bit 15 */
#define GPIO_IEV_BIT16                       ((uint32_t)0x00010000)            /*!< Pin iev, bit 16 */
#define GPIO_IEV_BIT17                       ((uint32_t)0x00020000)            /*!< Pin iev, bit 17 */
#define GPIO_IEV_BIT18                       ((uint32_t)0x00040000)            /*!< Pin iev, bit 18 */
#define GPIO_IEV_BIT19                       ((uint32_t)0x00080000)            /*!< Pin iev, bit 19 */
#define GPIO_IEV_BIT20                       ((uint32_t)0x00100000)            /*!< Pin iev, bit 20 */
#define GPIO_IEV_BIT21                       ((uint32_t)0x00200000)            /*!< Pin iev, bit 21 */
#define GPIO_IEV_BIT22                       ((uint32_t)0x00400000)            /*!< Pin iev, bit 22 */
#define GPIO_IEV_BIT23                       ((uint32_t)0x00800000)            /*!< Pin iev, bit 23 */
#define GPIO_IEV_BIT24                       ((uint32_t)0x01000000)            /*!< Pin iev, bit 24 */
#define GPIO_IEV_BIT25                       ((uint32_t)0x02000000)            /*!< Pin iev, bit 25 */
#define GPIO_IEV_BIT26                       ((uint32_t)0x04000000)            /*!< Pin iev, bit 26 */
#define GPIO_IEV_BIT27                       ((uint32_t)0x08000000)            /*!< Pin iev, bit 27 */
#define GPIO_IEV_BIT28                       ((uint32_t)0x10000000)            /*!< Pin iev, bit 28 */
#define GPIO_IEV_BIT29                       ((uint32_t)0x20000000)            /*!< Pin iev, bit 29 */
#define GPIO_IEV_BIT30                       ((uint32_t)0x40000000)            /*!< Pin iev, bit 30 */
#define GPIO_IEV_BIT31                       ((uint32_t)0x80000000)            /*!< Pin iev, bit 31 */

/*******************  Bit definition for GPIO_IE register  *******************/
#define GPIO_IE_BIT0                        ((uint32_t)0x00000001)            /*!< Pin ie, bit 0 */
#define GPIO_IE_BIT1                        ((uint32_t)0x00000002)            /*!< Pin ie, bit 1 */
#define GPIO_IE_BIT2                        ((uint32_t)0x00000004)            /*!< Pin ie, bit 2 */
#define GPIO_IE_BIT3                        ((uint32_t)0x00000008)            /*!< Pin ie, bit 3 */
#define GPIO_IE_BIT4                        ((uint32_t)0x00000010)            /*!< Pin ie, bit 4 */
#define GPIO_IE_BIT5                        ((uint32_t)0x00000020)            /*!< Pin ie, bit 5 */
#define GPIO_IE_BIT6                        ((uint32_t)0x00000040)            /*!< Pin ie, bit 6 */
#define GPIO_IE_BIT7                        ((uint32_t)0x00000080)            /*!< Pin ie, bit 7 */
#define GPIO_IE_BIT8                        ((uint32_t)0x00000100)            /*!< Pin ie, bit 8 */
#define GPIO_IE_BIT9                        ((uint32_t)0x00000200)            /*!< Pin ie, bit 9 */
#define GPIO_IE_BIT10                       ((uint32_t)0x00000400)            /*!< Pin ie, bit 10 */
#define GPIO_IE_BIT11                       ((uint32_t)0x00000800)            /*!< Pin ie, bit 11 */
#define GPIO_IE_BIT12                       ((uint32_t)0x00001000)            /*!< Pin ie, bit 12 */
#define GPIO_IE_BIT13                       ((uint32_t)0x00002000)            /*!< Pin ie, bit 13 */
#define GPIO_IE_BIT14                       ((uint32_t)0x00004000)            /*!< Pin ie, bit 14 */
#define GPIO_IE_BIT15                       ((uint32_t)0x00008000)            /*!< Pin ie, bit 15 */
#define GPIO_IE_BIT16                       ((uint32_t)0x00010000)            /*!< Pin ie, bit 16 */
#define GPIO_IE_BIT17                       ((uint32_t)0x00020000)            /*!< Pin ie, bit 17 */
#define GPIO_IE_BIT18                       ((uint32_t)0x00040000)            /*!< Pin ie, bit 18 */
#define GPIO_IE_BIT19                       ((uint32_t)0x00080000)            /*!< Pin ie, bit 19 */
#define GPIO_IE_BIT20                       ((uint32_t)0x00100000)            /*!< Pin ie, bit 20 */
#define GPIO_IE_BIT21                       ((uint32_t)0x00200000)            /*!< Pin ie, bit 21 */
#define GPIO_IE_BIT22                       ((uint32_t)0x00400000)            /*!< Pin ie, bit 22 */
#define GPIO_IE_BIT23                       ((uint32_t)0x00800000)            /*!< Pin ie, bit 23 */
#define GPIO_IE_BIT24                       ((uint32_t)0x01000000)            /*!< Pin ie, bit 24 */
#define GPIO_IE_BIT25                       ((uint32_t)0x02000000)            /*!< Pin ie, bit 25 */
#define GPIO_IE_BIT26                       ((uint32_t)0x04000000)            /*!< Pin ie, bit 26 */
#define GPIO_IE_BIT27                       ((uint32_t)0x08000000)            /*!< Pin ie, bit 27 */
#define GPIO_IE_BIT28                       ((uint32_t)0x10000000)            /*!< Pin ie, bit 28 */
#define GPIO_IE_BIT29                       ((uint32_t)0x20000000)            /*!< Pin ie, bit 29 */
#define GPIO_IE_BIT30                       ((uint32_t)0x40000000)            /*!< Pin ie, bit 30 */
#define GPIO_IE_BIT31                       ((uint32_t)0x80000000)            /*!< Pin ie, bit 31 */

/*******************  Bit definition for GPIO_IRS register  *******************/
#define GPIO_IRS_BIT0                        ((uint32_t)0x00000001)            /*!< Pin irs, bit 0 */
#define GPIO_IRS_BIT1                        ((uint32_t)0x00000002)            /*!< Pin irs, bit 1 */
#define GPIO_IRS_BIT2                        ((uint32_t)0x00000004)            /*!< Pin irs, bit 2 */
#define GPIO_IRS_BIT3                        ((uint32_t)0x00000008)            /*!< Pin irs, bit 3 */
#define GPIO_IRS_BIT4                        ((uint32_t)0x00000010)            /*!< Pin irs, bit 4 */
#define GPIO_IRS_BIT5                        ((uint32_t)0x00000020)            /*!< Pin irs, bit 5 */
#define GPIO_IRS_BIT6                        ((uint32_t)0x00000040)            /*!< Pin irs, bit 6 */
#define GPIO_IRS_BIT7                        ((uint32_t)0x00000080)            /*!< Pin irs, bit 7 */
#define GPIO_IRS_BIT8                        ((uint32_t)0x00000100)            /*!< Pin irs, bit 8 */
#define GPIO_IRS_BIT9                        ((uint32_t)0x00000200)            /*!< Pin irs, bit 9 */
#define GPIO_IRS_BIT10                       ((uint32_t)0x00000400)            /*!< Pin irs, bit 10 */
#define GPIO_IRS_BIT11                       ((uint32_t)0x00000800)            /*!< Pin irs, bit 11 */
#define GPIO_IRS_BIT12                       ((uint32_t)0x00001000)            /*!< Pin irs, bit 12 */
#define GPIO_IRS_BIT13                       ((uint32_t)0x00002000)            /*!< Pin irs, bit 13 */
#define GPIO_IRS_BIT14                       ((uint32_t)0x00004000)            /*!< Pin irs, bit 14 */
#define GPIO_IRS_BIT15                       ((uint32_t)0x00008000)            /*!< Pin irs, bit 15 */
#define GPIO_IRS_BIT16                       ((uint32_t)0x00010000)            /*!< Pin irs, bit 16 */
#define GPIO_IRS_BIT17                       ((uint32_t)0x00020000)            /*!< Pin irs, bit 17 */
#define GPIO_IRS_BIT18                       ((uint32_t)0x00040000)            /*!< Pin irs, bit 18 */
#define GPIO_IRS_BIT19                       ((uint32_t)0x00080000)            /*!< Pin irs, bit 19 */
#define GPIO_IRS_BIT20                       ((uint32_t)0x00100000)            /*!< Pin irs, bit 20 */
#define GPIO_IRS_BIT21                       ((uint32_t)0x00200000)            /*!< Pin irs, bit 21 */
#define GPIO_IRS_BIT22                       ((uint32_t)0x00400000)            /*!< Pin irs, bit 22 */
#define GPIO_IRS_BIT23                       ((uint32_t)0x00800000)            /*!< Pin irs, bit 23 */
#define GPIO_IRS_BIT24                       ((uint32_t)0x01000000)            /*!< Pin irs, bit 24 */
#define GPIO_IRS_BIT25                       ((uint32_t)0x02000000)            /*!< Pin irs, bit 25 */
#define GPIO_IRS_BIT26                       ((uint32_t)0x04000000)            /*!< Pin irs, bit 26 */
#define GPIO_IRS_BIT27                       ((uint32_t)0x08000000)            /*!< Pin irs, bit 27 */
#define GPIO_IRS_BIT28                       ((uint32_t)0x10000000)            /*!< Pin irs, bit 28 */
#define GPIO_IRS_BIT29                       ((uint32_t)0x20000000)            /*!< Pin irs, bit 29 */
#define GPIO_IRS_BIT30                       ((uint32_t)0x40000000)            /*!< Pin irs, bit 30 */
#define GPIO_IRS_BIT31                       ((uint32_t)0x80000000)            /*!< Pin irs, bit 31 */

/*******************  Bit definition for GPIO_MIS register  *******************/
#define GPIO_MIS_BIT0                        ((uint32_t)0x00000001)            /*!< Pin mis, bit 0 */
#define GPIO_MIS_BIT1                        ((uint32_t)0x00000002)            /*!< Pin mis, bit 1 */
#define GPIO_MIS_BIT2                        ((uint32_t)0x00000004)            /*!< Pin mis, bit 2 */
#define GPIO_MIS_BIT3                        ((uint32_t)0x00000008)            /*!< Pin mis, bit 3 */
#define GPIO_MIS_BIT4                        ((uint32_t)0x00000010)            /*!< Pin mis, bit 4 */
#define GPIO_MIS_BIT5                        ((uint32_t)0x00000020)            /*!< Pin mis, bit 5 */
#define GPIO_MIS_BIT6                        ((uint32_t)0x00000040)            /*!< Pin mis, bit 6 */
#define GPIO_MIS_BIT7                        ((uint32_t)0x00000080)            /*!< Pin mis, bit 7 */
#define GPIO_MIS_BIT8                        ((uint32_t)0x00000100)            /*!< Pin mis, bit 8 */
#define GPIO_MIS_BIT9                        ((uint32_t)0x00000200)            /*!< Pin mis, bit 9 */
#define GPIO_MIS_BIT10                       ((uint32_t)0x00000400)            /*!< Pin mis, bit 10 */
#define GPIO_MIS_BIT11                       ((uint32_t)0x00000800)            /*!< Pin mis, bit 11 */
#define GPIO_MIS_BIT12                       ((uint32_t)0x00001000)            /*!< Pin mis, bit 12 */
#define GPIO_MIS_BIT13                       ((uint32_t)0x00002000)            /*!< Pin mis, bit 13 */
#define GPIO_MIS_BIT14                       ((uint32_t)0x00004000)            /*!< Pin mis, bit 14 */
#define GPIO_MIS_BIT15                       ((uint32_t)0x00008000)            /*!< Pin mis, bit 15 */
#define GPIO_MIS_BIT16                       ((uint32_t)0x00010000)            /*!< Pin mis, bit 16 */
#define GPIO_MIS_BIT17                       ((uint32_t)0x00020000)            /*!< Pin mis, bit 17 */
#define GPIO_MIS_BIT18                       ((uint32_t)0x00040000)            /*!< Pin mis, bit 18 */
#define GPIO_MIS_BIT19                       ((uint32_t)0x00080000)            /*!< Pin mis, bit 19 */
#define GPIO_MIS_BIT20                       ((uint32_t)0x00100000)            /*!< Pin mis, bit 20 */
#define GPIO_MIS_BIT21                       ((uint32_t)0x00200000)            /*!< Pin mis, bit 21 */
#define GPIO_MIS_BIT22                       ((uint32_t)0x00400000)            /*!< Pin mis, bit 22 */
#define GPIO_MIS_BIT23                       ((uint32_t)0x00800000)            /*!< Pin mis, bit 23 */
#define GPIO_MIS_BIT24                       ((uint32_t)0x01000000)            /*!< Pin mis, bit 24 */
#define GPIO_MIS_BIT25                       ((uint32_t)0x02000000)            /*!< Pin mis, bit 25 */
#define GPIO_MIS_BIT26                       ((uint32_t)0x04000000)            /*!< Pin mis, bit 26 */
#define GPIO_MIS_BIT27                       ((uint32_t)0x08000000)            /*!< Pin mis, bit 27 */
#define GPIO_MIS_BIT28                       ((uint32_t)0x10000000)            /*!< Pin mis, bit 28 */
#define GPIO_MIS_BIT29                       ((uint32_t)0x20000000)            /*!< Pin mis, bit 29 */
#define GPIO_MIS_BIT30                       ((uint32_t)0x40000000)            /*!< Pin mis, bit 30 */
#define GPIO_MIS_BIT31                       ((uint32_t)0x80000000)            /*!< Pin mis, bit 31 */

/*******************  Bit definition for GPIO_IC register  *******************/
#define GPIO_IC_BIT0                         ((uint32_t)0x00000001)            /*!< Pin ic, bit 0 */
#define GPIO_IC_BIT1                         ((uint32_t)0x00000002)            /*!< Pin ic, bit 1 */
#define GPIO_IC_BIT2                         ((uint32_t)0x00000004)            /*!< Pin ic, bit 2 */
#define GPIO_IC_BIT3                         ((uint32_t)0x00000008)            /*!< Pin ic, bit 3 */
#define GPIO_IC_BIT4                         ((uint32_t)0x00000010)            /*!< Pin ic, bit 4 */
#define GPIO_IC_BIT5                         ((uint32_t)0x00000020)            /*!< Pin ic, bit 5 */
#define GPIO_IC_BIT6                         ((uint32_t)0x00000040)            /*!< Pin ic, bit 6 */
#define GPIO_IC_BIT7                         ((uint32_t)0x00000080)            /*!< Pin ic, bit 7 */
#define GPIO_IC_BIT8                         ((uint32_t)0x00000100)            /*!< Pin ic, bit 8 */
#define GPIO_IC_BIT9                         ((uint32_t)0x00000200)            /*!< Pin ic, bit 9 */
#define GPIO_IC_BIT10                        ((uint32_t)0x00000400)            /*!< Pin ic, bit 10 */
#define GPIO_IC_BIT11                        ((uint32_t)0x00000800)            /*!< Pin ic, bit 11 */
#define GPIO_IC_BIT12                        ((uint32_t)0x00001000)            /*!< Pin ic, bit 12 */
#define GPIO_IC_BIT13                        ((uint32_t)0x00002000)            /*!< Pin ic, bit 13 */
#define GPIO_IC_BIT14                        ((uint32_t)0x00004000)            /*!< Pin ic, bit 14 */
#define GPIO_IC_BIT15                        ((uint32_t)0x00008000)            /*!< Pin ic, bit 15 */
#define GPIO_IC_BIT16                        ((uint32_t)0x00010000)            /*!< Pin ic, bit 16 */
#define GPIO_IC_BIT17                        ((uint32_t)0x00020000)            /*!< Pin ic, bit 17 */
#define GPIO_IC_BIT18                        ((uint32_t)0x00040000)            /*!< Pin ic, bit 18 */
#define GPIO_IC_BIT19                        ((uint32_t)0x00080000)            /*!< Pin ic, bit 19 */
#define GPIO_IC_BIT20                        ((uint32_t)0x00100000)            /*!< Pin ic, bit 20 */
#define GPIO_IC_BIT21                        ((uint32_t)0x00200000)            /*!< Pin ic, bit 21 */
#define GPIO_IC_BIT22                        ((uint32_t)0x00400000)            /*!< Pin ic, bit 22 */
#define GPIO_IC_BIT23                        ((uint32_t)0x00800000)            /*!< Pin ic, bit 23 */
#define GPIO_IC_BIT24                        ((uint32_t)0x01000000)            /*!< Pin ic, bit 24 */
#define GPIO_IC_BIT25                        ((uint32_t)0x02000000)            /*!< Pin ic, bit 25 */
#define GPIO_IC_BIT26                        ((uint32_t)0x04000000)            /*!< Pin ic, bit 26 */
#define GPIO_IC_BIT27                        ((uint32_t)0x08000000)            /*!< Pin ic, bit 27 */
#define GPIO_IC_BIT28                        ((uint32_t)0x10000000)            /*!< Pin ic, bit 28 */
#define GPIO_IC_BIT29                        ((uint32_t)0x20000000)            /*!< Pin ic, bit 29 */
#define GPIO_IC_BIT30                        ((uint32_t)0x40000000)            /*!< Pin ic, bit 30 */
#define GPIO_IC_BIT31                        ((uint32_t)0x80000000)            /*!< Pin ic, bit 31 */

/*******************  Bit definition for GPIO_PinMask register  *******************/
#define GPIO_PinMask_BIT0                   ((uint32_t)0x00000001)            /*!< Data mask, bit 0 */
#define GPIO_PinMask_BIT1                   ((uint32_t)0x00000002)            /*!< Data mask, bit 1 */
#define GPIO_PinMask_BIT2                   ((uint32_t)0x00000004)            /*!< Data mask, bit 2 */
#define GPIO_PinMask_BIT3                   ((uint32_t)0x00000008)            /*!< Data mask, bit 3 */
#define GPIO_PinMask_BIT4                   ((uint32_t)0x00000010)            /*!< Data mask, bit 4 */
#define GPIO_PinMask_BIT5                   ((uint32_t)0x00000020)            /*!< Data mask, bit 5 */
#define GPIO_PinMask_BIT6                   ((uint32_t)0x00000040)            /*!< Data mask, bit 6 */
#define GPIO_PinMask_BIT7                   ((uint32_t)0x00000080)            /*!< Data mask, bit 7 */
#define GPIO_PinMask_BIT8                   ((uint32_t)0x00000100)            /*!< Data mask, bit 8 */
#define GPIO_PinMask_BIT9                   ((uint32_t)0x00000200)            /*!< Data mask, bit 9 */
#define GPIO_PinMask_BIT10                  ((uint32_t)0x00000400)            /*!< Data mask, bit 10 */
#define GPIO_PinMask_BIT11                  ((uint32_t)0x00000800)            /*!< Data mask, bit 11 */
#define GPIO_PinMask_BIT12                  ((uint32_t)0x00001000)            /*!< Data mask, bit 12 */
#define GPIO_PinMask_BIT13                  ((uint32_t)0x00002000)            /*!< Data mask, bit 13 */
#define GPIO_PinMask_BIT14                  ((uint32_t)0x00004000)            /*!< Data mask, bit 14 */
#define GPIO_PinMask_BIT15                  ((uint32_t)0x00008000)            /*!< Data mask, bit 15 */
#define GPIO_PinMask_BIT16                  ((uint32_t)0x00010000)            /*!< Data mask, bit 16 */
#define GPIO_PinMask_BIT17                  ((uint32_t)0x00020000)            /*!< Data mask, bit 17 */
#define GPIO_PinMask_BIT18                  ((uint32_t)0x00040000)            /*!< Data mask, bit 18 */
#define GPIO_PinMask_BIT19                  ((uint32_t)0x00080000)            /*!< Data mask, bit 19 */
#define GPIO_PinMask_BIT20                  ((uint32_t)0x00100000)            /*!< Data mask, bit 20 */
#define GPIO_PinMask_BIT21                  ((uint32_t)0x00200000)            /*!< Data mask, bit 21 */
#define GPIO_PinMask_BIT22                  ((uint32_t)0x00400000)            /*!< Data mask, bit 22 */
#define GPIO_PinMask_BIT23                  ((uint32_t)0x00800000)            /*!< Data mask, bit 23 */
#define GPIO_PinMask_BIT24                  ((uint32_t)0x01000000)            /*!< Data mask, bit 24 */
#define GPIO_PinMask_BIT25                  ((uint32_t)0x02000000)            /*!< Data mask, bit 25 */
#define GPIO_PinMask_BIT26                  ((uint32_t)0x04000000)            /*!< Data mask, bit 26 */
#define GPIO_PinMask_BIT27                  ((uint32_t)0x08000000)            /*!< Data mask, bit 27 */
#define GPIO_PinMask_BIT28                  ((uint32_t)0x10000000)            /*!< Data mask, bit 28 */
#define GPIO_PinMask_BIT29                  ((uint32_t)0x20000000)            /*!< Data mask, bit 29 */
#define GPIO_PinMask_BIT30                  ((uint32_t)0x40000000)            /*!< Data mask, bit 30 */
#define GPIO_PinMask_BIT31                  ((uint32_t)0x80000000)            /*!< Data mask, bit 31 */

/*******************  Bit definition for GPIO_DMA_CTRL register  *******************/
#define GPIO_XFER_COUNT                      ((uint32_t)0x0000FFFF)            /*!< Data counter */
#define GPIO_XFER_END                        ((uint32_t)0x00010000)            /*!< Transmit data end */
#define GPIO_FIFO_EMPTY                      ((uint32_t)0x00020000)            /*!< Transmit fifo empty */
#define GPIO_DMA_EN                          ((uint32_t)0x80000000)            /*!< DMA enable */

/*******************  Bit definition for GPIO_DMA_PADCTRL0 register  *******************/
#define GPIO_XFER_COUNT                      ((uint32_t)0x0000FFFF)            /*!< Select AHB clock cycle */

/*******************  Bit definition for GPIO_DMA_PADCTRL1 register  *******************/
#define GPIO_DMA_PADCTRL1_SEL0               ((uint32_t)0x0000000F)            /*!< Select GPIO0[7:0] */
#define GPIO_DMA_PADCTRL1_SEL1               ((uint32_t)0x000000F0)            /*!< Select GPIO0[15:8] */
#define GPIO_DMA_PADCTRL1_SEL2               ((uint32_t)0x00000F00)            /*!< Select GPIO0[23:16] */
#define GPIO_DMA_PADCTRL1_SEL3               ((uint32_t)0x0000F000)            /*!< Select GPIO0[31:24] */
#define GPIO_DMA_PADCTRL1_SEL4               ((uint32_t)0x000F0000)            /*!< Select GPIO1[7:0] */
#define GPIO_DMA_PADCTRL1_SEL5               ((uint32_t)0x00F00000)            /*!< Select GPIO1[15:8] */
#define GPIO_DMA_PADCTRL1_SEL6               ((uint32_t)0x0F000000)            /*!< Select GPIO1[23:16] */
#define GPIO_DMA_PADCTRL1_SEL7               ((uint32_t)0xF0000000)            /*!< Select GPIO1[31:24] */

/*******************  Bit definition for GPIO_DMA_PADCTRL2 register  *******************/
#define GPIO_DMA_PADCTRL1_SEL8               ((uint32_t)0x0000000F)            /*!< Select GPIO2[7:0] */
#define GPIO_DMA_PADCTRL1_SEL9               ((uint32_t)0x000000F0)            /*!< Select GPIO2[15:8] */
#define GPIO_DMA_PADCTRL1_SEL10              ((uint32_t)0x00000F00)            /*!< Select GPIO2[23:16] */


/******************************************************************************/
/*                                                                            									   */
/*                      Inter-integrated Circuit Interface                                                                             */
/*                                                                                                                                                       */
/******************************************************************************/
/*******************  Bit definition for I2C_CON register  ********************/
#define  I2C_CON_MASTER_MODE                 ((uint16_t)0x0001)
#define  I2C_CON_SPEED1_2                    ((uint16_t)0x0006)
#define  I2C_CON_IC_10BITADDR_SLAVE          ((uint16_t)0x0008)
#define  I2C_CON_IC_10BITADDR_MASTER         ((uint16_t)0x0010)
#define  I2C_CON_IC_RESTART_EN               ((uint16_t)0x0020)
#define  I2C_CON_IC_SLAVE_DISABLE            ((uint16_t)0x0040)

/*******************  Bit definition for IC_TAR register  ********************/
#define  I2C_TAR_IC_TAR0_9                   ((uint16_t)0x03FF)
#define  I2C_TAR_GC_OR_START                 ((uint16_t)0x0400)
#define  I2C_TAR_IC_SPECIAL                  ((uint16_t)0x0800)

/*******************  Bit definition for IC_SAR register  ********************/
#define  I2C_SAR_IC_SAR0_9                   ((uint16_t)0x03FF)

/*******************  Bit definition for IC_HS_MADDR register  ********************/
#define  I2C_IC_HS_MADDR_IC_HS_MAR0_2        ((uint16_t)0x0007)

/*******************  Bit definition for IC_DATA_CMD register  ********************/
#define  I2C_IC_DATA_CMD_DAT0_7              ((uint16_t)0x00FF)
#define  I2C_IC_DATA_CMD_CMD                 ((uint16_t)0x0100)

/*******************  Bit definition for IC_SS_SCL_HCNT register  ********************/
#define  I2C_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_SS_SCL_LCNT register  ********************/
#define  I2C_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_FS_SCL_HCNT register  ********************/
#define  I2C_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_FS_SCL_LCNT register  ********************/
#define  I2C_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_HS_SCL_HCNT register  ********************/
#define  I2C_IC_HS_SCL_HCNT_IC_HS_SCL_HCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_HS_SCL_LCNT register  ********************/
#define  I2C_IC_HS_SCL_LCNT_IC_HS_SCL_LCNT0_15 ((uint16_t)0xFFFF)

/*******************  Bit definition for IC_INTR_STAT register  ********************/
#define  I2C_IC_INTR_STAT_R_RX_UNDER         ((uint16_t)0x0001)
#define  I2C_IC_INTR_STAT_R_RX_OVER          ((uint16_t)0x0002)
#define  I2C_IC_INTR_STAT_R_RX_FULL          ((uint16_t)0x0004)
#define  I2C_IC_INTR_STAT_R_TX_OVER          ((uint16_t)0x0008)
#define  I2C_IC_INTR_STAT_R_TX_EMPTY         ((uint16_t)0x0010)
#define  I2C_IC_INTR_STAT_R_RD_REQ           ((uint16_t)0x0020)
#define  I2C_IC_INTR_STAT_R_TX_ABRT          ((uint16_t)0x0040)
#define  I2C_IC_INTR_STAT_R_RX_DONE          ((uint16_t)0x0080)
#define  I2C_IC_INTR_STAT_R_ACTIVITY         ((uint16_t)0x0100)
#define  I2C_IC_INTR_STAT_R_STOP_DET         ((uint16_t)0x0200)
#define  I2C_IC_INTR_STAT_R_START_DET        ((uint16_t)0x0400)
#define  I2C_IC_INTR_STAT_R_GEN_CALL         ((uint16_t)0x0800)

/*******************  Bit definition for IC_INTR_MASK register  ********************/
#define  I2C_IC_INTR_MASK_M_RX_UNDER         ((uint16_t)0x0001)
#define  I2C_IC_INTR_MASK_M_RX_OVER          ((uint16_t)0x0002)
#define  I2C_IC_INTR_MASK_M_RX_FULL          ((uint16_t)0x0004)
#define  I2C_IC_INTR_MASK_M_TX_OVER          ((uint16_t)0x0008)
#define  I2C_IC_INTR_MASK_M_TX_EMPTY         ((uint16_t)0x0010)
#define  I2C_IC_INTR_MASK_M_RD_REQ           ((uint16_t)0x0020)
#define  I2C_IC_INTR_MASK_M_TX_ABRT          ((uint16_t)0x0040)
#define  I2C_IC_INTR_MASK_M_ACTIVITY         ((uint16_t)0x0100)
#define  I2C_IC_INTR_MASK_M_STOP_DET         ((uint16_t)0x0200)
#define  I2C_IC_INTR_MASK_M_START_DET        ((uint16_t)0x0400)
#define  I2C_IC_INTR_MASK_M_GEN_CALL         ((uint16_t)0x0800)

/*******************  Bit definition for IC_RAW_INTR_STAT register  ********************/
#define  I2C_IC_RAW_INTR_STAT_RX_UNDER         ((uint16_t)0x0001)
#define  I2C_IC_RAW_INTR_STAT_RX_OVER          ((uint16_t)0x0002)
#define  I2C_IC_RAW_INTR_STAT_RX_FULL          ((uint16_t)0x0004)
#define  I2C_IC_RAW_INTR_STAT_TX_OVER          ((uint16_t)0x0008)
#define  I2C_IC_RAW_INTR_STAT_TX_EMPTY         ((uint16_t)0x0010)
#define  I2C_IC_RAW_INTR_STAT_RD_REQ           ((uint16_t)0x0020)
#define  I2C_IC_RAW_INTR_STAT_TX_ABRT          ((uint16_t)0x0040)
#define  I2C_IC_RAW_INTR_STAT_RX_DONE          ((uint16_t)0x0080)
#define  I2C_IC_RAW_INTR_STAT_ACTIVITY         ((uint16_t)0x0100)
#define  I2C_IC_RAW_INTR_STAT_STOP_DET         ((uint16_t)0x0200)
#define  I2C_IC_RAW_INTR_STAT_START_DET        ((uint16_t)0x0400)
#define  I2C_IC_RAW_INTR_STAT_GEN_CALL         ((uint16_t)0x0800)

/*******************  Bit definition for IC_RX_TL register  ********************/
#define  I2C_IC_RX_TL_RX_TL0_7                 ((uint16_t)0x00ff)

/*******************  Bit definition for IC_TX_TL register  ********************/
#define  I2C_IC_TX_TL_TX_TL0_7                 ((uint16_t)0x00ff)

/*******************  Bit definition for IC_CLR_INTR register  ********************/
#define  I2C_IC_CLR_INTR_CLR_INTR              ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_RX_UNDER register  ********************/
#define  I2C_IC_CLR_RX_UNDER_CLR_RX_UNDER      ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_RX_OVER register  ********************/
#define  I2C_IC_CLR_RX_OVER_CLR_RX_OVER        ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_TX_OVER register  ********************/
#define  I2C_IC_CLR_TX_OVER_CLR_TX_OVER        ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_RD_REQ register  ********************/
#define  I2C_IC_CLR_RD_REQ_CLR_RD_REQ          ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_TX_ABRT register  ********************/
#define  I2C_IC_CLR_TX_ABRT_CLR_TX_ABRT        ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_RX_DONE register  ********************/
#define  I2C_IC_CLR_RX_DONE_CLR_RX_DONE        ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_ACTIVITY register  ********************/
#define  I2C_IC_CLR_ACTIVITY_CLR_ACTIVITY      ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_STOP_DET register  ********************/
#define  I2C_IC_CLR_STOP_DET_CLR_STOP_DET      ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_START_DET register  ********************/
#define  I2C_IC_CLR_START_DET_CLR_START_DET    ((uint16_t)0x0001)

/*******************  Bit definition for IC_CLR_GEN_CALL register  ********************/
#define  I2C_IC_CLR_GEN_CALL_CLR_GEN_CALL      ((uint16_t)0x0001)

/*******************  Bit definition for IC_ENABLE register  ********************/
#define  I2C_IC_ENABLE_ENABLE                  ((uint16_t)0x0001)

/*******************  Bit definition for IC_STATUS register  ********************/
#define  I2C_IC_STATUS_ACTIVITY                ((uint16_t)0x0001)
#define  I2C_IC_STATUS_TFNF                    ((uint16_t)0x0002)
#define  I2C_IC_STATUS_TFE                     ((uint16_t)0x0004)
#define  I2C_IC_STATUS_RFNE                    ((uint16_t)0x0008)
#define  I2C_IC_STATUS_RFF                     ((uint16_t)0x0010)
#define  I2C_IC_STATUS_MST_ACTIVITY            ((uint16_t)0x0020)
#define  I2C_IC_STATUS_SLV_ACTIVITY            ((uint16_t)0x0040)

/*******************  Bit definition for IC_TXFLR register  ********************/
#define  I2C_IC_TXFLR_TXFLR0_3                 ((uint16_t)0x000f)

/*******************  Bit definition for IC_RXFLR register  ********************/
#define  I2C_IC_RXFLR_RXFLR0_3                 ((uint16_t)0x000f)

/*******************  Bit definition for IC_TX_ABRT_SOURCE register  ********************/
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK         ((uint16_t)0x0001)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK         ((uint16_t)0x0002)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK         ((uint16_t)0x0004)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK          ((uint16_t)0x0008)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK           ((uint16_t)0x0010)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ            ((uint16_t)0x0020)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET             ((uint16_t)0x0040)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET          ((uint16_t)0x0080)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT            ((uint16_t)0x0100)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT         ((uint16_t)0x0200)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT        ((uint16_t)0x0400)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS            ((uint16_t)0x0800)
#define  I2C_IC_TX_ABRT_SOURCE_ARB_LOST                   ((uint16_t)0x1000)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO       ((uint16_t)0x2000)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST           ((uint16_t)0x4000)
#define  I2C_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX            ((uint16_t)0x8000)

/*******************  Bit definition for IC_SLV_DATA_NACK_ONLY register  ********************/
#define  I2C_IC_SLV_DATA_NACK_ONLY_NACK        ((uint16_t)0x0001)

/*******************  Bit definition for IC_DMA_CR register  ********************/
#define  I2C_IC_DMA_CR_RDMAE                   ((uint16_t)0x0001)
#define  I2C_IC_DMA_CR_TDMAE                   ((uint16_t)0x0002)

/*******************  Bit definition for IC_DMA_TDLR register  ********************/
//NONE

/*******************  Bit definition for IC_DMA_RDLR register  ********************/
//NONE

/*******************  Bit definition for IC_SDA_SETUP register  ********************/
#define  I2C_IC_SDA_SETUP_SDA_SETUP0_7          ((uint16_t)0x00ff)

/*******************  Bit definition for I2C_CON register  ********************/
#define  I2C_IC_ACK_GENERAL_CALL_ACK_GEN_CALL   ((uint16_t)0x0001)

/*******************  Bit definition for IC_ENABLE_STATUS register  ********************/
#define  I2C_IC_ENABLE_STATUS_IC_EN             ((uint16_t)0x0001)
#define  I2C_IC_ENABLE_STATUS_SLV_RX_ABORTED    ((uint16_t)0x0002)
#define  I2C_IC_ENABLE_STATUS_SLV_FIFO_FILLED_AND_FLUSHED   ((uint16_t)0x0004)


/******************************************************************************/
/*                                                                            									   */
/*                      Direct Memory Access Interface                                                                                */
/*                                                                                                                                                       */
/******************************************************************************/
/*******************  Bit definition for SAR register  ********************/
//NONE

/*******************  Bit definition for DAR register  ********************/
//NONE

/*******************  Bit definition for LLP register  ********************/
#define  LLP_LMS        ((uint32_t)0x00000003)
#define  LLP_LOC        ((uint32_t)0xfffffffc)

/*******************  Bit definition for CTL_L register  ********************/
#define CTL_L_INT_EN   		((uint32_t)0x00000001) 
#define CTL_L_DST_TR_WIDTH    ((uint32_t)0x0000000e) 
#define CTL_L_SRC_TR_WIDTH	((uint32_t)0x00000070) 
#define CTL_L_DINC   		    ((uint32_t)0x00000180) 
#define CTL_L_SINC   		    ((uint32_t)0x00000600) 
#define CTL_L_DEST_MSIZE   	((uint32_t)0x00003800) 
#define CTL_L_SRC_MSIZE  		((uint32_t)0x0001C000) 
#define CTL_L_SRC_GATHER_EN	((uint32_t)0x00020000) 
#define CTL_L_DST_SCATTER_EN	((uint32_t)0x00040000) 
#define CTL_L_TT_FC    		((uint32_t)0x00700000) 
#define CTL_L_DMS         		((uint32_t)0x01800000) 
#define CTL_L_SMS      		((uint32_t)0x06000000) 
#define CTL_L_LLP_DST_EN 		((uint32_t)0x08000000) 
#define CTL_L_LLP_SRC_EN 		((uint32_t)0x10000000) 

/*******************  Bit definition for CTL_H register  ********************/
#define CTL_H_BLOCK_TS      	((uint32_t)0x00000fff) 
#define CTL_H_DONE      		((uint32_t)0x06001000) 

/*******************  Bit definition for SSTAT register  ********************/
//NONE

/*******************  Bit definition for DSTAT register  ********************/
//NONE

/*******************  Bit definition for SSTATAR register  ********************/
//NONE

/*******************  Bit definition for DSTATAR register  ********************/
//NONE

/*******************  Bit definition for CFG_L register  ********************/
#define CFG_L_CH_PRIOR      	((uint32_t)0x000000e0) 
#define CFG_L_CH_SUSP     		((uint32_t)0x00000100) 
#define CFG_L_FIFO_EMPTY 		((uint32_t)0x00000200) 
#define CFG_L_HS_SEL_DST   	((uint32_t)0x00000400) 
#define CFG_L_HS_SEL_SRC 		((uint32_t)0x00000800) 
#define CFG_L_LOCK_CH_L      	((uint32_t)0x00003000) 
#define CFG_L_LOCK_B_L      	((uint32_t)0x0000c000) 
#define CFG_L_LOCK_CH      	((uint32_t)0x00010000) 
#define CFG_L_LOCK_B      		((uint32_t)0x00020000) 
#define CFG_L_DST_HS_POL      ((uint32_t)0x00040000) 
#define CFG_L_SRC_HS_POL      ((uint32_t)0x00080000) 
#define CFG_L_MAX_ABRST       ((uint32_t)0x3ff00000) 
#define CFG_L_RELOAD_SRC      ((uint32_t)0x40000000) 
#define CFG_L_RELOAD_DST      ((uint32_t)0x80000000) 

/*******************  Bit definition for CFG_H register  ********************/
#define CFG_H_CH_FCMODE      	    ((uint32_t)0x00000001) 
#define CFG_H_CH_FIFO_MODE      	((uint32_t)0x00000002)
#define CFG_H_CH_PROTCTL      	((uint32_t)0x0000001c)
#define CFG_H_CH_DS_UPD_EN      	((uint32_t)0x00000020)
#define CFG_H_CH_SS_UPD_EN      	((uint32_t)0x00000040)
#define CFG_H_CH_SRC_PER      	((uint32_t)0x00000780)
#define CFG_H_CH_DEST_PER      	((uint32_t)0x00007800)

/*******************  Bit definition for SGR register  ********************/
#define SGR_SGI      	    ((uint32_t)0x000fffff) 

/*******************  Bit definition for DSR register  ********************/
#define SGR_DSI      	    ((uint32_t)0x000fffff) 

/*******************  Bit definition for Raw interrupt registers  ********************/
#define RawTfr_RAW      	    ((uint32_t)0x000000ff) 
#define RawBlock_RAW      	    ((uint32_t)0x000000ff) 
#define RawSrcTran_RAW      	((uint32_t)0x000000ff) 
#define RawDstTran_RAW      	((uint32_t)0x000000ff) 
#define RawErr_RAW      	    ((uint32_t)0x000000ff) 

/*******************  Bit definition for Status interrupt registers  ********************/
#define StatusTfr_STATUS      	    ((uint32_t)0x000000ff) 
#define StatusBlock_STATUS      	    ((uint32_t)0x000000ff) 
#define StatusSrcTran_STATUS      	((uint32_t)0x000000ff) 
#define StatusDstTran_STATUS      	((uint32_t)0x000000ff) 
#define StatusErr_STATUS      	    ((uint32_t)0x000000ff) 

/*******************  Bit definition for Mask interrupt registers  ********************/
#define MaskTfr_INT_MASK      	    ((uint32_t)0x000000ff)
#define MaskTfr_INT_MASK_WE      	    ((uint32_t)0x0000ff00)
#define MaskBlock_INT_MASK      	    ((uint32_t)0x000000ff) 
#define MaskBlock_INT_MASK_WE     	((uint32_t)0x0000ff00) 
#define MaskSrcTran_INT_MASK      	((uint32_t)0x000000ff) 
#define MaskSrcTran_INT_MASK_WE      	((uint32_t)0x0000ff00)
#define MaskDstTran_INT_MASK      	((uint32_t)0x000000ff) 
#define MaskDstTran_INT_MASK_WE      	((uint32_t)0x0000ff00) 
#define MaskErr_INT_MASK      	    ((uint32_t)0x000000ff) 
#define MaskErr_INT_MASK_WE      	    ((uint32_t)0x0000ff00) 

/*******************  Bit definition for Clear interrupt registers  ********************/
#define ClearTfr_CLEAR      	    ((uint32_t)0x000000ff) 
#define ClearBlock_CLEAR      	((uint32_t)0x000000ff) 
#define ClearSrcTran_CLEAR      	((uint32_t)0x000000ff) 
#define ClearDstTran_CLEAR      	((uint32_t)0x000000ff) 
#define ClearErr_CLEAR      	    ((uint32_t)0x000000ff) 

/*******************  Bit definition for StatusInt interrupt registers  ********************/
#define StatusInt_TFR				((uint32_t)0x00000001)
#define StatusInt_BLOCK			((uint32_t)0x00000002)
#define StatusInt_SRCT				((uint32_t)0x00000004)
#define StatusInt_DSTT				((uint32_t)0x00000008)
#define StatusInt_ERR				((uint32_t)0x00000010)

/*******************  Bit definition for ReqSrcReg interrupt registers  ********************/
#define ReqSrcReg_SRC_REQ         ((uint32_t)0x000000ff)   
#define ReqSrcReg_SRC_REQ_WE      ((uint32_t)0x0000ff00) 

/*******************  Bit definition for ReqDstReg interrupt registers  ********************/
#define ReqDstReg_DST_REQ         ((uint32_t)0x000000ff)   
#define ReqDstReg_DST_REQ_WE      ((uint32_t)0x0000ff00) 

/*******************  Bit definition for SglReqSrcReg interrupt registers  ********************/
#define SglReqSrcReg_SRC_SGLREQ         ((uint32_t)0x000000ff)   
#define SglReqSrcReg_SRC_SGLREQ_WE      ((uint32_t)0x0000ff00) 

/*******************  Bit definition for SglReqDstReg interrupt registers  ********************/
#define SglReqDstReg_DST_SGLREQ         ((uint32_t)0x000000ff)   
#define SglReqDstReg_DST_SGLREQ_WE      ((uint32_t)0x0000ff00) 

/*******************  Bit definition for LstSrcReg interrupt registers  ********************/
#define LstSrcReg_LSTSRC         ((uint32_t)0x000000ff)   
#define LstSrcReg_LSTSRC_WE      ((uint32_t)0x0000ff00) 

/*******************  Bit definition for LstDstReg interrupt registers  ********************/
#define LstDstReg_LSTDST         ((uint32_t)0x000000ff)   
#define LstDstReg_LSTDST_WE      ((uint32_t)0x0000ff00)

/*******************  Bit definition for DmaCfgReg interrupt registers  ********************/
#define DmaCfgReg_DMA_EN         ((uint32_t)0x00000001)   

/*******************  Bit definition for ChEnReg interrupt registers  ********************/
#define ChEnReg_CH_EN         ((uint32_t)0x000000ff)   
#define ChEnReg_CH_EN_WE      ((uint32_t)0x0000ff00)

/*******************  Bit definition for RCC_SYSPLLCTRL register  *******************/
#define  RCC_SYSPLLCTRL_FREQ            ((uint32_t)0x0000001F)        	/*!< System pll frequency */
#define  RCC_REF_SEL					((uint32_t)0x40000000)			/*!< System pll reference select */
#define  RCC_SYSPLLCTRL_FORCELOCK       ((uint32_t)0x80000000)        	/*!< System pll lock */

/*******************  Bit definition for RCC_SYSPLLSTAT register  *******************/
#define  RCC_SYSPLLSTAT_LOCK            ((uint8_t)0x01)           

/*******************  Bit definition for RCC_ANASTATUS register  *******************/
#define  RCC_ANASTATUS_RTC_POR          ((uint8_t)0x01)               	/*!< RTC analog signal */

/*******************  Bit definition for RCC_PIOPORCAP0 register  *******************/
#define  RCC_PIOPORCAP0_CAPPIO0         ((uint32_t)0x000000FF)        	/*!< Raw reset status input GPIO0 */
#define  RCC_PIOPORCAP0_CAPPIO1         ((uint32_t)0x0000FF00)         	/*!< Raw reset status input GPIO1 */
#define  RCC_PIOPORCAP0_CAPPIO2         ((uint32_t)0x00FF0000)         	/*!< Raw reset status input GPIO2 */
#define  RCC_PIOPORCAP0_CAPPIO3         ((uint32_t)0xFF000000)         	/*!< Raw reset status input GPIO3 */

/*******************  Bit definition for RCC_PIOPORCAP1 register  *******************/
#define  RCC_PIOPORCAP1_CAPPIO0         ((uint32_t)0x000000FF)         	/*!< Raw reset status input GPIO4 */
#define  RCC_PIOPORCAP1_CAPPIO1         ((uint32_t)0x0000FF00)         	/*!< Raw reset status input GPIO5 */
#define  RCC_PIOPORCAP1_CAPPIO2         ((uint32_t)0x00FF0000)         	/*!< Raw reset status input GPIO6 */
#define  RCC_PIOPORCAP1_CAPPIO3         ((uint32_t)0xFF000000)         	/*!< Raw reset status input GPIO7 */

/*******************  Bit definition for RCC_PIOPORCAP2 register  *******************/
#define  RCC_PIOPORCAP2_CAPPIO0         ((uint32_t)0x000000FF)         	/*!< Raw reset status input GPIO8 */
#define  RCC_PIOPORCAP2_CAPPIO1         ((uint32_t)0x0000FF00)         	/*!< Raw reset status input GPIO9 */
#define  RCC_PIOPORCAP2_CAPPIO2         ((uint32_t)0x00FF0000)         	/*!< Raw reset status input GPIO10 */

/*******************  Bit definition for RCC_BODCTRL register  *******************/
#define  RCC_PIOPORCAP3_BODINTVAL       ((uint8_t)0x03)               	/*!< BOD reset level */
#define  RCC_PIOPORCAP3_BODRSTENA       ((uint8_t)0x04)               	/*!< BOD reset enable */

/*******************  Bit definition for RCC_SYSTICKCAL register  *******************/
#define  RCC_SYSTICKCAL_CAL      	 	    ((uint32_t)0x03FFFFFF)         	/*!< System tick timer calibration value */

/*******************  Bit definition for RCC_STARTAPRP0 register  *******************/
#define  RCC_STARTAPRP0_APRPIO0         ((uint32_t)0x000000FF)         	/*!< Edge select for start logic input GPIO0 */
#define  RCC_STARTAPRP0_APRPIO1         ((uint32_t)0x0000FF00)         	/*!< Edge select for start logic input GPIO1 */
#define  RCC_STARTAPRP0_APRPIO2         ((uint32_t)0x00FF0000)         	/*!< Edge select for start logic input GPIO2 */
#define  RCC_STARTAPRP0_APRPIO3         ((uint32_t)0xFF000000)         	/*!< Edge select for start logic input GPIO3 */

/*******************  Bit definition for RCC_STARTERP0 register  *******************/
#define  RCC_STARTERP0_ERPIO0         	((uint32_t)0x000000FF)         	/*!< Enable start signal for start logic input GPIO1 */
#define  RCC_STARTERP0_ERPIO1         	((uint32_t)0x0000FF00)         	/*!< Enable start signal for start logic input GPIO2 */
#define  RCC_STARTERP0_ERPIO2         	((uint32_t)0x00FF0000)         	/*!< Enable start signal for start logic input GPIO3 */
#define  RCC_STARTERP0_ERPIO3         	((uint32_t)0xFF000000)         	/*!< Enable start signal for start logic input GPIO4 */

/*******************  Bit definition for RCC_STARTRSRP0 register  *******************/
#define  RCC_STARTRSRP0_RSRPIO0         ((uint32_t)0x000000FF)         	/*!< Start signal reset for start logic input GPIO1 */
#define  RCC_STARTRSRP0_RSRPIO1         ((uint32_t)0x0000FF00)         	/*!< Start signal reset for start logic input GPIO2 */
#define  RCC_STARTRSRP0_RSRPIO2         ((uint32_t)0x00FF0000)         	/*!< Start signal reset for start logic input GPIO3 */
#define  RCC_STARTRSRP0_RSRPIO3         ((uint32_t)0xFF000000)        	/*!< Start signal reset for start logic input GPIO4 */

/*******************  Bit definition for RCC_STARTSRP0 register  *******************/
#define  RCC_STARTSRP0_SRPIO0         	((uint32_t)0x000000FF)         	/*!< Start signal status for start logic input GPIO0 */
#define  RCC_STARTSRP0_SRPIO1         	((uint32_t)0x0000FF00)         	/*!< Start signal status for start logic input GPIO1 */
#define  RCC_STARTSRP0_SRPIO2         	((uint32_t)0x00FF0000)         	/*!< Start signal status for start logic input GPIO2 */
#define  RCC_STARTSRP0_SRPIO3         	((uint32_t)0xFF000000)         	/*!< Start signal status for start logic input GPIO3 */

/*******************  Bit definition for RCC_STARTAPRP1 register  *******************/
#define  RCC_STARTAPRP1_APRPIO0         ((uint8_t)0xFF)               	/*!< Edge select for start logic input GPIO4 */

/*******************  Bit definition for RCC_STARTERP1 register  *******************/
#define  RCC_STARTERP1_ERPIO0         	((uint8_t)0xFF)               	/*!< Enable start signal for start logic input GPIO4 */

/*******************  Bit definition for RCC_STARTRSRP1 register  *******************/
#define  RCC_STARTRSRP1_RSRPIO0         ((uint8_t)0xFF)               	/*!< Start signal reset for start logic input GPIO4 */

/*******************  Bit definition for RCC_STARTSRP1 register  *******************/
#define  RCC_STARTSRP1_SRPIO0         	((uint8_t)0xFF)               	/*!< Start signal status for start logic input GPIO4 */

/*******************  Bit definition for RCC_PDSLEEPCFG register  *******************/
#define  RCC_PDSLEEPCFG_EXT12M_PD      	((uint16_t)0x0001)        		/*!< IRC oscillator power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_ADC0_PD         ((uint16_t)0x0004)        		/*!< ADC0 power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_ADC1_PD         ((uint16_t)0x0008)        		/*!< ADC1 power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_SYSPLL_PD       ((uint16_t)0x0010)        		/*!< System PLL power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_BOD_PD          ((uint16_t)0x0020)        		/*!< BOD power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_BOR_PD          ((uint16_t)0x0040)        		/*!< BOD power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_RTC_PD         	((uint16_t)0x0080)        		/*!< RTC oscillator power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_IRC12M_PD       ((uint16_t)0x0100)        		/*!< RTC oscillator power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_CMP0_PD         ((uint16_t)0x0200)        		/*!< RTC oscillator power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_CMP1_PD         ((uint16_t)0x0400)        		/*!< DAC power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_USB_PD          ((uint16_t)0x0800)        		/*!< USB power-down control in Deep-sleep mode */
//#define  RCC_PDSLEEPCFG_USBPLL_PD       ((uint16_t)0x0100)        		/*!< USB PLL power-down control in Deep-sleep mode */
#define  RCC_PDSLEEPCFG_32KOSC_PD       ((uint16_t)0x1000)        		/*!< USB power-down control in Deep-sleep mode */

/*******************  Bit definition for RCC_PDAWAKECFG register  *******************/
#define  RCC_PDAWAKECFG_EXT12M_PD      	((uint16_t)0x0001)        		/*!< IRC oscillator power-down wake-up configuration */
#define  RCC_PDAWAKECFG_ADC0_PD         ((uint16_t)0x0004)        		/*!< ADC0 wake-up configuration */
#define  RCC_PDAWAKECFG_ADC1_PD         ((uint16_t)0x0008)        		/*!< ADC1 wake-up configuration */
#define  RCC_PDAWAKECFG_SYSPLL_PD       ((uint16_t)0x0010)        		/*!< System PLL wake-up configuration */
#define  RCC_PDAWAKECFG_BOD_PD          ((uint16_t)0x0020)        		/*!< BOD wake-up configuration */
#define  RCC_PDAWAKECFG_BOR_PD          ((uint16_t)0x0040)        		/*!< BOD wake-up configuration */
#define  RCC_PDAWAKECFG_RTC_PD         	((uint16_t)0x0080)        		/*!< RTC oscillator power-down wake-up configuration */
#define  RCC_PDAWAKECFG_IRC12M_PD       ((uint16_t)0x0100)        		/*!< BOD wake-up configuration */
#define  RCC_PDAWAKECFG_CMP0_PD         ((uint16_t)0x0200)        		/*!< DAC0 wake-up configuration */
#define  RCC_PDAWAKECFG_CMP1_PD         ((uint16_t)0x0400)        		/*!< DAC0 wake-up configuration */
#define  RCC_PDAWAKECFG_USB_PD          ((uint16_t)0x0800)        		/*!< USB wake-up configuration */
//#define  RCC_PDAWAKECFG_USBPLL_PD       ((uint16_t)0x0100)        		/*!< USB PLL wake-up configuration */
#define  RCC_PDAWAKECFG_32KOSC_PD          ((uint16_t)0x1000)        		/*!< USB wake-up configuration */

/*******************  Bit definition for RCC_PDRUNCFG register  *******************/
#define  RCC_PDRUNCFG_EXT12M_PD      	((uint16_t)0x0001)        		/*!< IRC oscillator power-down */
#define  RCC_PDRUNCFG_ADC0_PD         	((uint16_t)0x0004)        		/*!< ADC0 oscillator power-down */
#define  RCC_PDRUNCFG_ADC1_PD         	((uint16_t)0x0008)        		/*!< ADC1 oscillator power-down */
#define  RCC_PDRUNCFG_SYSPLL_PD       	((uint16_t)0x0010)        		/*!< System PLL oscillator power-down */
#define  RCC_PDRUNCFG_BOD_PD          	((uint16_t)0x0020)        		/*!< BOD oscillator power-down */
#define  RCC_PDRUNCFG_BOR_PD          	((uint16_t)0x0040)        		/*!< BOD oscillator power-down */
#define  RCC_PDRUNCFG_RTC_PD         	((uint16_t)0x0080)        		/*!< RTC oscillator power-down */
#define  RCC_PDRUNCFG_IRC12M_PD         ((uint16_t)0x0100)        		/*!< DAC0 oscillator power-down */
#define  RCC_PDRUNCFG_CMP0_PD         	((uint16_t)0x0200)        		/*!< RTC oscillator power-down */
#define  RCC_PDRUNCFG_CMP1_PD         	((uint16_t)0x0400)        		/*!< RTC oscillator power-down */
#define  RCC_PDRUNCFG_USB_PD          	((uint16_t)0x0800)        		/*!< USB oscillator power-down */
//#define  RCC_PDRUNCFG_USBPLL_PD       	((uint16_t)0x0100)        		/*!< USB PLL oscillator power-down */
#define  RCC_PDRUNCFG_32KOSC_PD         ((uint16_t)0x1000)        		/*!< USB oscillator power-down */

/*******************  Bit definition for RCC_DEVICEID register  *******************/
#define  RCC_DEVICEID               	((uint32_t)0xFFFFFFFF)        /*!< Device ID */

/*******************  Bit definition for RCC_PCON register  *******************/
#define  RCC_PCON_ADDR_DPDEN            ((uint16_t)0x0002)        		/*!< Deep-sleep enable */
#define  RCC_PCON_ADDR_SLEEPFLAG        ((uint16_t)0x0100)        		/*!< Sleep mode flag */
#define  RCC_PCON_ADDR_DPDFLAG          ((uint16_t)0x0800)        		/*!< Deep-sleep mode flag */


/******************************************************************************/
/*                                                                            */
/*                               Timers (TIM)                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            /*!<Counter enable */
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            /*!<Update disable */
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            /*!<Update request source */
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            /*!<One pulse mode */
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            /*!<Direction */

#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            /*!<Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            /*!<Bit 1 */

#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            /*!<Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            /*!<Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint16_t)0x0001)            /*!<Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint16_t)0x0004)            /*!<Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint16_t)0x0008)            /*!<Capture/Compare DMA Selection */

#define  TIM_CR2_MMS                         ((uint16_t)0x0070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CR2_TI1S                        ((uint16_t)0x0080)            /*!<TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint16_t)0x0100)            /*!<Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint16_t)0x0200)            /*!<Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint16_t)0x0400)            /*!<Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint16_t)0x0800)            /*!<Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint16_t)0x1000)            /*!<Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint16_t)0x2000)            /*!<Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint16_t)0x4000)            /*!<Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint16_t)0x0007)            /*!<SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint16_t)0x0004)            /*!<Bit 2 */

#define  TIM_SMCR_TS                         ((uint16_t)0x0070)            /*!<TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_SMCR_MSM                        ((uint16_t)0x0080)            /*!<Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint16_t)0x0F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint16_t)0x0800)            /*!<Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint16_t)0x3000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint16_t)0x2000)            /*!<Bit 1 */

#define  TIM_SMCR_ECE                        ((uint16_t)0x4000)            /*!<External clock enable */
#define  TIM_SMCR_ETP                        ((uint16_t)0x8000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            /*!<COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            /*!<Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            /*!<Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            /*!<Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            /*!<COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint16_t)0x0001)            /*!<Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint16_t)0x0020)            /*!<COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint16_t)0x0040)            /*!<Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint16_t)0x0080)            /*!<Break interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint16_t)0x0200)            /*!<Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF                        ((uint16_t)0x0400)            /*!<Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF                        ((uint16_t)0x0800)            /*!<Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF                        ((uint16_t)0x1000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint8_t)0x01)               /*!<Update Generation */
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               /*!<Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               /*!<Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               /*!<Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               /*!<Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               /*!<Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint8_t)0x40)               /*!<Trigger Generation */
#define  TIM_EGR_BG                          ((uint8_t)0x80)               /*!<Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint16_t)0x0003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint16_t)0x0004)            /*!<Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint16_t)0x0008)            /*!<Output Compare 1 Preload enable */

#define  TIM_CCMR1_OC1M                      ((uint16_t)0x0070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR1_OC1CE                     ((uint16_t)0x0080)            /*!<Output Compare 1Clear Enable */

#define  TIM_CCMR1_CC2S                      ((uint16_t)0x0300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint16_t)0x0400)            /*!<Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint16_t)0x0800)            /*!<Output Compare 2 Preload enable */

#define  TIM_CCMR1_OC2M                      ((uint16_t)0x7000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR1_OC2CE                     ((uint16_t)0x8000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint16_t)0x000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint16_t)0x00F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint16_t)0xF000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint16_t)0x0003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint16_t)0x0004)            /*!<Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint16_t)0x0008)            /*!<Output Compare 3 Preload enable */

#define  TIM_CCMR2_OC3M                      ((uint16_t)0x0070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR2_OC3CE                     ((uint16_t)0x0080)            /*!<Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S                      ((uint16_t)0x0300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint16_t)0x0400)            /*!<Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint16_t)0x0800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M                      ((uint16_t)0x7000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR2_OC4CE                     ((uint16_t)0x8000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint16_t)0x00F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint16_t)0xF000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint16_t)0x0001)            /*!<Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint16_t)0x0002)            /*!<Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint16_t)0x0004)            /*!<Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint16_t)0x0008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint16_t)0x0010)            /*!<Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint16_t)0x0020)            /*!<Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint16_t)0x0040)            /*!<Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint16_t)0x0080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint16_t)0x0100)            /*!<Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint16_t)0x0200)            /*!<Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint16_t)0x0400)            /*!<Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint16_t)0x1000)            /*!<Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint16_t)0x2000)            /*!<Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((uint16_t)0x8000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint16_t)0xFFFF)            /*!<Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint16_t)0xFFFF)            /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint16_t)0xFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint16_t)0x00FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint16_t)0x0010)            /*!<Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint16_t)0x0020)            /*!<Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint16_t)0x0040)            /*!<Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint16_t)0x0080)            /*!<Bit 7 */

#define  TIM_BDTR_LOCK                       ((uint16_t)0x0300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_BDTR_OSSI                       ((uint16_t)0x0400)            /*!<Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint16_t)0x0800)            /*!<Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint16_t)0x1000)            /*!<Break enable */
#define  TIM_BDTR_BKP                        ((uint16_t)0x2000)            /*!<Break Polarity */
#define  TIM_BDTR_AOE                        ((uint16_t)0x4000)            /*!<Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint16_t)0x8000)            /*!<Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA                         ((uint16_t)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0                       ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_DCR_DBA_1                       ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_DCR_DBA_2                       ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_DCR_DBA_3                       ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_DCR_DBA_4                       ((uint16_t)0x0010)            /*!<Bit 4 */

#define  TIM_DCR_DBL                         ((uint16_t)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_DCR_DBL_1                       ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_DCR_DBL_2                       ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_DCR_DBL_3                       ((uint16_t)0x0800)            /*!<Bit 3 */
#define  TIM_DCR_DBL_4                       ((uint16_t)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB                       ((uint16_t)0xFFFF)            /*!<DMA register for burst accesses */


/*******************  Bit definition for TIM_OR register  *********************/
#define TIM14_OR_TI1_RMP                       ((uint16_t)0x0003)            /*!<TI1_RMP[1:0] bits (TIM14 Input 4 remap) */
#define TIM14_OR_TI1_RMP_0                     ((uint16_t)0x0001)            /*!<Bit 0 */
#define TIM14_OR_TI1_RMP_1                     ((uint16_t)0x0002)            /*!<Bit 1 */

/******************************************************************************/
/*                                                                            */
/*                        QUAD Serial Peripheral Interface                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for HW_QSPI_CTRL0 register  ********************/
#define  QSPI_CTRL0_MEMAP                        ((uint32_t)0x02000000)     
#define  QSPI_CTRL0_READ                         ((uint32_t)0x04000000)            
#define  QSPI_CTRL0_LOCK_CS                      ((uint32_t)0x08000000)          
#define  QSPI_CTRL0_HALF_DUPLEX                  ((uint32_t)0x10000000) 
#define  QSPI_CTRL0_RUN                          ((uint32_t)0x20000000) 

/*******************  Bit definition for HW_QSPI_CTRL1 register  ********************/
#define  QSPI_CTRL1_MODE                         ((uint32_t)0x00000007)
#define  QSPI_CTRL1_WORD                         ((uint32_t)0x000000f8)
#define  QSPI_CTRL1_SLAVE_MODE                   ((uint32_t)0x00000100)
#define  QSPI_CTRL1_POLARITY                     ((uint32_t)0x00000200)
#define  QSPI_CTRL1_PHASE                        ((uint32_t)0x00000400)
#define  QSPI_CTRL1_SLAVE_OUT_DISABLE            ((uint32_t)0x00000800)
#define  QSPI_CTRL1_LOOP_BACK                    ((uint32_t)0x00001000)
#define  QSPI_CTRL1_DMA_ENABLE                   ((uint32_t)0x00002000)
#define  QSPI_CTRL1_RECV_OVRFLW_IRQ_EN           ((uint32_t)0x00004000)
#define  QSPI_CTRL1_RECV_OVRFLW_IRQ              ((uint32_t)0x00008000)
#define  QSPI_CTRL1_RECV_TIMEOUT_IRQ_EN          ((uint32_t)0x00010000)
#define  QSPI_CTRL1_RECV_TIMEOUT_IRQ             ((uint32_t)0x00020000)
#define  QSPI_CTRL1_RECV_IRQ_EN                  ((uint32_t)0x00040000)
#define  QSPI_CTRL1_RECV_IRQ                     ((uint32_t)0x00080000)
#define  QSPI_CTRL1_XMIT_IRQ_EN                  ((uint32_t)0x00100000)
#define  QSPI_CTRL1_XMIT_IRQ                     ((uint32_t)0x00200000)
#define  QSPI_CTRL1_LSB                          ((uint32_t)0x00400000)
#define  QSPI_CTRL1_QPI                          ((uint32_t)0x00800000)

/*******************  Bit definition for HW_QSPI_XFER register  ********************/
#define  QSPI_CMD                                ((uint32_t)0x00FF)  


/*******************  Bit definition for HW_QSPI_TIMING register  ********************/
#define  QSPI_TIMING_CLOCK_RATE                  ((uint32_t)0x000000FF)           
#define  QSPI_TIMING_CLOCK_DIVIDE                ((uint32_t)0x0000FF00)           

/*******************  Bit definition for HW_QSPI_DATA register  ********************/
#define  QSPI_DATA                               ((uint32_t)0xFFFFFFFF) 

/*******************  Bit definition for HW_QSPI_STATUS register  ********************/
#define  QSPI_STATUS_SPI_BUSY                    ((uint32_t)0x00000001)  
#define  QSPI_STATUS_XMIT_UNDRFLW                ((uint32_t)0x00000010)    
#define  QSPI_STATUS_XMIT_EMPTY                  ((uint32_t)0x00000020)
#define  QSPI_STATUS_XMIT_NOT_FULL               ((uint32_t)0x00000040)
#define  QSPI_STATUS_RECV_NOT_EMPTY              ((uint32_t)0x00000080)    
#define  QSPI_STATUS_RECV_FULL                   ((uint32_t)0x00000100)
#define  QSPI_STATUS_RECV_OVRFLW                 ((uint32_t)0x00000200)
#define  QSPI_STATUS_RECV_DATA_STAT              ((uint32_t)0x00000400)
#define  QSPI_STATUS_RECV_TIMEOUT_STAT           ((uint32_t)0x00000800)
#define  QSPI_STATUS_TXDAVL                      ((uint32_t)0x00F00000)
#define  QSPI_STATUS_RXDAVL                      ((uint32_t)0x0F000000)

/*******************  Bit definition for HW_QSPI_DEBUG register  ********************/
#define  QSPI_DEBUG0_SOEN                        ((uint32_t)0x00000001)  
#define  QSPI_DEBUG0_MOEN                        ((uint32_t)0x00000002)    
#define  QSPI_DEBUG0_SSN_OEN                     ((uint32_t)0x00000004)
#define  QSPI_DEBUG0_CLK_OEN                     ((uint32_t)0x00000008)
#define  QSPI_DEBUG0_RX_CNT_ONE                  ((uint32_t)0x00000010)    
#define  QSPI_DEBUG0_RFF4                        ((uint32_t)0x00000020)
#define  QSPI_DEBUG0_FORCE_TX                    ((uint32_t)0x00000040)
#define  QSPI_DEBUG0_LGNORE_RX                   ((uint32_t)0x00000080)
#define  QSPI_DEBUG0_TXD_BUSY                    ((uint32_t)0x00000100)
#define  QSPI_DEBUG0_FULL_CMD_DONE               ((uint32_t)0x00000200)
#define  QSPI_DEBUG0_HALF_CMD_DONE               ((uint32_t)0x00000400)
#define  QSPI_DEBUG0_FULL_DATA_STALL             ((uint32_t)0x00000800)
#define  QSPI_DEBUG0_HALF_DATA_STALL             ((uint32_t)0x00001000)
#define  QSPI_DEBUG0_FULL_DMA_ACK                ((uint32_t)0x00002000)
#define  QSPI_DEBUG0_HALF_DMA_ACK                ((uint32_t)0x00004000)
#define  QSPI_DEBUG0_FULL_DMA_STATE              ((uint32_t)0x00038000)
#define  QSPI_DEBUG0_HALF_DMA_STATE              ((uint32_t)0x001C0000)
#define  QSPI_DEBUG0_SLAVE_STATE                 ((uint32_t)0x03E00000)
#define  QSPI_DEBUG0_MASTER_STATE                ((uint32_t)0xFC000000)

/*******************  Bit definition for HW_QSPI_XFER register  ********************/
#define  QSPI_XFER                               ((uint32_t)0xFFFFFFFF) 

/***********************************************************************************/
/*                                                                                 */
/*                               RTC Peripheral Interface                          */
/*                                                                                 */
/***********************************************************************************/

/*******************  Bit definition for HW_RTC_CTRL register  ********************/
#define  RTC_CTRL_EN                             ((uint32_t)0x00000001)
#define  RTC_CTRL_TIE                            ((uint32_t)0x00000002)
#define  RTC_CTRL_AIE                            ((uint32_t)0x00000004)
#define  RTC_CTRL_CLKSEL                         ((uint32_t)0x00000030)
#define  RTC_CTRL_CLKSEL_0                       ((uint32_t)0x00000010)
#define  RTC_CTRL_CLKSEL_1                       ((uint32_t)0x00000020)

/*******************  Bit definition for HW_RTC_LOAD register  ********************/
#define  RTC_LOAD_EN                             ((uint32_t)0x00000001)

/*******************  Bit definition for HW_RTC_STAT register  ********************/
#define  RTC_STAT_TIS                            ((uint32_t)0x00000001)
#define  RTC_STAT_AIS                            ((uint32_t)0x00000002)

/***********************************************************************************/
/*                                                                                 */
/*                               CMP Peripheral Interface                          */
/*                                                                                 */
/***********************************************************************************/

/*******************  Bit definition for HW_CMP_CTRL0 register  ********************/
#define CMP_CTRL0_CMPEN                           ((uint32_t)0x00000001)
#define CMP_CTRL0_CMPIE                           ((uint32_t)0x00000002)
#define CMP_CTRL0_HYSEN                           ((uint32_t)0x00000004)
#define CMP_CTRL0_SELNG                           ((uint32_t)0x00000010)

/*******************  Bit definition for HW_CMP_CTRL1 register  ********************/
#define CMP_CTRL1_CMPEN                           ((uint32_t)0x00000001)
#define CMP_CTRL1_CMPIE                           ((uint32_t)0x00000002)
#define CMP_CTRL1_HYSEN                           ((uint32_t)0x00000004)
#define CMP_CTRL1_SELNG                           ((uint32_t)0x00000010)

/*******************  Bit definition for HW_CMP_STATUS register  ********************/
#define CMP_STATUS_FLAG0                           ((uint32_t)0x00000001)
#define CMP_STATUS_FLAG1                           ((uint32_t)0x00000002)
#define CMP_STATUS_CO0                             ((uint32_t)0x00000004)
#define CMP_STATUS_CO1                             ((uint32_t)0x00000008)


void writeReg(uint32_t addr, uint32_t value);
uint32_t readReg(uint32_t addr);

//寄存器读写函数
#define outl(v,p)   *(__IO uint32_t *) (p) = (v)	//write 32bit
#define inl(p)      (*(__IO uint32_t *)(p))			//read 32bit
#define outs(v,p)   *(__IO uint16_t *) (p) = (v)	//write 16bit
#define ins(p)      (*(__IO uint16_t *)(p))			//read 16bit
#define outb(v,p)   *(__IO uint8_t *) (p) = (v)		//write 8bit
#define inb(p)      (*(__IO uint8_t *)(p))			//read 8bit

#define SIM_FLAG                0x4000fffc

#define Byte2Bit(addr)	(((uint32_t)addr&0x03FFFFFF)<<3)	//Byte Addr to Bit Addr

//以下3个接口:测试一个寄存器的值是不是某个值，失败写入SIM_FLAG
//addr寄存器地址,val是正确值
void testReg32(uint32_t addr, uint32_t val);
void testReg16(uint32_t addr, uint16_t val);
void testReg8(uint32_t addr, uint8_t val);

//以下3个接口:测试一个寄存器的某些bit是不是某个值，失败写入SIM_FLAG
//addr寄存器地址,val是正确值
void testMask32(uint32_t addr, uint32_t mask, uint32_t val);
void testMask16(uint32_t addr, uint16_t mask, uint16_t val);
void testMask8(uint32_t addr, uint8_t mask, uint8_t val);

void commonDelay(volatile unsigned long time);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT TDO *****END OF FILE****/
