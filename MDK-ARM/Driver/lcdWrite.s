;;******************** (C) COPYRIGHT 2012 ALPSCALE ********************
;;* ���  д���ݵ�LCD
;;*******************************************************************************
	
;LCD_WR_SET_ADDR      EQU     0x40020004;����WR��GPIO��ַ
;LCD_WR_CLR_ADDR      EQU     0x40020008;����
;LCD_WR_PIN           EQU     0x00000010;WR pin  pin4 ���� 0x00000010
;LCD_DATA_PORT        EQU     0x40020000;LCD�����߶˿ڼĴ���
	
	
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
				;LDMIA R0!, {R6,R7};//R0 �����FLASH���ݵ�ַָ�룬һ���Լ���8���ֽ�  4�����ص�����ݵ�CPU �Ĵ���
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
				
				;SUBS R1, R1, #4;//R1 �������Ҫд��Ĵ���
				;BNE  writeLoops
				;POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				;BX   lr	
				;NOP
				
				
				;END


;******************** (C) COPYRIGHT 2012 ALPSCALE ********************
;* ���  д���ݵ�LCD
;*******************************************************************************
	
LCD_WR_SET_ADDR      EQU     0x40020004;����WR��GPIO��ַ
LCD_WR_CLR_ADDR      EQU     0x40020008;����
LCD_WR_PIN           EQU     0x00000010;WR pin  pin4 ���� 0x00000010
LCD_DATA_PORT        EQU     0x40020000;LCD�����߶˿ڼĴ���
	
	
			AREA    |.text|, CODE, READONLY
				THUMB
		
LCD_WriteOneData  ;ֻ����WR�����ź�
				EXPORT LCD_WriteOneData	
				PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}  	;     Push registers,
                LDR  R2, =LCD_WR_CLR_ADDR
				LDR  R3, =LCD_WR_SET_ADDR
				LDR R4, =LCD_WR_PIN
				LDR  R5, =LCD_DATA_PORT
                LSLS R6, R0, #8  ;��R0��ֵ����8λ����R6��
                LSLS R7, R0, #16  ;��R0��ֵ����16λ����R7�� 
	
writeLoop
				
                STR  R6, [R5]   ;��R6��ֵ������R5Ϊ��ַ���ڴ��У�������
                STR  R4, [R2]
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����
                STR  R7, [R5]   ;��R7��ֵ������R5Ϊ��ַ���ڴ��У�������  
                STR  R4, [R2]
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����
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
				LDMIA R0!, {R6,R7};//R0 �����FLASH���ݵ�ַָ�룬һ���Լ���8���ֽ�  4�����ص�����ݵ�CPU �Ĵ���  R6
				;MOVS R2, #0x00
				LSLS R2, R6, #16  ;��R6��ֵ����16λ����R2��
				STR  R2, [R5]   ;��R2��ֵ������R5Ϊ��ַ���ڴ��У�������
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����
                
                ;MOVS R2, #0x00
				LSRS R2, R2, #8 
				STR  R2, [R5]   ;��R2��ֵ������R5Ϊ��ַ���ڴ��У�������
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����
				

				LSRS R2, R6, #16  ;��R6��ֵ����16λ����R2��
				LSLS R2, R2, #16  
				STR  R2, [R5]   ;��R2��ֵ������R5Ϊ��ַ���ڴ��У�������
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����

				LSRS R2, R2, #8  
				STR  R2, [R5]   ;��R2��ֵ������R5Ϊ��ַ���ڴ��У�������
				STR  R4, [R3]   ;��R4��ֵ������R3Ϊ��ַ���ڴ��У���WR����

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
				
				SUBS R1, R1, #4;//R1 �������Ҫд��Ĵ���
				BNE  writeLoops
				POP {R0, R1, R2, R3, R4, R5, R6, R7, PC}  	;     Push registers,
				BX   lr	
				NOP 
				END


