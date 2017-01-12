/****************************************************************************
 *
 * MODULE:             Customer Module Evaluation Tool
 *
 * COMPONENT:          CustomerModuleEvalTool.c
 *
 * VERSION:            CustomerModuleEvalTool.c
 *
 * REVISION:           Revision: 1.02
 *
 * DATED:              Date: 2009/03/24
 *
 * STATUS:             State: Exp
 *
 * AUTHOR:             LM
 *
 * DESCRIPTION:
 * Code to run module based lab tests. User interaction is via serial
 * console at 38400 baud.
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

 * Copyright NXP B.V. 2012. All rights reserved
 *
***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <AppHardwareApi.h>
#include <JPT.h>
#include "Printf.h"
#include "UartBuffered.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define TIMEOUT_PER_TEST        10000
#define TIMEOUT_RESULTS         10000
#define TIMEOUT_COMMS_TO_MUT    4000000

#define PIN_SG_TRIGGER          1 << 8              /* Gig Gen Trigger Pin  */
#define PIN_DEBUG               1 << 0

#define UART_TO_PC              E_AHI_UART_0        /* Uart to PC           */
#define UART_TO_OTHER           E_AHI_UART_1        /* Uart to other board  */

#define BAUD_RATE               E_AHI_UART_RATE_38400 /* Baud rate to use   */

/* Duty cycles */
#define DC_100                  1
#define DC_50                   2
#define DC_30                   3
#define DC_1                    4
#define DC_VARIABLE             5

#define MAJOR_VERSION_NO        2
#define MINOR_VERSION_NO        1



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vDoPerTest(void);
PRIVATE void vPerTestMaster(uint8 u8Chan);
PRIVATE bool_t bPerTestSlave(uint8 u8Chan);
PRIVATE uint8 u8DeriveThroughput(uint32 u32FramesSeen, uint32 u32Acks);



PRIVATE void vPutC(uint8 u8Data);
PRIVATE char acGetC(void);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

uint64 u64MacAddress = 0;
uint32 u32MacAddressHigh = 0;
uint32 u32MacAddressLow = 0;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/


#if 0
	static uint8 au8Uart0TxBuffer[16];
	static uint8 au8Uart0RxBuffer[16];

	static uint8 au8Uart1TxBuffer[16];
	static uint8 au8Uart1RxBuffer[16];

#endif


	uint8 au8UartTxBuffer[100];
	uint8 au8UartRxBuffer[100];

	uint8 au8Uart1TxBuffer[100];
	uint8 au8Uart1RxBuffer[100];


char acFrequencies[][10] = {{"2.405 GHz\0"},
                            {"2.410 GHz\0"},
                            {"2.415 GHz\0"},
                            {"2.420 GHz\0"},
                            {"2.425 GHz\0"},
                            {"2.430 GHz\0"},
                            {"2.435 GHz\0"},
                            {"2.440 GHz\0"},
                            {"2.445 GHz\0"},
                            {"2.450 GHz\0"},
                            {"2.455 GHz\0"},
                            {"2.460 GHz\0"},
                            {"2.465 GHz\0"},
                            {"2.470 GHz\0"},
                            {"2.475 GHz\0"},
                            {"2.480 GHz\0"}};

uint32 u32RadioMode     = E_JPT_MODE_LOPOWER;

uint8 u8MaxTxPower      = 5;
uint8 u8MaxTxPowerFine  = 47;


uint16 u16OnTime        = 0xffff;
uint16 u16OffTime       = 0xffff;

uint32 u32PowerTestMode = E_JPT_TXPT_RUN_CW;

uint32 u32ClkMultiply   = 1;


