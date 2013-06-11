/*******************************************************************************
 * File Name: LCD_1.h
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

#include "LCD_1_lcd.h"
#include "device.h"
#include "glcdfont.h"

#define STATE_COMMAND 0x00
#define STATE_DATA 0x02

uint8 LCD_1_initVar = 0;
uint8 transmit_dma, buffer_td, interrupt_td, do_nothing;
LCD_1_buffer *current_buffer = null;
uint8 row = 0, column = 0;

void set_state(uint8 state) {
    uint8 current_state = LCD_1_LCD_Control_Read();
    if((current_state & 0x02) != state) {
        while(LCD_1_Busy());
        if(state == STATE_DATA) {
            LCD_1_LCD_Control_Write(current_state | STATE_DATA);
        } else {
            LCD_1_LCD_Control_Write(current_state & ~STATE_DATA);
        }
    }
}

void LCD_1_Start(void) {
    if(LCD_1_initVar == 0) {
        LCD_1_Init();
        LCD_1_Enable();
        LCD_1_initVar = 1;
    }
}

void LCD_1_Init(void) {
    LCD_1_LCD_SPI_Init();
}

void LCD_1_Enable(void) {
    // Take display out of reset
    LCD_1_LCD_Control_Write(0x01);

    // Enable the SPI interface
    LCD_1_LCD_SPI_Enable();

    // Default display settings
    LCD_1_SendCommand(LCD_1_SET_START_LINE | 0);
    LCD_1_SendCommand(LCD_1_ADC_SELECT | 1); // ADC reverse
    LCD_1_SendCommand(LCD_1_COMMON_SELECT | 0); // Normal COM0-COM63
    LCD_1_SendCommand(LCD_1_DISPLAY_REVERSE | 0); // Normal
    LCD_1_SendCommand(LCD_1_SET_BIAS | 0); // 1/9 bias
    LCD_1_SendCommand(LCD_1_POWER_CONTROL | 0x7); // Booster, regulator, follower on
    LCD_1_SendLongCommand(LCD_1_SET_BOOSTER_RATIO | 0x4); // 4x booster
    LCD_1_SendCommand(LCD_1_V0_REGULATOR_RATIO | 0x7); // Regulator resistor ratio
    LCD_1_SendLongCommand(LCD_1_SET_VOLUME | 0x16); // Set contrast
    LCD_1_SendCommand(LCD_1_SET_STATIC_INDICATOR | 0); // No indicator
    LCD_1_SendCommand(LCD_1_POWER | 1); // Power on.
}

void LCD_1_SendCommand(uint8 command) {
    set_state(STATE_COMMAND);
    LCD_1_LCD_SPI_WriteTxData(command);
}

void LCD_1_SendLongCommand(uint16 command) {
    set_state(STATE_COMMAND);
    LCD_1_LCD_SPI_WriteTxData((uint8)(command >> 8));
    LCD_1_LCD_SPI_WriteTxData((uint8)(command & 0xff));
}

LCD_1_buffer* LCD_1_Update(LCD_1_buffer *new_buffer, uint8 start_page, uint8 end_page) {
    LCD_1_buffer *ret = current_buffer;
    int i, j;

    current_buffer = new_buffer;
    
    for(i = start_page; i < end_page; i++) {
        // Set page and column
        LCD_1_SendCommand(LCD_1_SET_PAGE | (start_page & 0xF));
        LCD_1_SendLongCommand(LCD_1_SET_COLUMN | 0);

        // Switch to data mode
        set_state(STATE_DATA);
        
        // Send the page of data
        for(j = 0; j < LCD_1_COLUMNS; j++)
            LCD_1_LCD_SPI_WriteTxData(current_buffer[page * LCD_1_COLUMNS + j]);
    }
}

int LCD_1_Busy(void) {
    return !(LCD_1_LCD_SPI_ReadTxStatus() & (LCD_1_LCD_SPI_STS_SPI_DONE | LCD_1_LCD_SPI_STS_SPI_IDLE));
}

void LCD_1_PrintString(char *s) {
    char *c;
    uint8_t i;
    
    for(c = s; *c != '\0'; c++) {
        if(column + 6 >= LCD_1_VISIBLE_COLUMNS) {
            column = 0;
            row = (row + 1) % LCD_1_ROWS;
        }
        
        // Draw the letter
        for(i = 0; i < 5; i++) {
            current_buffer[row * LCD_1_COLUMNS + column] = glcd_font[*c * 5 + i];
            buf->column++;
        }
        
        // Empty column between letters
        current_buffer[row * LCD_1_COLUMNS + column] = 0;
        column++;
    }
    
    LCD_1_Update(current_buffer, 0, 8);
}

void LCD_1_Position(uint8 r, uint8 c) {
    row = r;
    column = c;
}

void LCD_1_ClearDisplay() {
    memset(current_buffer, 0, sizeof(LCD_1_buffer));
    LCD_1_Update(current_buffer, 0, 8);
}

/* [] END OF FILE */
