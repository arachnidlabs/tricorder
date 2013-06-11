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

#include "LCD_LCD.h"
#include "device.h"
#include "glcdfont.h"

#define STATE_COMMAND 0x00
#define STATE_DATA 0x02

uint8 LCD_initVar = 0;
uint8 transmit_dma, buffer_td, interrupt_td, do_nothing;
LCD_buffer *current_buffer = NULL;
uint8 page = 0, column = LCD_START_COLUMN;

void set_state(uint8 state) {
    uint8 current_state = LCD_LCD_Control_Read();
    if((current_state & 0x02) != state) {
        while(LCD_Busy());
        if(state == STATE_DATA) {
            LCD_LCD_Control_Write(current_state | STATE_DATA);
        } else {
            LCD_LCD_Control_Write(current_state & ~STATE_DATA);
        }
    }
}

void LCD_Start(void) {
    if(LCD_initVar == 0) {
        LCD_Init();
        LCD_Enable();
        LCD_initVar = 1;
    }
}

void LCD_Init(void) {
    LCD_LCD_SPI_Init();
}

void LCD_Enable(void) {
    // Take display out of reset
    LCD_LCD_Control_Write(0x01);

    // Enable the SPI interface
    LCD_LCD_SPI_Enable();

    // Default display settings
    LCD_SendCommand(LCD_SET_START_LINE | 0);
    LCD_SendCommand(LCD_ADC_SELECT | 0); // ADC normal
    LCD_SendCommand(LCD_COMMON_SELECT | 8); // Reverse COM63-COM0
    LCD_SendCommand(LCD_DISPLAY_REVERSE | 0); // Normal
    LCD_SendCommand(LCD_SET_BIAS | 0); // 1/9 bias
    LCD_SendCommand(LCD_POWER_CONTROL | 0x7); // Booster, regulator, follower on
    LCD_SendLongCommand(LCD_SET_BOOSTER_RATIO | 0x0); // 4x booster
    LCD_SendCommand(LCD_V0_REGULATOR_RATIO | 0x7); // Regulator resistor ratio
    LCD_SendLongCommand(LCD_SET_VOLUME | 0x16); // Set contrast
    LCD_SendLongCommand(LCD_SET_STATIC_INDICATOR | 0); // No indicator
    LCD_SendCommand(LCD_POWER | 1); // Power on.
}

void LCD_SendCommand(uint8 command) {
    set_state(STATE_COMMAND);
    LCD_LCD_SPI_WriteTxData(command);
}

void LCD_SendLongCommand(uint16 command) {
    set_state(STATE_COMMAND);
    LCD_LCD_SPI_WriteTxData((uint8)(command >> 8));
    LCD_LCD_SPI_WriteTxData((uint8)(command & 0xff));
}

void _PutChar(char c) {
    uint8 i;
    
    if(column + 6 >= LCD_VISIBLE_COLUMNS) {
        column = LCD_START_COLUMN;
        page = (page + 1) % (LCD_ROWS / 8);
    }
    
    // Draw the letter
    for(i = 0; i < 5; i++) {
        current_buffer->data[page * LCD_COLUMNS + column] = glcd_font[c * 5 + i];
        column++;
    }
    
    // Empty column between letters
    current_buffer->data[page * LCD_COLUMNS + column] = 0;
    column++;
}

LCD_buffer* LCD_Update(LCD_buffer *new_buffer, uint8 start_page, uint8 end_page) {
    LCD_buffer *ret = current_buffer;
    int i, j;

    current_buffer = new_buffer;
    
    for(i = start_page; i < end_page; i++) {
        // Set page and column
        LCD_SendCommand(LCD_SET_PAGE | (i & 0xF));
        LCD_SendLongCommand(LCD_SET_COLUMN | 0);

        // Switch to data mode
        set_state(STATE_DATA);
        
        // Send the page of data
        for(j = 0; j < LCD_COLUMNS; j++)
            LCD_LCD_SPI_WriteTxData(current_buffer->data[i * LCD_COLUMNS + j]);
    }
    
    return ret;
}

int LCD_Busy(void) {
    return !(LCD_LCD_SPI_ReadTxStatus() & (LCD_LCD_SPI_STS_SPI_DONE | LCD_LCD_SPI_STS_SPI_IDLE));
}

void LCD_PrintString(char *s) {
    char *c;
    
    for(c = s; *c != '\0'; c++)
        _PutChar(*c);
    
    LCD_Update(current_buffer, 0, 8);
}

void LCD_PutChar(char c) {
    _PutChar(c);
    LCD_Update(current_buffer, 0, 8);
}

void LCD_Position(uint8 r, uint8 c) {
    page = r;
    column = (c * 6) + LCD_START_COLUMN;
}

void LCD_ClearDisplay() {
    memset(current_buffer->data, 0, LCD_BUFFER_SIZE);
    LCD_Update(current_buffer, 0, 8);
}

/* [] END OF FILE */
