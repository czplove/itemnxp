/**
  ******************************************************************************
  * @file    E93196.h
  * @author  yuzz@http://www.wulian.cc/
  * @version V1.0.0
  * @date    05-11-2014
  * @brief   This file contains all the functions prototypes for the interface of
  *          E931.96  register accessing.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __E93196_H
#define __E93196_H

/* Includes ------------------------------------------------------------------*/
//#include "hal_mcu.h"
/* Exported typedef ----------------------------------------------------------*/
typedef struct {
    uint8 Sensitivity;
    uint8 BlindTime:4;
    uint8 PulseCounter:2;
    uint8 WindowTime:2;
    uint8 MotionDetect:1;
    uint8 InterruptSource:1;
    uint8 ADCVoltageSource:2;
    uint8 SupplyRegulator:1;
    uint8 StartSelfTest:1;
    uint8 SampleCapacitor:1;
    uint8 UserTestModes:2;
 }E93196Cfg_t;


typedef struct{
  uint8 Sensitivity;
  uint8 BlindTime;
  uint8 PulseCounter;
  uint8 WindowTime;
}E93196Cmd_t;
/**
  * @brief Supply Regulator Enable  and  Start Self-Test
  */
typedef enum{
  Enable                = 0 ,
  Disable               = 1
}SupplyRegulator_t ,StartSelfTest_t;
/**
  * @brief Motion Detect Enable
  */
typedef enum{
  MotionEnable          = 1 ,
  MotionDisable         = 0
} MotionDetect_t;

/**
  * @brief Interrupt Source
  */
typedef enum{
  InterruptSource_Motion      = 0,                   /*!<选择中断源为运动检测  */
  InterruptSource_Filter      = 1                    /*!<选择中断源为滤波器  */
} InterruptSource_t;

/**
  * @brief  ADC Input Source
  */
typedef enum{
  ADCInputSource_BPF        = 0,                         /*!< BPF模式         */
  ADCInputSource_LPF        = 1,                         /*!< LPF模式         */
  ADCInputSource_SUPPLY     = 2,                         /*!< SUPPLY模式      */
  ADCInputSource_TEMP       = 3                          /*!< TEMP模式        */
} ADCInputSource_t;
/**
  * @brief E93196 Configure Command
  */
typedef enum{
  Set_Empty                     = 0x00,
  Set_Sensitivity               = 0x01,                 /*!< 设置灵敏度      */
  Set_BlindTime                 = 0x02,                 /*!< 设置盲区时间    */
  Set_PulseCounter              = 0x03,                 /*!< 设置脉冲个数    */
  Set_WindowTime                = 0x04,                 /*!< 设置窗口时间    */
  Set_MotionDetect              = 0x05,                 /*!< 运动检测使能    */
  Set_InterruptSource           = 0x06,                 /*!< 中断源选择      */
  Set_ADCVoltageSource          = 0x07,                 /*!< ADC输入源选择   */
  Set_SupplyRegulator           = 0x08,                 /*!< 设置供电电压    */
  Set_StartSelfTest             = 0x09,                 /*!< 设置自测模式    */
  Set_SampleCapacitor           = 0x0A,                 /*!< 设置采样电容    */
  Set_UserTestModes             = 0x0B
}ConfigureE93196Cmd_t;
/* Exported constants --------------------------------------------------------*/
#define PIR_SERIN_PIN (1<<11)
#define PIR_DOCI_PIN (1<<17)



/**
  * @brief Sensitivity Configure
  */
#define SensitivityThreshold_104uV              0x10
#define SensitivityThreshold_208uV              0x20
#define SensitivityThreshold_416uV              0x30
#define SensitivityThreshold_832uV              0x40
#define SensitivityThreshold_1664uV             0x50
#define SensitivityThreshold_3328uV             0x60
#define SensitivityThreshold_6656uV             0x70
#define SensitivityThreshold_13312uV            0x80
#define SensitivityThreshold_26624uV            0x90
#define SensitivityThreshold_53248uV            0xA0
#define SensitivityThreshold_106496uV           0xB0
#define SensitivityThreshold_212992uV           0xC0
#define SensitivityThreshold_425984uV           0xD0
#define SensitivityThreshold_851968uV           0xE0
#define SensitivityThreshold_1703936uV          0xF0
/**
  * @brief Blind Time Configure
  */
#define BlindTime_0_5S                          0x00
#define BlindTime_1S                            0x01
#define BlindTime_1_5S                          0x02
#define BlindTime_2S                            0x03
#define BlindTime_2_5S                          0x04
#define BlindTime_3S                            0x05
#define BlindTime_3_5S                          0x06
#define BlindTime_4S                            0x07
#define BlindTime_4_5S                          0x08
#define BlindTime_5S                            0x09
#define BlindTime_5_5S                          0x0A
#define BlindTime_6S                            0x0B
#define BlindTime_6_5S                          0x0C
#define BlindTime_7S                            0x0D
#define BlindTime_7_5S                          0x0E
#define BlindTime_8S                            0x0F
/**
  * @brief Pulse Counter Configure
  */
