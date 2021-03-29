#ifndef _USER_H
#define _USER_H
#include "main.h"

extern uint8_t BLEbuff[10];
extern uint8_t TarWeigh[3];
extern uint8_t TarMode;
extern uint8_t InitFlag;

void WeighInit(void);
void WeighCount(uint32_t data);
void WeighDisplay(uint32_t data);
void getBLEdata(uint8_t *bleData);
#endif

