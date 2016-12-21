/*****************************************************************************
 *
 * MODULE:             JN-AN-1201
 *
 * COMPONENT:          Temperature Management Implementation
 *
 * DESCRIPTION:        Set of functions/task for temperature related behaviour
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "os.h"
#include "os_gen.h"
#include "AppHardwareApi.h"
#include "app_timer_driver.h"
#include "app_manage_lv.h"
//-#include "DriverBulb.h"
#include "DBG.h"
//-#include "recal.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/



#ifdef DEBUG_LV
#define TRACE_APP_LV               TRUE
#else
#define TRACE_APP_LV                FALSE
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/



/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/



/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void APP_vManagelvInit(void)
{

    /* Set up the analogue peripherals ready to handle the conversions */
    vAHI_ApConfigure(E_AHI_AP_REGULATOR_ENABLE,
                     E_AHI_AP_INT_DISABLE,
                     E_AHI_AP_SAMPLE_8,
                     E_AHI_AP_CLOCKDIV_500KHZ,
                     E_AHI_AP_INTREF);

    while (!bAHI_APRegulatorEnabled());   /* spin on reg not enabled */
    DBG_vPrintf(TRACE_APP_LV, "\nAPP: InitManageLV");
}

PUBLIC void APP_vManageLVGetVoltage(void)
{
		uint16 VddVoltage;
	
		vAHI_AdcEnable(E_AHI_ADC_SINGLE_SHOT, E_AHI_AP_INPUT_RANGE_2, E_AHI_ADC_SRC_VOLT);
    vAHI_AdcStartSample();
    while(bAHI_AdcPoll())
		vAHI_WatchdogRestart();	//-暂时等待的时候复位看门狗,防止程序重启,后期合理性需要考虑
    VddVoltage = u16AHI_AdcRead();
		DBG_vPrintf(TRACE_APP_LV, "\nAPP GetVoltage: ADC = %d",VddVoltage);
		VddVoltage = (45 * VddVoltage) / 128;	//-采集电压值扩大了100
		DBG_vPrintf(TRACE_APP_LV, "\nAPP GetVoltage: VDD *100 = %dV",VddVoltage);
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
