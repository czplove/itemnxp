/**
  ******************************************************************************
  * @file    E93196.c
  * @author  yuzz@http://www.wulian.cc/
  * @version V1.0.0
  * @date    10-11-2014
  * @brief
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <jendefs.h>
#include "AppHardwareApi_JN516x.h"
#include "E93196.h"
//#include "osal_memory.h"
//#include "hal_board.h"
//#include "hal_led.h"
/** @addtogroup
  * @{
  */

/** @defgroup
  * @brief
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
E93196Cfg_t  E93196Cfg;
E93196Cmd_t  E93196DefaultCmd={0x40,0x0a,0x02,0x40};
/* Private function prototypes -----------------------------------------------*/
static void Delay (uint32 u32DelayUs);
/* Private functions ---------------------------------------------------------*/


void PIR_ChgDefenceCfg(E93196Cmd_t *pCmd)
{
  InitE93196_IO();
  /* 初始化E931.96报警中断，不使能P0.4/INT_DOCI引脚中断*/
  //-InitE93196Interrupt();

  /* 设置工作模式*/
  ConfigE93196Cfg(pCmd);

  //-DOCI_ENABLE_INTERRUPT();
  /*清除不确定中断状态*/
  ClearE93196Interrupt();

}


/**
  * @brief
  * @param  None
  * @retval None
  */
void InitE93196Interrupt(void)
{
//-  PICTL &=~(DOCI_PIN_EDGEBIT);          /* Clear the edge bit */
//-  /* For falling edge, the bit must be set. */
//-#if (DOCI_PIN_EDGE == DOCI_INT_FALLING_EDGE)
//-  PICTL |= DOCI_PIN_EDGEBIT;
//-#endif
//-  /* Interrupt configuration:
//-  * - Enable interrupt generation at the port
//-  * - Enable CPU interrupt
//-  * - Clear any pending interrupt
//-  */
//-  DOCI_PIN_ICTL |= DOCI_PIN_ICTLBIT; /*禁止P0.4中断 */
//-
//-  DOCI_PORT_IEN |= DOCI_PORT_IENBIT;
//-
//-  DOCI_PIN_PXIFG &=~DOCI_PIN_ICTLBIT;

    DOCI_INIT_IN(); 
    vAHI_DioSetPullup(PIR_DOCI_PIN,0);
	vAHI_DioWakeEdge(0,PIR_DOCI_PIN);	//-测试使用下降沿触发
	vAHI_DioWakeEnable(PIR_DOCI_PIN,0);
}

void ClearE93196Interrupt(void)
{
  DOCI_INIT_OUT();
  DOCI_ON();
  Delay(WAIT_FOR_4_5US);
  DOCI_OFF();
  Delay(WAIT_FOR_4_5US);
  //DOCI_3STATE();
  DOCI_INIT_IN();
}
/**
  * @brief
  * @param  None
  * @retval None
  */
void ProcessDOCIInterrupt(void)
{
  /* 清除E931.96中断状态*/
  DOCI_INIT_OUT();
  DOCI_OFF();
  DOCI_INIT_IN();
  //DOCI_3STATE();
}

void SetE93196Config(void)
{
  E93196Cfg.Sensitivity = SensitivityThreshold_208uV;
  E93196Cfg.BlindTime = BlindTime_4S;
  E93196Cfg.PulseCounter = PulseCounter_2;
  E93196Cfg.WindowTime = WindowTime_4S;
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Enable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}

