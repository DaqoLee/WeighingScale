#ifndef _MYIIC_H
#define _MYIIC_H
#include "main.h"

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)0x80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)0x30000000;}

//IO操作
#define SCL_H    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)//PBout(6) //SCL
#define SCL_L    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)//PBout(6) //SCL

#define SDA_H    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)//PBout(7) //SDA	 
#define SDA_L    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)//PBout(7) //SDA	

#define READ_SDA HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)//PBin(7)  //输入SDA 

//IIC所有操作函数			 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
void MyIICInit(void);
#endif

