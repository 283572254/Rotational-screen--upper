#include "Y6_led.h"
#include "Y6_rcc.h"
#include "Y6_gpio.h"
#include "stdio.h"
#include "misc.h"

void LedReset(void)
{
	RCC_ResetAHBCLK(1<<AHBCLK_BIT_LED);
}

void LedSetPol(uint8_t clk_pol, uint8_t oe_pol, uint8_t hs_pol, uint8_t data_invert, uint8_t row_pol)
{
	//bit4
	if(clk_pol){
		LED->CONTROL |= 0x00000010;
	}else{
		LED->CONTROL &= 0xFFFFFFEF;
	}
	
	//bit5
	if(oe_pol){
		LED->CONTROL |= 0x00000020;
	}else{
		LED->CONTROL &= 0xFFFFFFDF;
	}
	
	//bit6
	if(hs_pol){
		LED->CONTROL |= 0x00000040;
	}else{
		LED->CONTROL &= 0xFFFFFFBF;
	}
	
	//bit7
	if(data_invert){
		LED->CONTROL |= 0x00000080;
	}else{
		LED->CONTROL &= 0xFFFFFF7F;
	}
	
	//bit8
	if(row_pol){
		LED->CONTROL |= 0x00000100;
	}else{
		LED->CONTROL &= 0xFFFFFEFF;
	}
}

void LedSetClkIdle(uint8_t clk_idle)
{
	//bit10
	if(clk_idle){
		LED->CONTROL |= 0x00000400;
	}else{
		LED->CONTROL &= 0xFFFFFBFF;
	}
}

void LedEnableBitcopy(uint8_t enable)
{
	//bit9
	if(enable){
		LED->CONTROL |= 0x00000200;
	}else{
		LED->CONTROL &= 0xFFFFFDFF;
	}
}


void LedEnableInt(uint8_t frameInt, uint8_t picInt)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//bit1
	if(frameInt){
		LED->CONTROL |= 0x00000002;
	}else{
		LED->CONTROL &= 0xFFFFFFFD;
	}
	//bit2
	if(picInt){
		LED->CONTROL |= 0x00000004;
	}else{
		LED->CONTROL &= 0xFFFFFFFB;
	}

	NVIC_InitStructure.NVIC_IRQChannel = LED_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	if(frameInt|picInt){
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	}else{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	}
	
	NVIC_Init(&NVIC_InitStructure);
}

void LedSetPin(uint8_t pinIndex, uint8_t value)
{
	uint32_t data = LED->GP[pinIndex/4];
	
	switch(pinIndex%4){
		case 0:
			data &= 0xFFFFFF00;
			data |= value;
			break;
		case 1:
			data &= 0xFFFF00FF;
			data |= (value<<8);
			break;
		case 2:
			data &= 0xFF00FFFF;
			data |= (value<<16);
			break;
		default:
			data &= 0x00FFFFFF;
			data |= (value<<24);
			break;
	}

	LED->GP[pinIndex/4] = data;
	
	if(pinIndex<32){
		//0~31
		GPIO_SetPinMux(GPIO0, 1<<pinIndex, GPIO_FUNCTION_1);
	}else if(pinIndex<43){
		//32~42=GP5_0~GP6_2
		GPIO_SetPinMux(GPIO1, 1<<(pinIndex-24), GPIO_FUNCTION_1);
	}else if(pinIndex<51){
		//43~50=GP7_0~GP7_7
		GPIO_SetPinMux(GPIO1, 1<<(pinIndex-19), GPIO_FUNCTION_1);
	}else{
		printf("pinIndex error\r\n");
	}
}

void LedSetDelay(uint8_t base, uint16_t before_hs, uint8_t hs_valid, uint16_t after_hs, uint16_t before_row, uint16_t after_row)
{
	before_hs &= 0xFFF;
	after_hs &= 0xFFF;
	before_row &= 0xFFF;
	after_row &= 0xFFF;

	LED->DELAY0 = (before_hs<<20)|(after_hs<<8)|hs_valid;
	LED->DELAY1 = (base<<24)|(after_row<<12)|before_row;
}