void WriteE93196Cfg(E93196Cfg_t* pCfg)
{

  unsigned char *pdata , *pHeader ;
  char  i, tmp;
  //pHeader = pdata = (unsigned char *)osal_mem_alloc(25);
  unsigned char pdatamen[25];
  pHeader = pdata = pdatamen;

  tmp = pCfg->Sensitivity;
  for (i = 0; i<8 ;++i)
  {
    if( 0x80 == (tmp & 0x80) ){
      *pdata++ = 1;
    }
    else {
      *pdata++ = 0;
    }
    tmp = tmp << 1;                      /* 左移一位 */
  }

  tmp = pCfg->BlindTime;
  for (i = 8; i < 12; ++i)            /*  数据一位一位传入         */
  {
    if(0x08 == (tmp & 0x08)) {        /* 　[11:8]位设置盲区时间     */
      *pdata++  = 1 ;
    }
    else {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;                 /* 左移一位                   */
  }

  tmp = pCfg->PulseCounter;
  for (i = 12;i < 14;i++)
  {                               /* 　[13:12]位设置脉冲个数    */
    if(0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;         /* 左移一位                   */
  }

  tmp = pCfg->WindowTime;
  for (i = 14;i < 16;i++)                   /* 　[15:14]位设置窗口时间    */
  {
    if (0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;               /* 左移一位                   */
  }
  *pdata++ = pCfg->MotionDetect;
  *pdata++ = pCfg->InterruptSource;

  tmp = pCfg->ADCVoltageSource;
  for(i = 18; i < 20; ++i)
  {
    if (0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;               /* 左移一位                   */
  }
  *pdata++ = pCfg->SupplyRegulator;
  *pdata++ = pCfg->StartSelfTest;
  *pdata++ = pCfg->SampleCapacitor;
  *pdata++ = 0;
  *pdata++ = 0;
  WriteE93196(pHeader);
  //osal_mem_free((void*)pHeader);
}

/**
  * @brief
  * @param
  * @retval None
  */
void InitE93196_IO( void )
{
  /* SERIN初始化为输出 */
  SERIN_INIT_OUT();

  /* SERIN初始化为低电平 */
  SERIN_OFF();

  /* DICO初始化为输出*/
  DOCI_INIT_OUT();
}
/**........................
  * @brief
  * @param
  * @retval None
  */
unsigned char ReadIntputBit(unsigned char Port , unsigned char Pin)
{
  unsigned char bit;
  if((Port&Pin) == 0 )
    bit = 0;
  else
    bit = 1;
  return  bit;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ReadE93196(unsigned char * ptr, unsigned char num)
{
  DOCI_INIT_OUT();                                      /*!<  DICO初始化为输出        */
  DOCI_ON();                                            /*!<  强制拉高管脚一段时间    */
  Delay(65);                                           /*!<  高脉冲时间大于等于65us  */
  DOCI_OFF();
  //for(unsigned char  n = 0; n < num; ++n)
  {
    Delay(1);
    DOCI_ON();                                          /*!<  产生上升沿      */
    //-DOCI_PULLUP();
    DOCI_INIT_IN();                                     /*!<  等待芯片改变总线电平 */
    Delay(1);
    //-*(ptr+n) = ReadIntputBit(DOCI_PIN_PORT,DOCI_PIN_BIT)+'0';    /*!<  读取一位数据    */
    Delay(1);
    DOCI_INIT_OUT();
    DOCI_OFF();                                         /*!<  将DOCI拉为低电平*/
  }
  Delay(125);                                        /*!<  高脉冲时间大于等于125us  */
  DOCI_INIT_IN();                                       /*!<  DICO初始化为输入*/
}
/**
  * @brief
  * @param
  * @retval None
  */
void WriteE93196( uint8* ptr )
{
	uint8 i;
  for (i = 0; i < 25; ++i)   /*!<  循环写入25位数据 */
  {
    SERIN_OFF();
    Delay(WAIT_FOR_4_5US);
    SERIN_ON();
    Delay(WAIT_FOR_4_5US);
    if(*ptr++)
    {
      SERIN_ON();
    }else{
      SERIN_OFF();
    }
    Delay(WAIT_FOR_100US);
  }
  SERIN_OFF();
  Delay(WAIT_FOR_600US);
}


/**
  * @brief
  * @param
  * @retval None
  */
static void Delay (uint32 u32DelayUs)
{
/*
  while (usec--){
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");
  }
  */
  uint32 start_tick,curr_tick, tick_delta, target_delta;
  
  target_delta = u32DelayUs * 16;
  start_tick = u32AHI_TickTimerRead();
  do
  {
    vAHI_WatchdogRestart();
    curr_tick = u32AHI_TickTimerRead();
    if (curr_tick > start_tick)
      tick_delta = curr_tick - start_tick;
    else
      tick_delta =  4294967296 - start_tick + curr_tick;
  } while (tick_delta < target_delta);
}
void ConfigE93196Cfg(E93196Cmd_t *pCmd)
{
  E93196Cfg.Sensitivity = pCmd->Sensitivity;
  E93196Cfg.BlindTime = ((pCmd->BlindTime)/5-1);
  E93196Cfg.PulseCounter = (pCmd->PulseCounter - 1);
  E93196Cfg.WindowTime = (pCmd->WindowTime/4 -1);
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Enable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}
void PIR_ClearDefence(void)
{
  /* 禁止 PIR中断*/
  DOCI_DISABLE_INTERRUPT();
  /* 关闭PIR电源*/
  E93196Cfg.Sensitivity = E93196DefaultCmd.Sensitivity;
  E93196Cfg.BlindTime = ((E93196DefaultCmd.BlindTime)/5-1);
  E93196Cfg.PulseCounter = (E93196DefaultCmd.PulseCounter - 1);
  E93196Cfg.WindowTime = (E93196DefaultCmd.WindowTime/4 -1);
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Disable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}

void PIR_SetDefence(void)
{
  //-InitE93196_IO();
  /* 初始化E931.96报警中断，不使能P0.4/INT_DOCI引脚中断*/
  InitE93196Interrupt();

  /* 设置工作模式*/
  //-ConfigE93196Cfg(&E93196DefaultCmd);

  //DOCI_ENABLE_INTERRUPT();
  vAHI_DioInterruptEnable(PIR_DOCI_PIN,0);
  /*清除不确定中断状态*/
  //-ClearE93196Interrupt();
}
/**
  * @}
  */

/**
  * @}
  */

/************** (C) Copyright 2014 南京物联传感技术有限公司*****END OF FILE****/