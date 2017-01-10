/*****************************************************************************
 *
 * MODULE:             JN-AN-1189
 *
 * COMPONENT:          app_occupancy_buttons.c
 *
 * DESCRIPTION:        DK4 (DR1175/DR1199) Button Press detection (Implementation)
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2013. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "os.h"
#include "os_gen.h"
#include "DBG.h"
#include "AppHardwareApi.h"
#include "app_events.h"
#include "app_timer_driver.h"
#include "pwrm.h"
#include "app_occupancy_buttons.h"
#include "app_sensor_state_machine.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define STCP   		(1<<15)			//-´æ´¢Æ÷Ëø´æÊ±ÖÓÏß
#define SHCP_CLK   	(1<<0)				//-Êý¾ÝÊäÈëÊ±ÖÓÏß
#define DS_DIO   	(1<<18)			//-´®ÐÐÊý¾ÝÊäÈë

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
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
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
void HC595IO_Init(void)
{
	/* Set DIO lines to outputs with buttons connected */
	    vAHI_DioSetDirection(0, STCP | SHCP_CLK | DS_DIO);
	    bAHI_DoEnableOutputs(1);
	/* Turn on pull-ups for DIO lines with buttons connected */
	    vAHI_DioSetPullup(STCP | SHCP_CLK | DS_DIO, 0);
	    //-vAHI_DoSetPullup();
	    HC595SendData(0x2A);	//-出口继电器输出为0
	    Delay(100*1000);
	    HC595SendData(0);	//-DIO3输出低
}


void HC595SendData(unsigned char SendVal)
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
		if((SendVal<<i)&0x80)
			vAHI_DioSetOutput(DS_DIO,0);
		else 
			vAHI_DioSetOutput(0,DS_DIO);
		//-vAHI_DioSetOutput(0,SHCP_CLK);
		//-vAHI_DioSetOutput(SHCP_CLK,0);
		vAHI_DoSetDataOut(0,SHCP_CLK);
		j = 2;
		while(j)
		j--;
		//-vAHI_DioSetOutput(SHCP_CLK,0);
		//-vAHI_DioSetOutput(0,SHCP_CLK);
		vAHI_DoSetDataOut(SHCP_CLK,0);
	}
	vAHI_DioSetOutput(0,STCP);
	j = 2;
			while(j)
			j--;
	vAHI_DioSetOutput(STCP,0);
}

void HC595SendData0(unsigned char SendVal)
{
	vAHI_DioSetOutput(0,STCP);
	vAHI_DioSetOutput(0,DS_DIO);
	vAHI_DioSetOutput(0,SHCP_CLK);
	vAHI_DoSetDataOut(0,SHCP_CLK);
}

void HC595SendData1(unsigned char SendVal)
{
	vAHI_DioSetOutput(STCP,0);
	vAHI_DioSetOutput(DS_DIO,0);
	vAHI_DioSetOutput(SHCP_CLK,0);
	vAHI_DoSetDataOut(SHCP_CLK,0);
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
