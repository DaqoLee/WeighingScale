#include "HX711.h"
#include "delay.h"

uint32_t Read_Weigh(void)
{
	uint8_t i;
	uint32_t value = 0;
	
	/**
	�����ֲ�д��������������ܽ� DOUT Ϊ�ߵ�ƽʱ������A/D ת������δ׼����������ݣ���ʱ����ʱ
	�������ź� PD_SCK ӦΪ�͵�ƽ������������������״̬��
	**/
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	/**
	�ȴ�DT���ű�Ϊ�ߵ�ƽ
	**/
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15));
	delay_us(1);
	
	/**
	�� DOUT �Ӹߵ�ƽ��͵�ƽ��PD_SCK Ӧ���� 25 �� 27 �����ȵ�ʱ������
	25��ʱ������ ---> ͨ��A ����128
	26��ʱ������ ---> ͨ��B ����32
	27��ʱ������ ---> ͨ��A ����64
	**/
	for(i=0; i<24; i++) //24λ������ݴ����λ�����λ��λ������
	{
//		//����һ��
//		GPIO_SetBits(GPIOB, GPIO_Pin_6); //ʱ�Ӹߵ�ƽ
//		value = value << 1; //���DTλΪ������һλ
//		delay_us(1);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //ʱ�ӵ͵�ƽ
//		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
//			value++; //���DTλΪ�ߣ�ֵ+1
//		delay_us(1);
		

		//��������
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
	
	//�� 25�� 27 ��ʱ����������ѡ����һ�� A/D ת��������ͨ��������
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	value = value^0x800000; 
	delay_us(1); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	delay_us(1);  
	return value; 	
}