#define PulseCounter_1                          0x00
#define PulseCounter_2                          0x01
#define PulseCounter_3                          0x02
#define PulseCounter_4                          0x03
/**
  * @brief Window Time Configure
  */
#define WindowTime_4S                           0x00
#define WindowTime_8S                           0x01
#define WindowTime_12S                          0x02
#define WindowTime_16S                          0x03


/* ------------------E93196 Input/Output INT/DOCI----------*/
//#define DOCI_PORT_0

//#define DOCI_INT_RISING_EDGE            0
//#define DOCI_INT_FALLING_EDGE           1

/* CPU port interrupt */
//#define DOCI_INT_CPU_PORT_0_IF          P0IF
//#define DOCI_INT_CPU_PORT_1_IF          P1IF
//#define DOCI_INT_CPU_PORT_2_IF          P2IF

//#if defined(DOCI_PORT_0)
//#define DOCI_INT_CPU_PORT_IF            DOCI_INT_CPU_PORT_0_IF
//#else
//#define DOCI_INT_CPU_PORT_IF            DOCI_INT_CPU_PORT_1_IF
//#endif

/* DOCI_DATA is at P0.4 */
//-#define DOCI_DATA_PIN_PORT                   P0
//-#define DOCI_DATA_PIN_BIT                    BV(4)
//-#define DOCI_DATA_PIN_SEL                    P0SEL
//-#define DOCI_DATA_PIN_DIR                    P0DIR
//-#define DOCI_DATA_PIN_INP                    P0INP

/* DOCI_INT is at P0.4 */
//#define DOCI_PIN_PORT                   P0
//#define DOCI_PIN_BIT                    BV(4)
//#define DOCI_PIN_SEL                    P0SEL
//#define DOCI_PIN_DIR                    P0DIR
//#define DOCI_PIN_INP                    P0INP
//#define DOCI_PIN_PULL                   P2INP
//#define DOCI_PIN_PULLBIT                BV(5)
/* edge interrupt */
//#define DOCI_PIN_EDGEBIT                BV(0)
//#define DOCI_PIN_EDGE                   DOCI_INT_RISING_EDGE

/* DOCI interrupts */
//#define DOCI_PORT_IEN                   IEN1  /* CPU interrupt mask register */
//#define DOCI_PORT_IENBIT                BV(5) /* Mask bit for all of Port_1 */
//#define DOCI_PIN_ICTL                   P0IEN /* Port Interrupt Control register */
//#define DOCI_PIN_ICTLBIT                BV(4) /* P0IEN - P0.4 enable/disable bit */
//#define DOCI_PIN_PXIFG                  P0IFG /* Interrupt flag at source */

/* ------------------E93196 Input SERIN---------------------*/
/* SERIN is at P1.1 */
//#define SERIN_PIN_PORT                  P1
//#define SERIN_PIN_BIT                   BV(1)
//#define SERIN_PIN_SEL                   P1SEL
//#define SERIN_PIN_DIR                   P1DIR
/* Exported Macros -----------------------------------------------------------*/

/* ------------------E93196 Input/Output INT/DOCI----------*/
//#define DOCI_DATA_IN()                  {DOCI_DATA_PIN_DIR &=~DOCI_DATA_PIN_BIT;} /*!< DOCI_Data初始化为输入 */
//#define DOCI_DATA_OUT()                 {DOCI_DATA_PIN_DIR |= DOCI_DATA_PIN_BIT;} /*!<DOCI_Data初始化为输出 */
//-#define DOCI_DATA_IN()                  {vAHI_DioSetDirection(PIR_DOCI_PIN,0);} /*!< DOCI_Data初始化为输入 */
//-#define DOCI_DATA_OUT()                 {vAHI_DioSetDirection(0,PIR_DOCI_PIN);} /*!<DOCI_Data初始化为输出 */

//#define DOCI_DATA_3STATE()              {DOCI_PIN_INP |= DOCI_DATA_PIN_BIT;}    /*!< DOCI_Data 3-state输入*/