void LedSetClock(uint8_t low, uint8_t high)
{
	LED->COL_CLK = (high<<8)|low;
}

void LedSetRow(uint8_t with138, uint8_t rowscanCount)
{
	//bit0
	if(with138){
		LED->ROW |= 0x00000001;
	}else{
		LED->ROW &= 0xFFFFFFFE;
	}

	//bit1~6
	LED->ROW &= 0xFFFFFF81;
	LED->ROW |= ((rowscanCount-1)<<1);	//0=1 RowScan
}

void LedSetCol(uint8_t msb, uint8_t colCount, uint16_t dwCount)
{
	//bit7
	if(msb){
		LED->ROW |= 0x00000080;
  		LED->CONTROL &= ~(1 << 11);
	}else{
		LED->ROW &= 0xFFFFFF7F;
  		LED->CONTROL |= 1 << 11;
	}

	//bit8~12
	LED->ROW &= 0xFFFFE0FF;
	LED->ROW |= ((colCount-1)<<8);	//0=1 Col 假如不减一，5bit只能表示0~31个列信号

	//bit16~27
	LED->ROW &= 0xF000FFFF;
	LED->ROW |= (dwCount<<16);
}

void LedSetLatchClkNum(uint8_t clkNum)
{
	//bit28~31
	LED->ROW &= 0x0FFFFFFF;
	LED->ROW |= (clkNum<<28);
}

void LedSetPwm(uint32_t clkInPeriod, uint16_t periodInBase)
{
	//bit10~12
	LED->CONTROL &= 0xFFFFE3FF;
	LED->PWM_CTRL = (periodInBase<<24)|clkInPeriod;
}

void LedSetGrayPwm(uint8_t gray, uint32_t activeInPeriod)
{
	LED->GL_PWM_CTRL[gray] = activeInPeriod;
}

//addr is [31:16]
void LedSetAddrBase(uint16_t baseAddr)
{
	LED->CONTROL &= 0x0000FFFF;
	LED->CONTROL |= (baseAddr<<16);
}

//一次设置8个灰度,scan0在高位
void LedSetScanGrey(uint8_t scan, uint32_t grey)
{
	LED->SCAN_GREY[scan] = grey;
}

//totalScanNum一共多少灰度,scanNumInRow:一个行循环内包含多少灰度
void LedSetScanNumber(uint8_t totalScanNum, uint8_t scanNumInRow)
{
	LED->SCAN_NUM = (scanNumInRow-1)|((totalScanNum-1)<<8);
}

uint8_t LedGetLoopCount(void)
{
	uint8_t totalScanNum;
	uint8_t scanNumInRow;

	scanNumInRow = (LED->SCAN_NUM & 0x7F)+1;
	totalScanNum = ((LED->SCAN_NUM>>8) & 0x7F)+1;
	return (totalScanNum+scanNumInRow-1)/scanNumInRow;
}

uint8_t LedGetScanGrey(uint8_t scan)
{
	uint32_t data = LED->SCAN_GREY[scan/8];
	data >>= 28-(scan%8)*4;
	return data&0xF;
}

//greyArray.size >= scanNumInRow
uint8_t LedGetGreyArray(uint8_t loopIndex, uint8_t* greyArray)
{
	uint8_t scanNumInRow,count;
	uint8_t i,grey;
	uint8_t totalScanNum;
		
	scanNumInRow = (LED->SCAN_NUM & 0x7F)+1;
	totalScanNum = ((LED->SCAN_NUM>>8) & 0x7F)+1;
	count=0;
	
	for(i=scanNumInRow*loopIndex;i<scanNumInRow*loopIndex+scanNumInRow;i++){
		if(i>=totalScanNum){
			break;
		}
		grey = LedGetScanGrey(i);
		if(count==0 || greyArray[count-1] != grey){
			greyArray[count] = grey;
			count++;
		}
	}
	return count;
}

