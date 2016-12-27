/****************************************************************************
 *
 * MODULE:             ZigbeeNodeControlBridge
 *
 * COMPONENT:          Serial Link to Host
 *
 * VERSION:
 *
 * REVISION:           $Revision: 54831 $
 *
 * DATED:              $Date: 2013-06-21 16:35:20 +0100 (Fri, 21 Jun 2013) $
 *
 * STATUS:             $State: Exp $
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:
 *
 * LAST MODIFIED BY:   $Author: nxp29741 $
 *                     $Modtime: $
 *
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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

#ifndef  SERIALLINK_H_INCLUDED
#define  SERIALLINK_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <AppHardwareApi.h>


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define SL_WRITE(DATA)		bPutChar(DATA)

#define SL_START_CHAR	0x01
#define SL_ESC_CHAR		0x02
#define SL_END_CHAR		0x03

/** Macro to send a log message to the host machine
 *  First byte of the message is the level (0-7).
 *  Remainder of message is char buffer containing ascii message
 */

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/** Serial link message types */
typedef enum
{
/* Common Commands */
    E_SL_MSG_STATUS                         =   0x8000,
    E_SL_MSG_LOG                            =   0x8001,

    E_SL_MSG_DATA_INDICATION                =   0x8002,

    E_SL_MSG_NODE_CLUSTER_LIST              =   0x8003,
    E_SL_MSG_NODE_ATTRIBUTE_LIST            =   0x8004,
    E_SL_MSG_NODE_COMMAND_ID_LIST           =   0x8005,
    E_SL_MSG_NODE_NON_FACTORY_NEW_RESTART   =   0x8006,
    E_SL_MSG_NODE_FACTORY_NEW_RESTART       =   0x8007,
    E_SL_MSG_GET_VERSION                    =   0x0010,
    E_SL_MSG_VERSION_LIST                   =   0x8010,

    E_SL_MSG_SET_EXT_PANID                  =   0x0020,
    E_SL_MSG_SET_CHANNELMASK                =   0x0021,
    E_SL_MSG_SET_SECURITY                   =   0x0022,
    E_SL_MSG_SET_DEVICETYPE                 =   0x0023,
    E_SL_MSG_START_NETWORK                  =   0x0024,
    E_SL_MSG_START_SCAN                     =   0x0025,
    E_SL_MSG_NETWORK_JOINED_FORMED          =   0x8024,
    E_SL_MSG_NETWORK_REMOVE_DEVICE          =   0x0026,
    E_SL_MSG_NETWORK_WHITELIST_ENABLE       =   0x0027,
    E_SL_MSG_ADD_AUTHENTICATE_DEVICE        =   0x0028,
    E_SL_MSG_AUTHENTICATE_DEVICE_RESPONSE   =   0x8028,

    E_SL_MSG_RESET                          =   0x0011,
    E_SL_MSG_ERASE_PERSISTENT_DATA          =   0x0012,
    E_SL_MSG_ZLL_FACTORY_NEW                =   0x0013,
    E_SL_MSG_GET_PERMIT_JOIN                =   0x0014,
    E_SL_MSG_GET_PERMIT_JOIN_RESPONSE       =   0x8014,
    E_SL_MSG_BIND                           =   0x0030,
    E_SL_MSG_BIND_RESPONSE                  =   0x8030,
    E_SL_MSG_UNBIND                         =   0x0031,
    E_SL_MSG_UNBIND_RESPONSE                =   0x8031,

    E_SL_MSG_NETWORK_ADDRESS_REQUEST        =   0x0040,
    E_SL_MSG_NETWORK_ADDRESS_RESPONSE       =   0x8040,
    E_SL_MSG_IEEE_ADDRESS_REQUEST           =   0x0041,
    E_SL_MSG_IEEE_ADDRESS_RESPONSE          =   0x8041,
    E_SL_MSG_NODE_DESCRIPTOR_REQUEST        =   0x0042,
    E_SL_MSG_NODE_DESCRIPTOR_RESPONSE       =   0x8042,
    E_SL_MSG_SIMPLE_DESCRIPTOR_REQUEST      =   0x0043,
    E_SL_MSG_SIMPLE_DESCRIPTOR_RESPONSE     =   0x8043,
    E_SL_MSG_POWER_DESCRIPTOR_REQUEST       =   0x0044,
    E_SL_MSG_POWER_DESCRIPTOR_RESPONSE      =   0x8044,
    E_SL_MSG_ACTIVE_ENDPOINT_REQUEST        =   0x0045,
    E_SL_MSG_ACTIVE_ENDPOINT_RESPONSE       =   0x8045,
    E_SL_MSG_MATCH_DESCRIPTOR_REQUEST       =   0x0046,
    E_SL_MSG_MATCH_DESCRIPTOR_RESPONSE      =   0x8046,
    E_SL_MSG_MANAGEMENT_LEAVE_REQUEST       =   0x0047,
    E_SL_MSG_MANAGEMENT_LEAVE_RESPONSE      =   0x8047,
    E_SL_MSG_LEAVE_INDICATION               =   0x8048,
    E_SL_MSG_PERMIT_JOINING_REQUEST         =   0x0049,
    E_SL_MSG_MANAGEMENT_NETWORK_UPDATE_REQUEST =0x004A,
    E_SL_MSG_MANAGEMENT_NETWORK_UPDATE_RESPONSE =0x804A,
    E_SL_MSG_SYSTEM_SERVER_DISCOVERY        =   0x004B,
    E_SL_MSG_SYSTEM_SERVER_DISCOVERY_RESPONSE  =   0x804B,
    E_SL_MSG_DEVICE_ANNOUNCE                =   0x004D,
    E_SL_MSG_MANAGEMENT_LQI_REQUEST       =   0x004E,
    E_SL_MSG_MANAGEMENT_LQI_RESPONSE      =   0x804E,

    /* Group Cluster */
    E_SL_MSG_ADD_GROUP                      =   0x0060,
    E_SL_MSG_ADD_GROUP_RESPONSE             =   0x8060,
    E_SL_MSG_VIEW_GROUP                     =   0x0061,
    E_SL_MSG_VIEW_GROUP_RESPONSE            =   0x8061,
    E_SL_MSG_GET_GROUP_MEMBERSHIP           =   0x0062,
    E_SL_MSG_GET_GROUP_MEMBERSHIP_RESPONSE  =   0x8062,
    E_SL_MSG_REMOVE_GROUP                   =   0x0063,
    E_SL_MSG_REMOVE_GROUP_RESPONSE          =   0x8063,
    E_SL_MSG_REMOVE_ALL_GROUPS              =   0x0064,
    E_SL_MSG_ADD_GROUP_IF_IDENTIFY          =   0x0065,

    /* Identify Cluster */
    E_SL_MSG_IDENTIFY_SEND                  =   0x0070,
    E_SL_MSG_IDENTIFY_QUERY                 =   0x0071,

    /* Level Cluster */
    E_SL_MSG_MOVE_TO_LEVEL                  =   0x0080,
    E_SL_MSG_MOVE_TO_LEVEL_ONOFF            =   0x0081,
    E_SL_MSG_MOVE_STEP                      =   0x0082,
    E_SL_MSG_MOVE_STOP_MOVE                 =   0x0083,
    E_SL_MSG_MOVE_STOP_ONOFF                =   0x0084,

    /* Scenes Cluster */
    E_SL_MSG_VIEW_SCENE                     =   0x00A0,
    E_SL_MSG_VIEW_SCENE_RESPONSE            =   0x80A0,
    E_SL_MSG_ADD_SCENE                      =   0x00A1,
    E_SL_MSG_ADD_SCENE_RESPONSE             =   0x80A1,
    E_SL_MSG_REMOVE_SCENE                   =   0x00A2,
    E_SL_MSG_REMOVE_SCENE_RESPONSE          =   0x80A2,
    E_SL_MSG_REMOVE_ALL_SCENES              =   0x00A3,
    E_SL_MSG_REMOVE_ALL_SCENES_RESPONSE     =   0x80A3,
    E_SL_MSG_STORE_SCENE                    =   0x00A4,
    E_SL_MSG_STORE_SCENE_RESPONSE           =   0x80A4,
    E_SL_MSG_RECALL_SCENE                   =   0x00A5,
    E_SL_MSG_SCENE_MEMBERSHIP_REQUEST       =   0x00A6,
    E_SL_MSG_SCENE_MEMBERSHIP_RESPONSE      =   0x80A6,

    /* Colour Cluster */
    E_SL_MSG_MOVE_TO_HUE                    =   0x00B0,
    E_SL_MSG_MOVE_HUE                       =   0x00B1,
    E_SL_MSG_STEP_HUE                       =   0x00B2,
    E_SL_MSG_MOVE_TO_SATURATION             =   0x00B3,
    E_SL_MSG_MOVE_SATURATION                =   0x00B4,
    E_SL_MSG_STEP_SATURATION                =   0x00B5,
    E_SL_MSG_MOVE_TO_HUE_SATURATION         =   0x00B6,
    E_SL_MSG_MOVE_TO_COLOUR                 =   0x00B7,
    E_SL_MSG_MOVE_COLOUR                    =   0x00B8,
    E_SL_MSG_STEP_COLOUR                    =   0x00B9,

/* ZLL Commands */
    /* Touchlink */
    E_SL_MSG_INITIATE_TOUCHLINK             =   0x00D0,
    E_SL_MSG_TOUCHLINK_STATUS               =   0x00D1,
    E_SL_MSG_TOUCHLINK_FACTORY_RESET        =   0x00D2,

    /* Identify Cluster */
    E_SL_MSG_IDENTIFY_TRIGGER_EFFECT        =   0x00E0,

    /* On/Off Cluster */
    E_SL_MSG_ONOFF_NOEFFECTS                =   0x0092,
    E_SL_MSG_ONOFF_TIMED                    =   0x0093,
    E_SL_MSG_ONOFF_EFFECTS                  =   0x0094,
    E_SL_MSG_ONOFF_UPDATE                   =   0x8095,

    /* Scenes Cluster */
    E_SL_MSG_ADD_ENHANCED_SCENE             =   0x00A7,
    E_SL_MSG_VIEW_ENHANCED_SCENE            =   0x00A8,
    E_SL_MSG_COPY_SCENE                     =   0x00A9,

    /* Colour Cluster */
    E_SL_MSG_ENHANCED_MOVE_TO_HUE           =   0x00BA,
    E_SL_MSG_ENHANCED_MOVE_HUE              =   0x00BB,
    E_SL_MSG_ENHANCED_STEP_HUE              =   0x00BC,
    E_SL_MSG_ENHANCED_MOVE_TO_HUE_SATURATION =  0x00BD,
    E_SL_MSG_COLOUR_LOOP_SET                =   0x00BE,
    E_SL_MSG_STOP_MOVE_STEP                 =   0x00BF,
    E_SL_MSG_MOVE_TO_COLOUR_TEMPERATURE     =   0x00C0,
    E_SL_MSG_MOVE_COLOUR_TEMPERATURE        =   0x00C1,
    E_SL_MSG_STEP_COLOUR_TEMPERATURE        =   0x00C2,

/* ZHA Commands */
    /* Door Lock Cluster */
    E_SL_MSG_LOCK_UNLOCK_DOOR                   =      0x00F0,
    E_SL_MSG_READ_ATTRIBUTE_REQUEST             =      0x0100,
    E_SL_MSG_READ_ATTRIBUTE_RESPONSE            =      0x8100,
    E_SL_MSG_DEFAULT_RESPONSE                   =      0x8101,
    E_SL_MSG_REPORT_IND_ATTR_RESPONSE           =      0x8102,
    E_SL_MSG_WRITE_ATTRIBUTE_REQUEST            =      0x0110,
    E_SL_MSG_WRITE_ATTRIBUTE_RESPONSE           =      0x8110,
    E_SL_MSG_CONFIG_REPORTING_REQUEST           =      0x0120,
    E_SL_MSG_CONFIG_REPORTING_RESPONSE          =      0x8120,
    E_SL_MSG_REPORT_ATTRIBUTES					=	   0x8121,
    E_SL_MSG_ATTRIBUTE_DISCOVERY_REQUEST		=      0x0140,
    E_SL_MSG_ATTRIBUTE_DISCOVERY_RESPONSE		=      0x8140,

    E_SL_MSG_SAVE_PDM_RECORD                    =      0x0200,
    E_SL_MSG_SAVE_PDM_RECORD_RESPONSE           =      0x8200,
    E_SL_MSG_LOAD_PDM_RECORD_REQUEST        	=      0x0201,
    E_SL_MSG_LOAD_PDM_RECORD_RESPONSE       	=      0x8201,
    E_SL_MSG_DELETE_PDM_RECORD                  =      0x0202,

    E_SL_MSG_PDM_HOST_AVAILABLE                 =      0x0300,
    E_SL_MSG_ASC_LOG_MSG                        =      0x0301,
    E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE        =      0x8300,
    /* IAS Cluster */
    E_SL_MSG_SEND_IAS_ZONE_ENROLL_RSP			=	   0x0400,
    E_SL_MSG_IAS_ZONE_STATUS_CHANGE_NOTIFY		=	   0x8401,


} teSL_MsgType;