//#define DOCI_INIT_IN()                  {DOCI_PIN_DIR &=~DOCI_PIN_BIT;}         /*!< DOCI初始化为输入 */
//#define DOCI_INIT_OUT()                 {DOCI_PIN_DIR |= DOCI_PIN_BIT;}         /*!< DOCI初始化为输出 */
#define DOCI_INIT_IN()                  {vAHI_DioSetDirection(PIR_DOCI_PIN,0);}         /*!< DOCI初始化为输入 */
#define DOCI_INIT_OUT()                 {vAHI_DioSetDirection(0,PIR_DOCI_PIN);}         /*!< DOCI初始化为输出 */
//#define DOCI_ON()                       {DOCI_PIN_PORT |= DOCI_PIN_BIT;}        /*!< DOCI输出高电平 */
//#define DOCI_OFF()                      {DOCI_PIN_PORT &=~DOCI_PIN_BIT;}        /*!< DOCI输出低电平 */
#define DOCI_ON()                       {vAHI_DioSetOutput(PIR_DOCI_PIN,0);}        /*!< DOCI输出高电平 */
#define DOCI_OFF()                      {vAHI_DioSetOutput(0,PIR_DOCI_PIN);}        /*!< DOCI输出低电平 */

//#define DOCI_PULLUP()                   \
//{                                                                              \
//                                        DOCI_PIN_INP &=~DOCI_PIN_BIT;           /*!< DOCI上拉输入 */\
//                                        DOCI_PIN_PULL &=~DOCI_PIN_PULLBIT;     \
//}
//#define DOCI_PULLDOWN()                 \
//{                                                                              \
//                                        DOCI_PIN_INP &=~DOCI_PIN_BIT;           /*!< DOCI下拉输入*/\
//                                        DOCI_PIN_PULL |= DOCI_PIN_PULLBIT;     \
//                                        }
//#define DOCI_3STATE()                   {DOCI_PIN_INP |= DOCI_PIN_BIT;}         /*!< DOCI 3-state输入*/

//#define DOCI_ENABLE_INTERRUPT()         {DOCI_PIN_ICTL |= DOCI_PIN_ICTLBIT;}    /*!< 使能DOCI引脚中断*/
//#define DOCI_DISABLE_INTERRUPT()        {DOCI_PIN_ICTL &=~DOCI_PIN_ICTLBIT;}    /*!< 禁止DOCI引脚中断*/
//#define PORT1_ENABLE_INTERRUPTS()       {DOCI_PORT_IEN |= DOCI_PORT_IENBIT;}      /*!< 使能端口1.0~1.7中断*/
//#define PORT1_DISABLE_INTERRUPTS()      {DOCI_PORT_IEN &=~DOCI_PORT_IENBIT;}      /*!< 禁止端口1.0~1.7中断*/

/* ------------------E93196 Input SERIN----------------------*/
//#define SERIN_INIT_IN()                 {SERIN_PIN_DIR &=~SERIN_PIN_BIT;}       /*!< SERIN初始化为输入 */
//#define SERIN_INIT_OUT()                {SERIN_PIN_DIR |= SERIN_PIN_BIT;}       /*!< SERIN初始化为输出 */
//#define SERIN_ON()                      {SERIN_PIN_PORT |= SERIN_PIN_BIT;}      /*!< SERIN输出高电平 */
//#define SERIN_OFF()                     {SERIN_PIN_PORT &=~SERIN_PIN_BIT;}      /*!< SERIN输出低电平 */
#define SERIN_INIT_IN()                 {vAHI_DioSetDirection(PIR_SERIN_PIN,0);}       /*!< SERIN初始化为输入 */
#define SERIN_INIT_OUT()                {vAHI_DioSetDirection(0, PIR_SERIN_PIN);}       /*!< SERIN初始化为输出 */
#define SERIN_ON()                      {vAHI_DioSetOutput(PIR_SERIN_PIN,0);}      /*!< SERIN输出高电平 */
#define SERIN_OFF()                     {vAHI_DioSetOutput(0,PIR_SERIN_PIN);}      /*!< SERIN输出低电平 */


#define WAIT_FOR_4_5US                  1
#define WAIT_FOR_100US                  40
#define WAIT_FOR_150US                  60
#define WAIT_FOR_600US                  240
/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void ConfigE93196Cfg(E93196Cmd_t *pCmd);

void PIR_ChgDefenceCfg(E93196Cmd_t *pCmd);

void InitE93196Interrupt(void);

void SetE93196Config(void);
/*  Configure the IO of  CC2530 for E93196  *****/
void InitE93196_IO(void);

void ClearE93196Interrupt(void);

void ProcessDOCIInterrupt(void);
/*  Read the pin level *****/
uint8 ReadIntputBit(uint8 PORT, uint8 PIN);
/*  Read num  bytes data from registers of E93196 Controller Integrated Circuit *****/
void ReadE93196(uint8 *ptr,uint8 num);
/*  write 25 bytes data into registers of E93196 Controller Integrated Circuit *****/
void WriteE93196(uint8*ptr);

void WriteE93196Cfg(E93196Cfg_t* pCfg);

void PIR_ClearDefence(void);

void PIR_SetDefence(void);
#endif /*__E93196_H */

/************** (C) Copyright 2014 南京物联传感技术有限公司*****END OF FILE****/