//addr is [15:8]
void LedSetAddrPic0(uint32_t foregroundAddr, uint32_t backgroundAddr, uint32_t maskAddr)
{
	LED->PIC0_ADR = 0;
	
	if(foregroundAddr & 0xFF){
		printf("pic0 FAddr error\r\n");
	}
	LED->PIC0_ADR |= (foregroundAddr>>8)&0xFF;
	
	if(backgroundAddr & 0xFF){
		printf("pic0 BAddr error\r\n");
	}
	LED->PIC0_ADR |= (backgroundAddr)&0xFF00;
	
	if(maskAddr & 0xFF){
		printf("pic0 MAddr error\r\n");
	}
	LED->PIC0_ADR |= (maskAddr<<8)&0xFF0000;
}

//addr is [15:8]
void LedSetAddrPic1(uint32_t foregroundAddr, uint32_t backgroundAddr, uint32_t maskAddr)
{
	LED->PIC1_ADR = 0;
	
	if(foregroundAddr & 0xFF){
		printf("pic1 FAddr error\r\n");
	}
	LED->PIC1_ADR |= (foregroundAddr>>8)&0xFF;
	
	if(backgroundAddr & 0xFF){
		printf("pic1 BAddr error\r\n");
	}
	LED->PIC1_ADR |= (backgroundAddr)&0xFF00;
	
	if(maskAddr & 0xFF){
		printf("pic1 MAddr error\r\n");
	}
	LED->PIC1_ADR |= (maskAddr<<8)&0xFF0000;
}

void pic0IsReady(uint16_t displayTimes)
{
	LED->PIC0_CTRL = 0x10000|displayTimes;
}

void pic1IsReady(uint16_t displayTimes)
{
	LED->PIC1_CTRL = 0x10000|displayTimes;
}

int LedRun(void)
{
	//check PWM time >= data time
	uint32_t pwmTimes;
	uint32_t dataTimes;

	pwmTimes = (LED->PWM_CTRL >> 24)&0xFF;		//PWM_BASE
	pwmTimes *= (LED->PWM_CTRL & 0xFFFFF);		//PWM_PERIOD

	dataTimes = (LED->COL_CLK >> 8)&0xFF;		//HIGH
	dataTimes += (LED->COL_CLK & 0xFF);			//LOW
	dataTimes *= ((LED->ROW >> 16)&0xFFF)<<5;	//CS_CNT

	if(pwmTimes<dataTimes){
		printf("Error : PWM time < data time\r\n");
		return -1;
	}

	LED->CONTROL |= 0x1;
	return 0;
}

void LedStop(void)
{
	LED->CONTROL &= 0xFFFFFFFE;
}

uint8_t LedGetCurrentPic(void)
{
	if(LED->STATUS & 0x4)
		return 0;
	else
		return 1;
}

