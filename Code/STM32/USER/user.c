#include "user.h"
#include "HX711.h"
#include "TM1650.h"
#include <stdio.h>
#include <string.h>
#include "SYN6288.h"

#define NUM 5
uint8_t BLEbuff[10]={0};
uint32_t BasicsVal=7942000;
uint32_t ErrVal=12600;

uint16_t WeighStr[NUM]={0};

uint8_t TarWeigh[3]={45,45,45};
uint8_t TarMode=3;
uint8_t InitFlag=0;

void WeighInit(void)
{
	static uint32_t Weigh=0;
	static uint32_t val=0;
	for(int i=0;i<10;i++)
	{
		val=Read_Weigh();
		Weigh=Weigh+val;		
		HAL_Delay(100);
	}
	BasicsVal=Weigh/10;
	Weigh=0;
}

void WeighDisplay(uint32_t data)
{
	DisplayNumber_4BitDig(data);
		
}

void WeighCount(uint32_t data)
{
//	static uint8_t num=0;
	static uint16_t timeflag=0,weighflag=0;	
	static uint32_t Weigh=0,WeighArr[10];
	static uint32_t val=0;
  static char spkStr[30];
	for(int i=0;i<NUM;i++)
	{
		val=Read_Weigh();
		if(val>BasicsVal)
		{
			if((val-BasicsVal)>1000)
			{
				Weigh=Weigh+(val-BasicsVal)*100/ErrVal;
			}
			else
			{
				Weigh=0;
			}
			
		}
		else
		{
			Weigh=0;
		}
			
		HAL_Delay(100);
	}
	
	Weigh=Weigh/NUM;
	
	if(Weigh==0)
	{
		weighflag=0;
		timeflag=timeflag<20?(timeflag+1):20;
	
	}
	else
	{
		timeflag=0;
	}
		
	if(timeflag>10)
	{
		DisplayOff();
	}
	else
	{	
		if(TarMode==1)
		{
			if(Weigh < TarWeigh[0]*100)
			{
				WeighArr[weighflag]=Weigh;
			}
			else
			{
				WeighArr[weighflag]=TarWeigh[0]*200 + Weigh%1000;
			}
		
		}
		else
		{
			WeighArr[weighflag]=((Weigh+5)/10)*10;
		}
		if(weighflag<5)
		{		
			WeighDisplay(WeighArr[weighflag]/2);	
	    weighflag++;			
		}
		else
		{	
			
			if(WeighArr[weighflag]>0 && weighflag==5 )//&&!HAL_GPIO_ReadPin(R_B_GPIO_Port,R_B_Pin)
			{			
				
				if(TarMode==2)
				{
					WeighDisplay(WeighArr[weighflag]/2);
					if(WeighArr[weighflag]/2 > TarWeigh[1]*100)
					{
						SYN_FrameInfo(0,(uint8_t*)"您的体重是",3);			
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);				
						sprintf(spkStr,"%.2f%s",(float)(WeighArr[weighflag]/2)/100,"千克" );
						SYN_FrameInfo(0,(uint8_t*)spkStr,3);	
						HAL_Delay(3000);							
						SYN_FrameInfo(0,(uint8_t*)"注意减肥",3);
						HAL_Delay(1500);			
					}
					else
					{
						SYN_FrameInfo(0,(uint8_t*)"您的体重是",2);			
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);				
						sprintf(spkStr,"%.2f%s",(float)(WeighArr[weighflag]/2)/100,"千克" );
						SYN_FrameInfo(0,(uint8_t*)spkStr,2);	
						HAL_Delay(3000);	
	
					}
				
				}			
				else if(TarMode==3)
				{
					
					if(WeighArr[weighflag]/2 > TarWeigh[2]*100)
					{	
						
						//WeighDisplay(11*WeighArr[weighflag]/20+(WeighArr[weighflag]/2)%1000/2);
						WeighDisplay((WeighArr[weighflag]+(WeighArr[weighflag]/1000+WeighArr[weighflag]%1000/100)*50)/2);
						
						SYN_FrameInfo(0,(uint8_t*)"您的体重是",2);		
						SYN_FrameInfo(0,(uint8_t*)"您的体重是",3);								
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay((WeighArr[weighflag]+(WeighArr[weighflag]/1000+WeighArr[weighflag]%1000/100)*50)/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay((WeighArr[weighflag]+(WeighArr[weighflag]/1000+WeighArr[weighflag]%1000/100)*50)/2);								
						sprintf(spkStr,"%.2f%s",(float)(WeighArr[weighflag]+(WeighArr[weighflag]/1000+WeighArr[weighflag]%1000/100)*50)/200,"千克" );
						SYN_FrameInfo(0,(uint8_t*)spkStr,2);	
						SYN_FrameInfo(0,(uint8_t*)spkStr,3);	
						HAL_Delay(3000);	
						SYN_FrameInfo(0,(uint8_t*)"你真胖",2);		
						SYN_FrameInfo(0,(uint8_t*)"你真胖",3);	
						HAL_Delay(1500);	
//						SYN_FrameInfo(0,(uint8_t*)"注意减肥",2);		
//						SYN_FrameInfo(0,(uint8_t*)"注意减肥",3);	
						
					}
					else
					{
						WeighDisplay(WeighArr[weighflag]/2);
//						SYN_FrameInfo(0,(uint8_t*)"您的体重是",2);			
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);				
//						sprintf(spkStr,"%.2f%s",(float)(WeighArr[weighflag]/2)/100,"千克" );
//						SYN_FrameInfo(0,(uint8_t*)spkStr,2);	
//						HAL_Delay(3000);	
					}
				}
				else
				{				
						WeighDisplay(WeighArr[weighflag]/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);
						HAL_Delay(500);
						DisplayOff();
						HAL_Delay(500);
						WeighDisplay(WeighArr[weighflag]/2);	
				}
				weighflag++;
			}		
		}
	
	}
	printf("%d\t%d\t",val,(val-BasicsVal));
	printf("%d\r\n",Weigh);
	Weigh=0;
}

void getBLEdata(uint8_t *bleData)
{
	if(bleData[0] == 0xAA && bleData[2] == 0xAA )
	{		
		TarMode=bleData[1];
	
	}
	else if(bleData[0] == 0x5A && bleData[3] == 0x5A )
	{		
		TarWeigh[bleData[1]-1]=bleData[2];	
	}
	else if(bleData[0] == 0xFF && bleData[2] == 0xFF )
	{
		InitFlag=1;
	}
}