PUBLIC void vDebug(char *pcMessage)
{
    while (*pcMessage)
    {
        while ((u8AHI_UartReadLineStatus(0) & 0x20) == 0);
        vAHI_UartWriteData(0, *pcMessage);
        pcMessage++;
    }
}
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void AppColdStart(void)
{

    char   acCommand = 0;
    bool_t bExitLoop = FALSE;
    uint32 u32JPT_Ver;
    uint32 u32JPT_RadioModes = 0;

    // Menu keystokes
	uint8  u8LPKey = 0;
	uint8  u8LPBKey = 0;
	uint8  u8LP0Key = 0;
	uint8  u8HPKey = 0;
	uint8  u8HPEKey = 0;
	uint8  u8HPE6Key = 0;

#ifdef JENNIC_CHIP_FAMILY_JN516x

    /* Turn off debugger */
    *(volatile uint32 *)0x020000a0 = 0;
#endif

    /* Disable watchdog if enabled by default */
    #ifdef WATCHDOG_ENABLED
    vAHI_WatchdogStop();
    #endif


    u32JPT_Ver = u32JPT_Init();                 /* initialise production test API */

    u32JPT_RadioModes = u32JPT_RadioModesAvailable(); /* Get the Modes supported by this device */
    u32AHI_Init();                              /* initialise hardware API */

	vUartInit(UART_TO_PC, BAUD_RATE, au8UartTxBuffer, sizeof(au8UartTxBuffer), au8UartRxBuffer, sizeof(au8UartRxBuffer));/* uart for user interface */

    vInitPrintf((void*)vPutC);

    vAHI_DioSetPullup(0xffffffff, 0x00000000);  /* turn all pullups on      */

    // Default to DIO2 and DIO3 output low
    vAHI_DioSetDirection(0,0xc);	// set DIO2&3 to output
    vAHI_DioSetOutput(0,0);

    /* Get module type, low or high power */
    while(!bExitLoop){
    	uint8 u8MenuCtr=97;   // ASCII 'a'
        vPrintf("\n*********************************************"
                "\n*    Customer Module Evaluation PER Tool        *"
                "\n*    Version %2d.%02d                          *"
                "\n*    Compiled %s %s          *"
                "\n*    Production Test API Version %08x *"
                "\n*********************************************\n", MAJOR_VERSION_NO, MINOR_VERSION_NO, __DATE__, __TIME__, u32JPT_Ver);
        if (u32JPT_RadioModes & (1<<E_JPT_MODE_LOPOWER)){
        	u8LPKey = u8MenuCtr;
        	vPrintf("\n%c) Standard Module",u8MenuCtr++);
		}
		if (u32JPT_RadioModes & (1<<E_JPT_MODE_BOOST)){
			u8LPBKey = u8MenuCtr;
			vPrintf("\n%c) Standard Module (Boost Mode)",u8MenuCtr++);
		}
		if (u32JPT_RadioModes & (1<<E_JPT_MODE_0DBM)){
			u8LP0Key = u8MenuCtr;
			vPrintf("\n%c) Standard Module (0dBm  Mode)",u8MenuCtr++);
		}
		if (u32JPT_RadioModes & (1<<E_JPT_MODE_HIPOWER)){
			u8HPKey = u8MenuCtr;
			vPrintf("\n%c) High Power Module",u8MenuCtr++);
		}
		if (u32JPT_RadioModes & (1<<E_JPT_MODE_ETSI)){
			u8HPEKey = u8MenuCtr;
			vPrintf("\n%c) High Power Module (ETSI-M04 Mode)",u8MenuCtr++);
		}
		if (u32JPT_RadioModes & (1<<E_JPT_MODE_ETSIM06)){
			u8HPE6Key = u8MenuCtr;
			vPrintf("\n%c) High Power Module (ETSI-M06 Mode)",u8MenuCtr++);
		}
		vPrintf("\n\nPlease choose an option > ");

		acCommand = acGetC();

		if (acCommand != 0){
			vPutC(acCommand);

			if ((acCommand == u8LPKey) || ((acCommand|0x20) == u8LPKey)){
				/* Low Power Module */
				vPrintf(" Standard Module Selected\n");
				u32RadioMode = E_JPT_MODE_LOPOWER;
				bExitLoop = TRUE;
			}
			else if ((acCommand == u8LPBKey) || ((acCommand|0x20) == u8LPBKey)){
				/* Boost mode */
				vPrintf(" Boost Mode Selected\n");
				u32RadioMode = E_JPT_MODE_BOOST;
				bExitLoop = TRUE;
			}
			else if ((acCommand == u8LP0Key) || ((acCommand|0x20) == u8LP0Key)){
				/* 0dBm mode */
				vPrintf(" 0Db Mode Selected\n");
				u32RadioMode = E_JPT_MODE_0DBM;
				u8MaxTxPower = 3;
				bExitLoop = TRUE;
			}
			else if ((acCommand == u8HPKey) || ((acCommand|0x20) == u8HPKey)){
				/* High Power Module */
				vPrintf(" HP Mode Selected\n");
				u32RadioMode = E_JPT_MODE_HIPOWER;
				bExitLoop = TRUE;
			}
			else if ((acCommand == u8HPEKey) || ((acCommand|0x20) == u8HPEKey)){
				/* High Power ETSI (M04) Module */
				vPrintf(" HP-M04 (ETSI) Mode Selected\n");
				u8MaxTxPower = 2;
				u32RadioMode = E_JPT_MODE_ETSI;
				bExitLoop = TRUE;
			}
			else if ((acCommand == u8HPE6Key) || ((acCommand|0x20) == u8HPE6Key)){
			    /* High Power ETSI (M06) Module */
				vPrintf(" HP-M06 (ETSI) Mode Selected\n");
				u32RadioMode = E_JPT_MODE_ETSIM06;
				// u8MaxTxPower = 1;
				bExitLoop = TRUE;
			}
		}
	}

    /* Sit in loop forever */
    while (1) {
                vPrintf("\f*******************"
                        "\n*   Do PER TEST   *"
                        "\n*******************\n");

              vDoPerTest();

    }

}


