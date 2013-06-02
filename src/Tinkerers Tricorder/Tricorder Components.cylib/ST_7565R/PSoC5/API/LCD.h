/*******************************************************************************
 * File Name: `$INSTANCE_NAME`.h
 * Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
 *
 *  Description:
 *    Provides an interface to ST 7565R LCD controllers.
 *
 *******************************************************************************
 *
 * Copyright Arachnid Labs, 2013
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
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
 *******************************************************************************/

#include <cytypes.h>

#if !defined(ST7565R_`$INSTANCE_NAME`_H)
#define ST7565R_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_POWER 0xAE
#define `$INSTANCE_NAME`_SET_START_LINE 0x40
#define `$INSTANCE_NAME`_SET_PAGE 0xB0
#define `$INSTANCE_NAME`_SET_COLUMN 0x1000
#define `$INSTANCE_NAME`_ADC_SELECT 0xA0
#define `$INSTANCE_NAME`_DISPLAY_REVERSE 0xA6
#define `$INSTANCE_NAME`_DISPLAY_ALL_PTS 0xA4
#define `$INSTANCE_NAME`_SET_BIAS 0xA2
#define `$INSTANCE_NAME`_RESET 0xE2
#define `$INSTANCE_NAME`_COMMON_SELECT 0xC8
#define `$INSTANCE_NAME`_POWER_CONTROL 0x28
#define `$INSTANCE_NAME`_V0_REGULATOR_RATIO 0x20
#define `$INSTANCE_NAME`_SET_VOLUME 0x8100
#define `$INSTANCE_NAME`_SET_STATIC_INDICATOR 0xAC00
#define `$INSTANCE_NAME`_SET_BOOSTER_RATIO 0xF800
#define `$INSTANCE_NAME`_NOP 0xE3

#define `$INSTANCE_NAME`_COLUMNS 132
#define `$INSTANCE_NAME`_VISIBLE_COLUMNS 128
#define `$INSTANCE_NAME`_ROWS 64
#define `$INSTANCE_NAME`_BUFFER_SIZE ((`$INSTANCE_NAME`_COLUMNS * `$INSTANCE_NAME`_ROWS) / 8)

typedef struct `$INSTANCE_NAME`_buffer {
    uint8 data[`$INSTANCE_NAME`_BUFFER_SIZE];
} `$INSTANCE_NAME`_buffer;

extern uint8 `$INSTANCE_NAME`_initVar;

extern void `$INSTANCE_NAME`_Start(void);
extern void `$INSTANCE_NAME`_Init(void);
extern void `$INSTANCE_NAME`_Enable(void);

extern void `$INSTANCE_NAME`_SendCommand(uint8);
extern void `$INSTANCE_NAME`_SendLongCommand(uint16);
extern `$INSTANCE_NAME`_buffer* `$INSTANCE_NAME`_Update(`$INSTANCE_NAME`_buffer*, uint8, uint8);

extern int `$INSTANCE_NAME`_Busy(void);

extern void `$INSTANCE_NAME`_PrintString(char *s);
extern void `$INSTANCE_NAME`_PutChar(char c);
extern void `$INSTANCE_NAME`_Position(uint8 row, uint8 column);
extern void `$INSTANCE_NAME`_ClearDisplay();


#endif
//[] END OF FILE
