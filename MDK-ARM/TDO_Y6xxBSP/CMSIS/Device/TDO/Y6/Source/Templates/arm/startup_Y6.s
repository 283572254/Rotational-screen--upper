
;
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00004000;4k

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WKT_IRQHandler        ; 0            
                DCD     TIM1_IRQHandler       ; 1             
                DCD     TIM15_IRQHandler      ; 2
                DCD     TIM16_IRQHandler      ; 3
                DCD     TIM17_IRQHandler      ; 4
                DCD     RTC_IRQHandler        ; 5            
                DCD     USB0_IRQHandler	      ; 6            
                DCD     USB0_DMA_IRQHandler   ; 7
                DCD     TIM4_IRQHandler       ; 8            
                DCD     UART0_IRQHandler      ; 9 --UART0 IR
                DCD     UART1_IRQHandler      ; 10 --UART1 IR
                DCD     I2C0_IRQHandler       ; 11 --I2C0 IRQ
                DCD     UART2_IRQHandler      ; 12 --UART2 IR
                DCD     QSPI0_IRQHandler      ; 13 --QSPI0 IRQ
                DCD     QSPI1_IRQHandler      ; 14 --QSPI1 IRQ
                DCD     QSPI2_IRQHandler      ; 15 --QSPI2 IRQ
                DCD     DMA_IRQHandler        ; 16 --DMA IRQ 
                DCD     GPIO0_IRQHandler      ; 17 --GPIO0_IR
                DCD     GPIO1_IRQHandler      ; 18 --GPIO1_IR
                DCD     ADC0_IRQHandler       ; 19 --ADC0_IRQ
                DCD     0                     ; 
                DCD     BOD_IRQHandler        ; 21 --BOD_IRQ 
                DCD     BOR_IRQHandler        ; 22 --BOR_IRQ 
                DCD     CMP_IRQHandler        ; 23 --CMP_IRQ 
                DCD     0                     ; 
                DCD     0                     ; 
                DCD     LED_IRQHandler        ; 26 LED IRQ
                DCD     BITCOPY_IRQHandler    ; 27 BITCOPY IRQ
               
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
        IMPORT  __main
        IMPORT  SystemInit  
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC
 
                EXPORT  WKT_IRQHandler                 [WEAK]            
                EXPORT  TIM1_IRQHandler              [WEAK]            
                EXPORT  TIM15_IRQHandler             [WEAK]            
                EXPORT  TIM16_IRQHandler             [WEAK]            
                EXPORT  TIM17_IRQHandler             [WEAK]            
                EXPORT  RTC_IRQHandler                 [WEAK]            
                EXPORT  USB0_IRQHandler                [WEAK]            
                EXPORT  USB0_DMA_IRQHandler            [WEAK]            
                EXPORT  TIM4_IRQHandler              [WEAK]            
                EXPORT  UART0_IRQHandler               [WEAK]
                EXPORT  UART1_IRQHandler               [WEAK]
                EXPORT  I2C0_IRQHandler                [WEAK]
                EXPORT  UART2_IRQHandler               [WEAK]
                EXPORT  QSPI0_IRQHandler               [WEAK]
                EXPORT  QSPI1_IRQHandler               [WEAK]
                EXPORT  QSPI2_IRQHandler               [WEAK]
                EXPORT  DMA_IRQHandler                 [WEAK]
                EXPORT  GPIO0_IRQHandler               [WEAK]
                EXPORT  GPIO1_IRQHandler               [WEAK]
                EXPORT  ADC0_IRQHandler                [WEAK]
                EXPORT  BOD_IRQHandler                 [WEAK]
                EXPORT  BOR_IRQHandler                 [WEAK]
                EXPORT  CMP_IRQHandler                 [WEAK]
		EXPORT  LED_IRQHandler               [WEAK]
		EXPORT  BITCOPY_IRQHandler               [WEAK]

WKT_IRQHandler
TIM1_IRQHandler                        
TIM15_IRQHandler                        
TIM16_IRQHandler                        
TIM17_IRQHandler                        
RTC_IRQHandler                        
USB0_IRQHandler                        
USB0_DMA_IRQHandler                        
TIM4_IRQHandler                        
UART0_IRQHandler  
UART1_IRQHandler  
I2C0_IRQHandler   
UART2_IRQHandler  
QSPI0_IRQHandler   
QSPI1_IRQHandler   
QSPI2_IRQHandler   
DMA_IRQHandler    
GPIO0_IRQHandler  
GPIO1_IRQHandler  
ADC0_IRQHandler   
BOD_IRQHandler    
BOR_IRQHandler
CMP_IRQHandler
LED_IRQHandler
BITCOPY_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