PUBLIC void AppWarmStart(void)
{
    AppColdStart();
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME:       vDoPerTest
 *
 * DESCRIPTION:
 * A sub menu allowing the user to choose between operating as a PER test
 * master or a PER test slave.
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vDoPerTest(void)
{

    uint8  u8Chan;
    bool_t bExit = FALSE;

    vUartInit(UART_TO_PC, BAUD_RATE, au8UartTxBuffer, sizeof(au8UartTxBuffer), au8UartRxBuffer, sizeof(au8UartRxBuffer));/* uart for user interface */
	vUartInit(UART_TO_OTHER, BAUD_RATE, au8Uart1TxBuffer, sizeof(au8Uart1TxBuffer), au8Uart1RxBuffer, sizeof(au8Uart1RxBuffer));/* uart for link to other board */

    while(1){

        vPrintf("\n***************************************"
                "\n*       Packet Error Rate Test        *"
                "\n***************************************\n"
                "\nNote, this test requires the following"
                "\nconnections to be made :-\n"
                "\n  Master                        Slave"
                "\n  DIO 14  <------------------>  DIO 15"
                "\n  DIO 15  <------------------>  DIO 14"
                "\n  GND     <------------------>  GND\n"
                "\na) Run as PER Test Master (Controller)"
                "\nb) Run as PER Test Slave  (D.U.T)"
                "\nx) Return to main menu"
                "\n\nPlease choose an option >");

        switch(acGetC()){

        /* act as a PER test master */
        case 'a':
        case 'A':
            /* enable protocol */
            bJPT_RadioInit(u32RadioMode);

            /* set default power level */
            vJPT_RadioSetPower(u8MaxTxPower);

            vPrintf("\f");
            vPrintf("\nChannel\t\tHeaders Seen\tPackets Seen\tAcks Received\tThroughput(%%)");

            for (u8Chan=11; u8Chan<=26; u8Chan++)
            {
                vPrintf("\n  %d\t\t   ",u8Chan);
#ifdef TXPOWERADJUST
				u8PowerAdjustChannel = u8Chan;
				//vJPT_TxPowerAdjust(u8TxPowerAdj, u8Attenuator3dB, u8PowerAdjustChannel);
				vJPT_TxPowerAdjust(0, 0, u8PowerAdjustChannel);
#endif
                vPerTestMaster(u8Chan);
            }

            /* disable protocol */
            vJPT_RadioDeInit();

            vPrintf("\n\nPress any key to continue..");
            acGetC();
            break;

        /* act as a per test slave */
        case 'b':
        case 'B':
            /* enable protocol */
            bJPT_RadioInit(u32RadioMode);

            /* set default power level */
            vJPT_RadioSetPower(u8MaxTxPower);

            vPrintf("\fRunning as PER test slave (DUT), press x to exit");

            do {
                for (u8Chan=11; u8Chan<=26; u8Chan++) {
#ifdef TXPOWERADJUST
					u8PowerAdjustChannel = u8Chan;
					//vJPT_TxPowerAdjust(u8TxPowerAdj, u8Attenuator3dB, u8PowerAdjustChannel);
					vJPT_TxPowerAdjust(0, 0, u8PowerAdjustChannel);
#endif
                    if(!bPerTestSlave(u8Chan)){
                        bExit = TRUE;
                        break;
                    }
                }
            } while (!bExit);

            /* disable protocol */
            vJPT_RadioDeInit();
            break;


        case 'x':
        case 'X':
            vUartDeInit(UART_TO_OTHER);                         /* turn uart off */
            return;
            break;

        }

    }

}


/****************************************************************************
 *
 * NAME:       vDoPerTestMaster
 *
 * DESCRIPTION:
 * Transmits packets on the specified channel and looks for acknowledges from
 * a device operating as the PER test slave. A count is kept of the number
 * of packets sent and the number of ack's received. After performing a number
 * of repetitions, a command is sent via uart to the PER test slave to request
 * its results (number of headers received and number of frames received), and
 * then the results are displayed.
 *
 * PARAMETERS:      Name        RW  Usage
 *                  u8Channel   R   Channel to transmit on
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vPerTestMaster(uint8 u8Channel)
{
    int i;
    uint32 u32Acks;
    uint16 u16Reps;
    uint32 u32HeadersSeen;
    uint32 u32FramesSeen;
    uint32 u32Timeout;
    uint8  u8Throughput;

    /* select channel */
    bJPT_RadioSetChannel(u8Channel);

    vJPT_MTPT_MasterStart(100);

    u32Acks = 0;
    u16Reps = 500;

    for(i = 0; i < u16Reps; i++){

        vJPT_MTPT_MasterTxPacket(&u32Acks);

    }

    /* request results from MUT */
    vUartWrite(UART_TO_OTHER, 'r');

    /* wait for results to arrive over UART */
    u32Timeout = 0;
    while(!bUartRxDataAvailable(UART_TO_OTHER)){
        u32Timeout++;

        if(u32Timeout > TIMEOUT_RESULTS * u32ClkMultiply){
            vPrintf("No data returned from PER Test Slave, Check connections !");
            vUartFlush(UART_TO_OTHER);
            return;
        }
    }

    vJPT_MTPT_MasterStop();

    /* receive results over UART1 */
    bUartReadBinary(UART_TO_OTHER, (uint8*)&u32HeadersSeen, sizeof(u32HeadersSeen), TIMEOUT_RESULTS);
    bUartReadBinary(UART_TO_OTHER, (uint8*)&u32FramesSeen, sizeof(u32FramesSeen), TIMEOUT_RESULTS);

    /* calculate PER */
	#ifndef JENNIC_CHIP_FAMILY_JN516x	// NON 6x implementation
		u8Throughput = u8DeriveThroughput(u32HeadersSeen, u32Acks);      /* calculate the percentage throughput */

	#else		// 6x implementation
    	u8Throughput = u8DeriveThroughput(u16Reps, u32Acks);      /* calculate the percentage throughput */

	#endif

    /* need to format and display the results here */
    vPrintf("%d\t\t   %d\t\t   %d\t\t     %d",u32HeadersSeen, u32FramesSeen, u32Acks, u8Throughput);

}


