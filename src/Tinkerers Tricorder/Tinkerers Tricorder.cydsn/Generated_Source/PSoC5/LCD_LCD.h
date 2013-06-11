/*******************************************************************************
 * File Name: LCD.h
 * Version 0.0
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

#if !defined(ST7565R_LCD_H)
#define ST7565R_LCD_H

#define LCD_POWER 0xAE
#define LCD_SET_START_LINE 0x40
#define LCD_SET_PAGE 0xB0
#define LCD_SET_COLUMN 0x1000
#define LCD_ADC_SELECT 0xA0
#define LCD_DISPLAY_REVERSE 0xA6
#define LCD_DISPLAY_ALL_PTS 0xA4
#define LCD_SET_BIAS 0xA2
#define LCD_RESET 0xE2
#define LCD_COMMON_SELECT 0xC8
#define LCD_POWER_CONTROL 0x28
#define LCD_V0_REGULATOR_RATIO 0x20
#define LCD_SET_VOLUME 0x8100
#define LCD_SET_STATIC_INDICATOR 0xAC00
#define LCD_SET_BOOSTER_RATIO 0xF800
#define LCD_NOP 0xE3

#define LCD_COLUMNS 132
#define LCD_VISIBLE_COLUMNS 128
#define LCD_START_COLUMN 4
#define LCD_ROWS 64
#define LCD_BUFFER_SIZE ((LCD_COLUMNS * LCD_ROWS) / 8)

typedef struct LCD_buffer {
    uint8 data[LCD_BUFFER_SIZE];
} LCD_buffer;

extern uint8 LCD_initVar;

extern void LCD_Start(void);
extern void LCD_Init(void);
extern void LCD_Enable(void);

extern void LCD_SendCommand(uint8);
extern void LCD_SendLongCommand(uint16);
extern LCD_buffer* LCD_Update(LCD_buffer*, uint8, uint8);

extern int LCD_Busy(void);

extern void LCD_PrintString(char *s);
extern void LCD_PutChar(char c);
extern void LCD_Position(uint8 row, uint8 column);
extern void LCD_ClearDisplay();


#endif
//[] END OF FILE
