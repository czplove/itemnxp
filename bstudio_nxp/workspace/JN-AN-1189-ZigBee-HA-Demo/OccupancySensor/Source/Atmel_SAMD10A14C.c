/*******************************************************************************
* @file   UART.c
* @author  dongxin
* @version V1.0.0
* @date    2016/01/14,dongxin
* @brief
*
*******************************************************************************/
#include <jendefs.h>
#include "AppHardwareApi_JN516x.h"
#include "app_events.h"
#include "app_event_handler.h"
#include "Atmel_SAMD10A14C.h"

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8 I2C_ReadState();
uint8 I2C_CheckState(uint8 data);
void I2C_SendState(uint8 data);
void Delay_us(uint32 number);

uint8 LoadState;

extern void Delay (uint32 u32DelayUs);

#define Delay_us	Delay		
/**********************************************************************
函    数:
功    能：
说    明：
参    数：
返 回 值：
***********************************************************************/
void I2C_Init(void)                   //IO初始化
{
  /*SDA*/
  //P0SEL &= ~0x04; 
  /*SCK*/
  //-P0SEL &= ~0x08;
  //-P0DIR |= 0x08;
  I2C_SCK_OUT;
  I2C_SCK_H;
}
/**********************************************************************
函    数:
功    能：
说    明：
参    数：
返 回 值：
***********************************************************************/
uint8 I2C_ReadState(void)
{
  uint8 RecData = 0X00;  
  uint8 i,temp_data;
  /*读取当前状态*/
  I2C_SDA_IN;
  for(i = 0;i < 4;i++)
  {
    RecData <<= 1;
    I2C_SCK_L;
    Delay_us(5);
    temp_data = I2C_SDA_DATA;
    RecData |= temp_data;
    Delay_us(2); 
    
    RecData <<= 1;
    I2C_SCK_H;
    Delay_us(5);
    temp_data = I2C_SDA_DATA;
    RecData |= temp_data;
    Delay_us(2);
  } 
  return RecData;
}
/**********************************************************************
函    数:
功    能：
说    明：
参    数：
返 回 值：
***********************************************************************/
uint8 I2C_CheckState(uint8 data)
{
  uint8 keys = 0;
  uint8 RecData = 0X00; 
  RecData = data;
  /*读取数据格式0xYY*/
  /*读取数据 Temp 最高位为1,则表示数据读取正确*/
  if(RecData & 0X80 )
  { 
    /*LoadState:  1 l1 l2 L3 S K1  K2  K3(S:表示led显示状态)*/
    /*RecData:    1 0  0  0  0 K1  K2  K3*/
    if(RecData & 0X04)
    {
      keys = SW1_PRESSED;
      //-if(halShift == HAL_KEY_STATE_NORMAL)
      {
        if(LoadState & 0x40)
        {  
          LoadState &= ~(0x01<<6); 
        }
        else
        {
          LoadState |= (0x01<<6);
        }
      }
    }
    else if(RecData & 0X02)
    {
      keys = SW2_PRESSED;
      //-if(halShift == HAL_KEY_STATE_NORMAL)
      {      
        if(LoadState & 0x20)
        {  
          LoadState &= ~(0x01<<5); 
        }
        else
        {
          LoadState |= (0x01<<5);
        }
      }
    }
    else if(RecData & 0X01)
    {
      //-keys = HAL_KEY_SW_5;
      //-if(halShift == HAL_KEY_STATE_NORMAL)
      {
        if(LoadState & 0x10)
        {  
          LoadState &= ~(0x01<<4); 
        }
        else
        {
          LoadState |= (0x01<<4);
        }
      }
    }
    //-if (keys && (pHalKeyProcessFunction))
    //-{
    //-  (pHalKeyProcessFunction) (keys, halShift);
    //-} 
  }
  return keys;
}
/**********************************************************************
函    数:
功    能：
说    明：
参    数：
返 回 值：
***********************************************************************/
void I2C_SendState(uint8 data)
{
  uint8 i;  
  uint8 SendData =0X00;  
  /*将当前状态赋值*/ 
  SendData = data;   
  /*状态切换*/
  I2C_SCK_L;
  Delay_us(10); 
  
  I2C_SDA_OUT; 
  I2C_SDA_L;  
  
  I2C_SCK_H;                         
  Delay_us(10);  

  /*LoadState:  1 l1 l2 L3 0 K1  K2  K3*/
  /*向触摸写状态数据,高位->低位*/
  for(i=0;i<4;i++)                     
  {
    if(SendData & 0x80)
      I2C_SDA_H;                          
    else
      I2C_SDA_L; 
    I2C_SCK_L;
    Delay_us(5);   
    SendData <<= 1;
    
    if(SendData & 0x80)
      I2C_SDA_H;                          
    else
      I2C_SDA_L; 
    I2C_SCK_H;                         
    Delay_us(5);
    SendData <<= 1;                           
  }   
}
/**********************************************************************
函    数:
功    能：
说    明：
参    数：
返 回 值：
***********************************************************************/
/*void Delay_us(uint32 number)
{
  while(number--)
  {
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop");
  }
}
*/