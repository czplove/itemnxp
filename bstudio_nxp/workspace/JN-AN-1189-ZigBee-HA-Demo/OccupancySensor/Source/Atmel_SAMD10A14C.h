/**
******************************************************************************
* @file    UART.h
* @author  dongxin
* @version V1.0.0
* @date    2016/01/14,dongxin
* @brief
*
******************************************************************************
*/
#ifndef I2C_H
#define I2C_H
//-#include "hal_mcu.h"

//-#define         I2C_SCK     P0_3
//-#define         I2C_SDA     P0_2
#define I2C_SCK_PIN (1<<14)
#define I2C_SDA_PIN (1<<15)
#define I2C_SDA_DATA ((u32AHI_DioReadInput()) & I2C_SDA_PIN) ? 1 : 0

//-#define   I2C_SDA_IN()	{P0DIR &= ~0x04;}
//-#define   I2C_SDA_OUT()	{P0DIR |= 0x04;}
#define   I2C_SCK_OUT	{vAHI_DioSetDirection(0, I2C_SCK_PIN);}
#define   I2C_SDA_IN	{vAHI_DioSetDirection(I2C_SDA_PIN,0);}
#define   I2C_SDA_OUT	{vAHI_DioSetDirection(0, I2C_SDA_PIN);}

//-#define I2C_SDA_H()		(I2C_SDA=1)
//-#define I2C_SDA_L()		(I2C_SDA=0)
//-#define I2C_SCK_H()		(I2C_SCK=1)
//-#define I2C_SCK_L()		(I2C_SCK=0)
#define I2C_SDA_H		vAHI_DioSetOutput(I2C_SDA_PIN,0)
#define I2C_SDA_L		vAHI_DioSetOutput(0,I2C_SDA_PIN)
#define I2C_SCK_H		vAHI_DioSetOutput(I2C_SCK_PIN,0)
#define I2C_SCK_L		vAHI_DioSetOutput(0,I2C_SCK_PIN)

extern void I2C_Init(void);
extern uint8 I2C_ReadState(void);
extern uint8 I2C_CheckState(uint8 data);
extern void I2C_SendState(uint8 data);


#endif