/*
default Rule:
	greyCount=1		PWM0=1		GreyArray=0
	greyCount=2		PWM0=1/2	GreyArray=10
	greyCount=3		PWM0=1/2	GreyArray=2210
	greyCount=4		PWM0=1/4	GreyArray=33210
	
	greyCount=5		PWM0=1/4	GreyArray=44440+3321
	greyCount=6		PWM0=1/8	GreyArray=55550+44321
	
	greyCount=7		PWM0=1/8	GreyArray=66660+66661+55552+443
	greyCount=8		PWM0=1/16	GreyArray=77770+77771+66662+5543
	
	greyCount=9		PWM0=1/16	GreyArray=888880+888881+888882+877773+777745+66665
	greyCount=10	PWM0=1/32	GreyArray=999990+999991+999992+988883+888845+777766
	
	greyCount=11	PWM0=1/32	GreyArray=AAAAAAAA0+AAAAAAAA1+AAAAAAAA2+AAAAAAAA3+999999994+999999995+888888886+77776
	greyCount=12	PWM0=1/64	GreyArray=BBBBBBBB0+BBBBBBBB1+BBBBBBBB2+BBBBBBBB3+AAAAAAAA4+AAAAAAAA5+999999996+888877

clkInPeriod:
	20 bit : 1PWM has how many 96M clk
*/
void LedSetDefaultGreyArray(uint8_t greyCount, uint32_t clkInPeriod)
{
	uint8_t times;
	int i;

	if(greyCount<1 || greyCount>12){
		printf("Error greyCount\r\n");
		return;
	}

	LedSetPwm(clkInPeriod, 1);

	times=1;
	for(i=greyCount/2;i<greyCount;i++){
		LedSetGrayPwm(i, clkInPeriod);
		times *= 2;
	}

	for(i=greyCount/2;i>=0;i--){
		LedSetGrayPwm(i, clkInPeriod);
		clkInPeriod /= 2;
	}

	switch(greyCount){
		case 12:
			LedSetScanNumber(69, 9);
			LedSetScanGrey(0, 0xBBBBBBBB);
			LedSetScanGrey(1, 0x0BBBBBBB);
			LedSetScanGrey(2, 0xB1BBBBBB);
			LedSetScanGrey(3, 0xBB2BBBBB);
			LedSetScanGrey(4, 0xBBB3AAAA);
			LedSetScanGrey(5, 0xAAAA4AAA);
			LedSetScanGrey(6, 0xAAAAA599);
			LedSetScanGrey(7, 0x99999968);
			LedSetScanGrey(8, 0x88877000);
			break;
		case 11:
			LedSetScanNumber(68, 9);
			LedSetScanGrey(0, 0xAAAAAAAA);
			LedSetScanGrey(1, 0x0AAAAAAA);
			LedSetScanGrey(2, 0xA1AAAAAA);
			LedSetScanGrey(3, 0xAA2AAAAA);
			LedSetScanGrey(4, 0xAAA39999);
			LedSetScanGrey(5, 0x99994999);
			LedSetScanGrey(6, 0x99999588);
			LedSetScanGrey(7, 0x88888867);
			LedSetScanGrey(8, 0x77760000);
			break;
		case 10:
			LedSetScanNumber(36, 6);
			LedSetScanGrey(0, 0x99999099);
			LedSetScanGrey(1, 0x99919999);
			LedSetScanGrey(2, 0x92988883);
			LedSetScanGrey(3, 0x88884577);
			LedSetScanGrey(4, 0x77660000);
			break;
		case 9:
			LedSetScanNumber(35, 6);
			LedSetScanGrey(0, 0x88888088);
			LedSetScanGrey(1, 0x88818888);
			LedSetScanGrey(2, 0x82877773);
			LedSetScanGrey(3, 0x77774566);
			LedSetScanGrey(4, 0x66500000);
			break;
		case 8:
			LedSetScanNumber(19, 5);
			LedSetScanGrey(0, 0x77770777);
			LedSetScanGrey(1, 0x71666625);
			LedSetScanGrey(2, 0x53400000);
			break;
		case 7:
			LedSetScanNumber(18, 5);
			LedSetScanGrey(0, 0x66660666);
			LedSetScanGrey(1, 0x61555524);
			LedSetScanGrey(2, 0x43000000);
			break;
		case 6:
			LedSetScanNumber(10, 5);
			LedSetScanGrey(0, 0x55550443);
			LedSetScanGrey(1, 0x21000000);
			break;
		case 5:
			LedSetScanNumber(9, 5);
			LedSetScanGrey(0, 0x44440332);
			LedSetScanGrey(1, 0x10000000);
			break;
		case 4:
			LedSetScanNumber(5, 5);
			LedSetScanGrey(0, 0x33210000);
			break;
		case 3:
			LedSetScanNumber(4, 4);
			LedSetScanGrey(0, 0x22100000);
			break;
		case 2:
			LedSetScanNumber(2, 2);
			LedSetScanGrey(0, 0x10000000);
			break;
		default:
			LedSetScanNumber(1, 1);
			LedSetScanGrey(0, 0x00000000);
			break;
	}

}