/****************************************************************************
 *
 * NAME:       bPerTestSlave
 *
 * DESCRIPTION:
 * Checks for received packets (both headers and complete frames), and keeps
 * a running total of the number of each received, then waits for a command
 * via UART from a device running as the PER test master and transmits the
 * results back via UART.
 *
 * PARAMETERS:      Name        RW  Usage
 *                  u8Chan      R   Channel to listen for packets on
 *
 * RETURNS:
 * bool_t, FALSE if the function exited due to a keypress
 *         TRUE if the function returned normally
 *
 ****************************************************************************/
PRIVATE bool_t bPerTestSlave(uint8 u8Channel)
{
    uint32 u32HeadersSeen = 0;
    uint32 u32FramesSeen = 0;
    uint32 u32ErrorsSeen = 0;

    uint8  u8CommandChar = '0';
    uint8 u8Cmd;

    bJPT_RadioSetChannel(u8Channel);

    vJPT_MTPT_SlaveStart();

    /* Wait for frames */

    do
    {

        vJPT_MTPT_SlavePoll(&u32HeadersSeen, &u32FramesSeen, &u32ErrorsSeen);

        /* see if any key presses */
        if(bUartRxDataAvailable(UART_TO_PC)){
            u8Cmd = u8UartRead(UART_TO_PC);
            if(u8Cmd == 'x' || u8Cmd == 'X'){
                return(0);
            }
        }

        /* see if a command byte has arrived over the UART */
        if(bUartRxDataAvailable(UART_TO_OTHER)){
            u8CommandChar = u8UartRead(UART_TO_OTHER);
        }
    } while (u8CommandChar != 'r');

    vJPT_MTPT_SlaveStop();

    vUartWriteBinary(UART_TO_OTHER, (uint8*)&u32HeadersSeen, sizeof(u32HeadersSeen));
    vUartWriteBinary(UART_TO_OTHER, (uint8*)&u32FramesSeen, sizeof(u32FramesSeen));

    return(1);

}





