#include "HX711.h"
#include "delay.h"

uint32_t Read_Weigh(void)
{
	uint8_t i;
	uint32_t value = 0;
	
	/**
	数据手册写到，当数据输出管脚 DOUT 为高电平时，表明A/D 转换器还未准备好输出数据，此时串口时
	钟输入信号 PD_SCK 应为低电平，所以下面设置引脚状态。
	**/
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	/**
	等待DT引脚变为高电平
	**/
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15));
	delay_us(1);
	
	/**
	当 DOUT 从高电平变低电平后，PD_SCK 应输入 25 至 27 个不等的时钟脉冲
	25个时钟脉冲 ---> 通道A 增益128
	26个时钟脉冲 ---> 通道B 增益32
	27个时钟脉冲 ---> 通道A 增益64
	**/
	for(i=0; i<24; i++) //24位输出数据从最高位至最低位逐位输出完成
	{
//		//方法一：
//		GPIO_SetBits(GPIOB, GPIO_Pin_6); //时钟高电平
//		value = value << 1; //如果DT位为低左移一位
//		delay_us(1);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //时钟低电平
//		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
//			value++; //如果DT位为高，值+1
//		delay_us(1);
		

		//方法二：
	//	GPIO_SetBits(GPIOB, GPIO_Pin_15);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		delay_us(1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == 0)
		{
			value = value << 1;
			value |= 0x00;
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == 1)
		{
			value = value << 1;
			value |= 0x01;
		}
		delay_us(1);
	}
	
	//第 25至 27 个时钟脉冲用来选择下一次 A/D 转换的输入通道和增益
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	value = value^0x800000; 
	delay_us(1); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	delay_us(1);  
	return value; 	
}





