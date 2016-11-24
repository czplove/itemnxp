/*****************************************************************************
 *
 * MODULE:          JN-AN-1189
 *
 * COMPONENT:       app_blink_led.h
 *
 * DESCRIPTION:     ZHA Demo: Blinks an LED a number of pre defined ticks
 *
 *****************************************************************************
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
 ****************************************************************************/
#ifndef APP_APP_BLINK_LED_H_
#define APP_APP_BLINK_LED_H_

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define APP_LEDS_NUM         (4UL)
#define BOARDLED0_pin            (16)
#define BOARDLED1_pin            (13)
#define BOARDLED2_pin            (0)
#define BOARDLED3_pin            (16)


#define BOARDLED0            (1 << BOARDLED0_pin)
#define BOARDLED1            (1 << BOARDLED1_pin)
#define BOARDLED2            (1 << BOARDLED2_pin)
#define BOARDLED3            (1 << BOARDLED3_pin)

#define APP_LedS_DIO_MASK        ((1 << BOARDLED0_pin) | (1 << BOARDLED1_pin) | (1 << BOARDLED2_pin) | (1 << BOARDLED3_pin))

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vToggleLED(void);
PUBLIC void vStartBlinkTimer(uint32 u32Ticks);
PUBLIC void vStopBlinkTimer(void);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#endif /* APP_APP_BLINK_LED_H_ */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