/** Status message */
typedef struct
{
    enum
    {
        E_SL_MSG_STATUS_SUCCESS,
        E_SL_MSG_STATUS_INCORRECT_PARAMETERS,
        E_SL_MSG_STATUS_UNHANDLED_COMMAND,
        E_SL_MSG_STATUS_BUSY,
        E_SL_MSG_STATUS_STACK_ALREADY_STARTED,
    }  eStatus;
    uint8 u8SeqNum;
    char                acMessage[];            /**< Optional message */
}  tsSL_Msg_Status;

/** Structure containing a log message for passing to the host via the serial link */
typedef struct
{
	enum
	{
		E_SL_LOG_EMERG,
		E_SL_LOG_ALERT,
		E_SL_LOG_CRIT,
		E_SL_LOG_ERR,
		E_SL_LOG_WARNING,
		E_SL_LOG_NOTICE,
		E_SL_LOG_INFO,
		E_SL_LOG_DEBUG,
	} PACK eLevel;
	uint8 au8Message[256];
}  tsSL_Msg_Log;

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

PUBLIC bool bSL_ReadMessage(uint16 *pu16Type, uint16 *pu16Length, uint16 u16MaxLength, uint8 *pu8Message,uint8 u8Byte);
PUBLIC void vSL_WriteMessage(uint16 u16Type, uint16 u16Length, uint8 *pu8Data);
PUBLIC uint8 u8SL_CalculateCRC(uint16 u16Type, uint16 u16Length, uint8 *pu8Data);
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* SERIALLINK_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
