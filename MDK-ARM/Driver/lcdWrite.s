;;******************** (C) COPYRIGHT 2012 ALPSCALE ********************
;;* 汇编  写数据到LCD
;;*******************************************************************************
	
;LCD_WR_SET_ADDR      EQU     0x40020004;拉高WR的GPIO地址
;LCD_WR_CLR_ADDR      EQU     0x40020008;拉低
;LCD_WR_PIN           EQU     0x00000010;WR pin  pin4 就是 0x00000010
;LCD_DATA_PORT        EQU     0x40020000;LCD数据线端口寄存器
	
	
			;AREA    |.text|, CODE, READONLY
				;THUMB
		
;LCD_WriteOneData  
				;EXPORT LCD_WriteOneData	
				;PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}  	;     Push registers,
				;LDR  R1, =LCD_WR_SET_ADDR
				;LDR  R2, =LCD_WR_CLR_ADDR
				;MOVS R3, #LCD_WR_PIN
	
;writeLoop
				;STR  R3, [R2]
				;STR  R3, [R1]
				;SUBS R0, R0, #1
				;BNE  writeLoop
				;POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				;BX   lr
				
;;LCD_WriteOneDatas  
				;;EXPORT LCD_WriteOneDatas	
				;;LDR  R3, =LCD_WR_SET_ADDR
				;;MOVS R4, #LCD_WR_PIN
				;;LDR  R5, =LCD_DATA_PORT
				;;;LDR  R2, lr
;;writeLoops
				;;LDRH R6, [R0]
				;;LSLS R6, R6, #16
				;;STR  R6, [R5]
				;;STR  R4, [R3]
				;;ADDS R0, R0, #2
				;;SUBS R1, R1, #1
				;;BNE  writeLoops
				;;BX   lr	
				;;NOP
				
;LCD_WriteDatas  
				;EXPORT LCD_WriteDatas
				;PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}  	;     Push registers,
				;LDR  R3, =LCD_WR_SET_ADDR
				;MOVS R4, #LCD_WR_PIN
				;LDR  R5, =LCD_DATA_PORT
;writeLoops
				;LDMIA R0!, {R6,R7};//R0 传入的FLASH数据地址指针，一次性加载8个字节  4个像素点的数据到CPU 寄存器
				;;MOVS R2, #0x00
				;LSLS R2, R6, #16
				;STR  R2, [R5]
				;STR  R4, [R3]
				
				;;MOVS R2, #0x00
				;LSRS R2, R6, #16
				;LSLS R2, R2, #16
				;STR  R2, [R5]
				;STR  R4, [R3]
				
				;;MOVS R2, #0x00
				;LSLS R2, R7, #16
				;STR  R2, [R5]
				;STR  R4, [R3]
				
				;;MOVS R2, #0x00
				;LSRS R2, R7, #16
				;LSLS R2, R2, #16
				;STR  R2, [R5]
				;STR  R4, [R3]
				
				;SUBS R1, R1, #4;//R1 传入的需要写入的次数
				;BNE  writeLoops
				;POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				;BX   lr	
				;NOP
				
				
				;END


;******************** (C) COPYRIGHT 2012 ALPSCALE ********************
;* 汇编  写数据到LCD
;*******************************************************************************
	
LCD_WR_SET_ADDR      EQU     0x40020004;拉高WR的GPIO地址
LCD_WR_CLR_ADDR      EQU     0x40020008;拉低
LCD_WR_PIN           EQU     0x00000010;WR pin  pin4 就是 0x00000010
LCD_DATA_PORT        EQU     0x40020000;LCD数据线端口寄存器
	
	
			AREA    |.text|, CODE, READONLY
				THUMB
		
LCD_WriteOneData  ;只给个WR脉冲信号
				EXPORT LCD_WriteOneData	
				PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}  	;     Push registers,
                LDR  R2, =LCD_WR_CLR_ADDR
				LDR  R3, =LCD_WR_SET_ADDR
				LDR R4, =LCD_WR_PIN
				LDR  R5, =LCD_DATA_PORT
                LSLS R6, R0, #8  ;把R0的值左移8位放入R6中
                LSLS R7, R0, #16  ;把R0的值左移16位放入R7中 
	
writeLoop
				
                STR  R6, [R5]   ;把R6的值传入以R5为地址的内存中，给数据
                STR  R4, [R2]
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲
                STR  R7, [R5]   ;把R7的值传入以R5为地址的内存中，给数据  
                STR  R4, [R2]
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲
				SUBS R1, R1, #1 ;R0=R0-1;
				BNE  writeLoop
				POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				BX   lr
				
;LCD_WriteOneDatas  
				;EXPORT LCD_WriteOneDatas	
				;LDR  R3, =LCD_WR_SET_ADDR
				;MOVS R4, #LCD_WR_PIN
				;LDR  R5, =LCD_DATA_PORT
				;;LDR  R2, lr
;writeLoops
				;LDRH R6, [R0]
				;LSLS R6, R6, #16
				;STR  R6, [R5]
				;STR  R4, [R3]
				;ADDS R0, R0, #2
				;SUBS R1, R1, #1
				;BNE  writeLoops
				;BX   lr	
				;NOP
				
LCD_WriteDatas  
				EXPORT LCD_WriteDatas
				PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}  	;     Push registers,
				LDR  R3, =LCD_WR_SET_ADDR
				LDR R4, =LCD_WR_PIN
				LDR  R5, =LCD_DATA_PORT
writeLoops
				LDMIA R0!, {R6,R7};//R0 传入的FLASH数据地址指针，一次性加载8个字节  4个像素点的数据到CPU 寄存器  R6
				;MOVS R2, #0x00
				LSLS R2, R6, #16  ;把R6的值左移16位放入R2中
				STR  R2, [R5]   ;把R2的值传入以R5为地址的内存中，给数据
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲
                
                ;MOVS R2, #0x00
				LSRS R2, R2, #8 
				STR  R2, [R5]   ;把R2的值传入以R5为地址的内存中，给数据
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲
				

				LSRS R2, R6, #16  ;把R6的值右移16位放入R2中
				LSLS R2, R2, #16  
				STR  R2, [R5]   ;把R2的值传入以R5为地址的内存中，给数据
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲

				LSRS R2, R2, #8  
				STR  R2, [R5]   ;把R2的值传入以R5为地址的内存中，给数据
				STR  R4, [R3]   ;把R4的值传入以R3为地址的内存中，给WR脉冲

				;MOVS R2, #0x00
				LSLS R2, R7, #16
				STR  R2, [R5]
				STR  R4, [R3]
				
                LSRS R2, R2, #8
				STR  R2, [R5]
				STR  R4, [R3]				
				
                ;MOVS R2, #0x00
				LSRS R2, R7, #16
				LSLS R2, R2, #16
				STR  R2, [R5]
				STR  R4, [R3]

				LSRS R2, R2, #8
				STR  R2, [R5]
				STR  R4, [R3]
				
				SUBS R1, R1, #4;//R1 传入的需要写入的次数
				BNE  writeLoops
				POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				BX   lr	
				NOP 
				END


