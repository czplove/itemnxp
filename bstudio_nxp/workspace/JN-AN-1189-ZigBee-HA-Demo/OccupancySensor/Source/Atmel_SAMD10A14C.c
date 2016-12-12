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
��    ��:
��    �ܣ�
˵    ����
��    ����
�� �� ֵ��
***********************************************************************/
void I2C_Init(void)                   //IO��ʼ��
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
��    ��:
��    �ܣ�
˵    ����
��    ����
�� �� ֵ��
***********************************************************************/
uint8 I2C_ReadState(void)
{
  uint8 RecData = 0X00;  
  uint8 i,temp_data;
  /*��ȡ��ǰ״̬*/
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
��    ��:
��    �ܣ�
˵    ����
��    ����
�� �� ֵ��
***********************************************************************/
uint8 I2C_CheckState(uint8 data)
{
  uint8 keys = 0;
  uint8 RecData = 0X00; 
  RecData = data;
  /*��ȡ���ݸ�ʽ0xYY*/
  /*��ȡ���� Temp ���λΪ1,���ʾ���ݶ�ȡ��ȷ*/
  if(RecData & 0X80 )
  { 
    /*LoadState:  1 l1 l2 L3 S K1  K2  K3(S:��ʾled��ʾ״̬)*/
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
��    ��:
��    �ܣ�
˵    ����
��    ����
�� �� ֵ��
***********************************************************************/
void I2C_SendState(uint8 data)
{
  uint8 i;  
  uint8 SendData =0X00;  
  /*����ǰ״̬��ֵ*/ 
  SendData = data;   
  /*״̬�л�*/
  I2C_SCK_L;
  Delay_us(10); 
  
  I2C_SDA_OUT; 
  I2C_SDA_L;  
  
  I2C_SCK_H;                         
  Delay_us(10);  

  /*LoadState:  1 l1 l2 L3 0 K1  K2  K3*/
  /*����д״̬����,��λ->��λ*/
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
��    ��:
��    �ܣ�
˵    ����
��    ����
�� �� ֵ��
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