/*****************************************************************************
 *
 * MODULE:             Electrical Measurement Cluster
 *
 * COMPONENT:          ElectricalMeasurement.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Electrical Measurement cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/UnifiedZCL_ZLL102_HA122_Maintenance/Clusters/General/Source/ElectricalMeasurement.c $
 *
 * $Revision: 66142 $
 *
 * $LastChangedBy: nxp58432 $
 *
 * $LastChangedDate: 2014-11-28 09:07:10 +0000 (Fri, 28 Nov 2014) $
 *
 * $Id: ElectricalMeasurement.c 66142 2014-11-28 09:07:10Z nxp58432 $
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
#include "zcl.h"
#include "ElectricalMeasurement.h"


#ifdef CLD_ELECTRICAL_MEASUREMENT
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

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
#ifdef ELECTRICAL_MEASUREMENT_SERVER
    const tsZCL_AttributeDefinition asCLD_ElectricalMeasurementClusterAttributeDefinitions[] = {

        {E_CLD_ELECTMEAS_ATTR_ID_MEASUREMENT_TYPE,         E_ZCL_AF_RD,        E_ZCL_BMAP32,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u32MeasurementType),      0},   /* Mandatory */

    #ifdef CLD_ELECTMEAS_ATTR_AC_FREQUENCY
        {E_CLD_ELECTMEAS_ATTR_ID_AC_FREQUENCY,             E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACFrequency),          0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_RMS_VOLTAGE
        {E_CLD_ELECTMEAS_ATTR_ID_RMS_VOLATAGE,             E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16RMSVoltage),           0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_RMS_CURRENT
        {E_CLD_ELECTMEAS_ATTR_ID_RMS_CURRENT,              E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16RMSCurrent),           0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_ACTIVE_POWER
        {E_CLD_ELECTMEAS_ATTR_ID_ACTIVE_POWER,             E_ZCL_AF_RD,        E_ZCL_INT16,     (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->i16ActivePower),          0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_REACTIVE_POWER
        {E_CLD_ELECTMEAS_ATTR_ID_REACTIVE_POWER,           E_ZCL_AF_RD,        E_ZCL_INT16,     (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->i16ReactivePower),        0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_APPARENT_POWER
        {E_CLD_ELECTMEAS_ATTR_ID_APPARENT_POWER,           E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ApparentPower),        0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_POWER_FACTOR
        {E_CLD_ELECTMEAS_ATTR_ID_POWER_FACTOR,             E_ZCL_AF_RD,        E_ZCL_INT8,      (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->i8PowerFactor),           0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_MULTIPLIER
        {E_CLD_ELECTMEAS_ATTR_ID_AC_VOLTAGE_MULTIPLIER,    E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACVoltageMultiplier),  0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_DIVISOR
        {E_CLD_ELECTMEAS_ATTR_ID_AC_VOLTAGE_DIVISOR,       E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACVoltageDivisor),     0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_MULTIPLIER
        {E_CLD_ELECTMEAS_ATTR_ID_AC_CURRENT_MULTIPLIER,    E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACCurrentMultiplier),  0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_DIVISOR
        {E_CLD_ELECTMEAS_ATTR_ID_AC_CURRENT_DIVISOR,       E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACCurentDivisor),      0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_POWER_MULTIPLIER
        {E_CLD_ELECTMEAS_ATTR_ID_AC_POWER_MULTIPLIER,      E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACPowerMultiplier),    0},   /* Optional */
    #endif

    #ifdef CLD_ELECTMEAS_ATTR_AC_POWER_DIVISOR
        {E_CLD_ELECTMEAS_ATTR_ID_AC_POWER_DIVISOR,         E_ZCL_AF_RD,        E_ZCL_UINT16,    (uint32)(&((tsCLD_ElectricalMeasurement*)(0))->u16ACPowerDivisor),       0},   /* Optional */
    #endif

    };


    tsZCL_ClusterDefinition sCLD_ElectricalMeasurement = {
            MEASUREMENT_AND_SENSING_CLUSTER_ID_ELECTRICAL_MEASUREMENT,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_ElectricalMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_ElectricalMeasurementClusterAttributeDefinitions,
            NULL
    };

    uint8 au8ElectricalMeasurementServerAttributeControlBits[(sizeof(asCLD_ElectricalMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
#else
    tsZCL_ClusterDefinition sCLD_ElectricalMeasurement = {
            MEASUREMENT_AND_SENSING_CLUSTER_ID_ELECTRICAL_MEASUREMENT,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            0,
            NULL,
            NULL
    };
#endif
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_ElectricalMeasurementCreateElectricalMeasurement
 **
 ** DESCRIPTION:
 ** Creates a temperature measurement cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ElectricalMeasurementCreateElectricalMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Create an instance of a temperature measurement cluster */
    vZCL_InitializeClusterInstance(
                   psClusterInstance, 
                   bIsServer,
                   psClusterDefinition,
                   pvEndPointSharedStructPtr,
                   pu8AttributeControlBits,
                   NULL,
                   NULL);

    #ifdef ELECTRICAL_MEASUREMENT_SERVER
        if(pvEndPointSharedStructPtr != NULL)
        {
            /* Initializing these values to invalid as ZCL spec does not mention the defualt */ 
            #ifdef CLD_ELECTMEAS_ATTR_AC_FREQUENCY
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACFrequency = 0xFFFF;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_RMS_VOLTAGE
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16RMSVoltage = 0xFFFF;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_RMS_CURRENT
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16RMSCurrent = 0xFFFF;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_ACTIVE_POWER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->i16ActivePower = 0xFFFF;
            #endif

            #ifdef CLD_ELECTMEAS_ATTR_REACTIVE_POWER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->i16ReactivePower = 0xFFFF;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_APPARENT_POWER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ApparentPower = 0xFFFF;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_MULTIPLIER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACVoltageMultiplier = 0x0001;
            #endif
            
            #ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_DIVISOR
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACVoltageDivisor = 0x0001;
            #endif
    
            #ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_MULTIPLIER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACCurrentMultiplier = 0x0001;
            #endif
    
            #ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_DIVISOR
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACCurentDivisor = 0x0001;
            #endif
    
            #ifdef CLD_ELECTMEAS_ATTR_AC_POWER_MULTIPLIER
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACPowerMultiplier = 0x0001;
            #endif
    
            #ifdef CLD_ELECTMEAS_ATTR_AC_POWER_DIVISOR
                ((tsCLD_ElectricalMeasurement*)pvEndPointSharedStructPtr)->u16ACPowerDivisor = 0x0001;
            #endif
        }
    #endif
    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif/* CLD_ELECTRICAL_MEASUREMENT */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