/****************************************************************************
 *
 * NAME:       u8DeriveThroughput
 *
 * DESCRIPTION:
 * Calculates the Throughput in Percent given the number of headers
 * received at the Slave and the number of acknowdgements received back at
 * the Master
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u32HeadersSeen  R   No. of headers received at the Slave
 *                  u32Acks         R   No. or return acks at the Master
 * RETURNS:
 * uint8            Throughput in percent (100% = all packets received)
 *
 * NOTE:	now redundant in 6x code.. left in for compatibility with AN1132
 *
 ****************************************************************************/
PRIVATE uint8 u8DeriveThroughput(uint32 u32HeadersSeen, uint32 u32Acks)
{
    return (uint8)((u32Acks * 100) / u32HeadersSeen);
}




/****************************************************************************
 *
 * NAME:       vPutC
 *
 * DESCRIPTION:
 * Writes a byte to the UART connected to the PC.
 *
 * PARAMETERS:      Name        RW  Usage
 *                  u8Data      R   Byte to write to the UART
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vPutC(uint8 u8Data)
{
    vUartWrite(UART_TO_PC, u8Data);

    // while ((u8AHI_UartReadLineStatus(0) & 0x20) == 0);
    // vAHI_UartWriteData(0, u8Data);

}


/****************************************************************************
 *
 * NAME:       acGetC
 *
 * DESCRIPTION:
 * Reads a character from the uart connected to the pc. If no character is
 * waiting in the rx buffer, it will wait until there is.
 *
 *
 * RETURNS:
 * char, Character read from the UART
 *
 ****************************************************************************/
PRIVATE char acGetC(void)
{
    return(u8UartRead(UART_TO_PC));
}


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

