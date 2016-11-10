/*****************************************************************************
 *
 * MODULE:             Smart Energy Profile
 *
 * COMPONENT:          se.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        ZigBee Smart Energy profile functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/UnifiedZCL_ZLL102_HA122_Maintenance/Profiles/ZLL/Source/zll.c $
 *
 * $Revision: 81838 $
 *
 * $LastChangedBy: nxp46755 $
 *
 * $LastChangedDate: 2016-07-27 07:33:01 +0100 (Wed, 27 Jul 2016) $
 *
 * $Id: zll.c 81838 2016-07-27 06:33:01Z nxp46755 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139]. 
 * You, and any third parties must reproduce the copyright and warranty notice 
 * and any other legend of ownership on each  copy or partial copy of the software.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  
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
 ****************************************************************************/
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "zps_apl.h"
#include "zcl_heap.h"
#include "zcl.h"
#include "zcl_options.h"
#include "zll.h"
#include "Scenes.h"
#include "Identify.h"
#include "LevelControl.h"
#include "ColourControl.h"
#include "OnOff.h"

extern PUBLIC void vIdEffectTick(uint8 u8Endpoint);
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
#define ZLL_NUMBER_OF_IDENTIFY_TIMERS                    (1)
#else
#define ZLL_NUMBER_OF_IDENTIFY_TIMERS                    (0)
#endif
#if (defined CLD_SCENES) && (defined SCENES_SERVER)
#define ZLL_NUMBER_OF_SCENES_TIMERS                      (1)
#else
#define ZLL_NUMBER_OF_SCENES_TIMERS                      (0)
#endif
#define ZLL_NUMBER_OF_TIMERS     (ZLL_NUMBER_OF_ZCL_APPLICATION_TIMERS + ZLL_NUMBER_OF_IDENTIFY_TIMERS + ZLL_NUMBER_OF_SCENES_TIMERS)
#define ZLL_NUMBER_OF_STRING_REPORTS     (0)
#ifdef ZCL_ATTRIBUTE_REPORTING_SERVER_SUPPORTED
#define ZLL_NUMBER_OF_REPORTS            (10)
#define ZLL_SYSTEM_MIN_REPORT_INTERVAL   (0)
#define ZLL_SYSTEM_MAX_REPORT_INTERVAL   (0)
#else
#define ZLL_NUMBER_OF_REPORTS            (0)
#define ZLL_SYSTEM_MIN_REPORT_INTERVAL   (0)
#define ZLL_SYSTEM_MAX_REPORT_INTERVAL   (0)
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
#ifdef ZLL_PRIMARY
    const uint8 au8ZLLChannelSet[] = {11,11,11,11,11,15,20,25};
    //const uint8 au8ZLLChannelSet[] = {15,15,15,15,15,15,15,15};
#else
    #ifdef ZLL_PRIMARY_PLUS1
        const uint8 au8ZLLChannelSet[] = {12,12,12,12,12,16,21,26};
    #else
        #ifdef ZLL_PRIMARY_PLUS2
            const uint8 au8ZLLChannelSet[] = {13,13,13,13,13,17,22,19};
        #else
            #ifdef ZLL_PRIMARY_PLUS3
                const uint8 au8ZLLChannelSet[] = {14,14,14,14,14,18,23,24};
            #endif
        #endif
    #endif
#endif

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

PRIVATE uint32
        u32ZCL_Heap[ZCL_HEAP_SIZE(ZLL_NUMBER_OF_ENDPOINTS, ZLL_NUMBER_OF_TIMERS, ZLL_NUMBER_OF_REPORTS, ZLL_NUMBER_OF_STRING_REPORTS)];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
#include "dbg.h"
/****************************************************************************
 *
 * NAME: eZLL_Initialise
 *
 * DESCRIPTION:
 * Registers timer servers with the ZCL layer
 *
 * PARAMETERS:  Name                            Usage
 *              cbCallBack                      Pointer to general callback
 *              hAPdu                           pointer to pool of APDU's
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eZLL_Initialise(tfpZCL_ZCLCallBackFunction cbCallBack,
        PDUM_thAPdu hAPdu) {
    teZCL_Status eStatus;
    tsZCL_Config sConfig;

    sConfig.u8NumberOfEndpoints = ZLL_NUMBER_OF_ENDPOINTS;
    sConfig.u8NumberOfTimers = ZLL_NUMBER_OF_TIMERS;
    sConfig.u8NumberOfReports = ZLL_NUMBER_OF_REPORTS;
    sConfig.u16SystemMinimumReportingInterval = ZLL_SYSTEM_MIN_REPORT_INTERVAL;
    sConfig.u16SystemMaximumReportingInterval = ZLL_SYSTEM_MAX_REPORT_INTERVAL;
    sConfig.pfZCLcallBackFunction = cbCallBack;
    sConfig.hAPdu = hAPdu;
    sConfig.u32ZCL_HeapSizeInWords = sizeof(u32ZCL_Heap) / sizeof(uint32);
    sConfig.pu32ZCL_Heap = &u32ZCL_Heap[0];

    //DBG_vPrintf(TRUE, "No timers %d %d %d\n", ZLL_NUMBER_OF_ZCL_APPLICATION_TIMERS, ZLL_NUMBER_OF_IDENTIFY_TIMERS, ZLL_NUMBER_OF_SCENES_TIMERS);

    eStatus = eZCL_CreateZCL(&sConfig);
    if (eStatus != E_ZCL_SUCCESS) {
        return eStatus;
    }

    return eStatus;
}

/****************************************************************************
 *
 * NAME: eZLL_Update100mS
 *
 * DESCRIPTION:
 * Should be called by an application timer 10 times per second
 *
 * PARAMETERS:  Name                            Usage
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eZLL_Update100mS(void)
{

    /* Update clusters on each end point if any */
    #if ((defined LEVEL_CONTROL_SERVER) || (defined SCENES_SERVER) || \
         (defined COLOUR_CONTROL_SERVER)|| (defined ONOFF_SERVER) || \
         (defined IDENTIFY_SERVER) )
        {
            uint8 u8NumEndpoints;
            u8NumEndpoints = u8ZCL_GetNumberOfEndpointsRegistered();

            int i;
            for (i = 1; i < (u8NumEndpoints + 1); i++)
            {
                #if (defined LEVEL_CONTROL_SERVER)
                    eCLD_LevelControlUpdate(i);
                #endif

                #if (defined SCENES_SERVER)
                    eCLD_ScenesUpdate(i);
                #endif

                #if (defined COLOUR_CONTROL_SERVER)
                    eCLD_ColourControlUpdate(i);
                #endif

                #if (defined ONOFF_SERVER)
                    eCLD_OnOffUpdate(i);
                #endif

                #if (defined IDENTIFY_SERVER)
                    vIdEffectTick(i);
                #endif
            }
        }
    #endif
    return E_ZCL_SUCCESS;
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

