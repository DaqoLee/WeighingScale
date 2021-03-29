#include "TM1650.h"
#include "delay.h"
#include "myiic.h"
/**
  ******************************************************************************
  * @file           : TM1650.c
  * @brief          :  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */	
//段码数据表
const volatile uint8_t Digital_Table[11] = { 
0x3F, //0
0x06, //1
0x5B, //2
0x4F, //3
0x66, //4
0x6D, //5
0x7D, //6
0x07, //7
0x7F, //8
0x6F, //9
//0x80, //9
0x00  //'null '
};	

const volatile uint8_t Digital_Table2[11] = { 
0x3F|0x80, //0
0x06|0x80, //1
0x5B|0x80, //2
0x4F|0x80, //3
0x66|0x80, //4
0x6D|0x80, //5
0x7D|0x80, //6
0x07|0x80, //7
0x7F|0x80, //8
0x6F|0x80, //9
//0x80, //9
0x00  //'null '
};	
	
//写入数码管的四位变量
uint8_t Dig1_Data=0;
uint8_t Dig2_Data=0;
uint8_t Dig3_Data=0;
uint8_t Dig4_Data=0;	
	

//=============================================================================
//Function:	TM1650_SendCommand  
//note: Set TM1650 Command1&Command2
//Input:		CMD1,数据命令:48H。
//					CMD2,开显示，显示亮度级
//Output:	none
//Remark: none
//=============================================================================
void TM1650_SendCommand(uint8_t CMD1,uint8_t CMD2)
{	
  IIC_Start();
	IIC_Send_Byte(CMD1);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD2);
	IIC_Wait_Ack();
	IIC_Stop(); 
}





//=============================================================================
//Function:	Aip650_SendDigData  
//note: 发送Dat到Dig
//Input:		Dig,显存地址
//					Dat,显示数据
//Output:	none
//Remark: none
//=============================================================================
void Aip650_SendDigData(uint8_t Dig,uint8_t Dat)
{	
  IIC_Start();
	IIC_Send_Byte(Dig);
	IIC_Wait_Ack();
	IIC_Send_Byte(Dat);
	IIC_Wait_Ack();
	IIC_Stop(); 
}





//=============================================================================
//Function:	TM1650_Init  
//note: TM1650 初始化
//Input:	none
//Output:	none
//Remark: none
//=============================================================================
void TM1650_Init(void)
{
	delay_init(72);
	delay_ms(100);
	SCL_H;
	SDA_H;
	delay_ms(100);
	TM1650_SendCommand(0x48,0x71);
	
}

//=============================================================================
//Function:	DisplayNumber_4BitDig  
//note: 	设置4位数码管数据
//Input:	显示的4位数据
//Output:	none
//Remark: none
//=============================================================================
void DisplayNumber_4BitDig(uint16_t num)
{
	
	Dig1_Data=Digital_Table[num/1000];
	if(num==0)
	{
		Dig2_Data=Digital_Table[num/100%10];	
	}
	else
	{
		Dig2_Data=Digital_Table2[num/100%10];	
	}
		
	Dig3_Data=Digital_Table[num/10%10];
	Dig4_Data=Digital_Table[num%10];
	
	DigitalScan();
}

void DisplayNumber(uint16_t num)
{
	
	Dig1_Data=Digital_Table[num/1000];
	Dig2_Data=Digital_Table[num/100%10];	
	Dig3_Data=Digital_Table[num/10%10];
	Dig4_Data=Digital_Table[num%10];
	
	DigitalScan();
}


void DisplayOff(void)
{
	
	Dig1_Data=Digital_Table[10];
	Dig2_Data=Digital_Table[10];	
	Dig3_Data=Digital_Table[10];
	Dig4_Data=Digital_Table[10];
	DigitalScan();
}




//=============================================================================
//Function:	DigitalScan  
//note: 	数码管扫描
//Input:	none
//Output:	none
//Remark: none
//=============================================================================
void DigitalScan( void )  
{

	Aip650_SendDigData(DIG0,Dig1_Data);
	Aip650_SendDigData(DIG1,Dig2_Data);
	Aip650_SendDigData(DIG2,Dig3_Data);
	Aip650_SendDigData(DIG3,Dig4_Data);	
}
