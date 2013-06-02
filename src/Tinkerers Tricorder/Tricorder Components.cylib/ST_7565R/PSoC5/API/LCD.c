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

#include "`$INSTANCE_NAME`_LCD.h"
#include "device.h"
#include "glcdfont.h"

#define STATE_COMMAND 0x00
#define STATE_DATA 0x02

uint8 `$INSTANCE_NAME`_initVar = 0;
uint8 transmit_dma, buffer_td, interrupt_td, do_nothing;
`$INSTANCE_NAME`_buffer *current_buffer = NULL;
uint8 page = 0, column = 0;

void set_state(uint8 state) {
    uint8 current_state = `$INSTANCE_NAME``[LCD_Control]`Read();
    if((current_state & 0x02) != state) {
        while(`$INSTANCE_NAME`_Busy());
        if(state == STATE_DATA) {
            `$INSTANCE_NAME``[LCD_Control]`Write(current_state | STATE_DATA);
        } else {
            `$INSTANCE_NAME``[LCD_Control]`Write(current_state & ~STATE_DATA);
        }
    }
}

void `$INSTANCE_NAME`_Start(void) {
    if(`$INSTANCE_NAME`_initVar == 0) {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_Enable();
        `$INSTANCE_NAME`_initVar = 1;
    }
}

void `$INSTANCE_NAME`_Init(void) {
    `$INSTANCE_NAME``[LCD_SPI]`Init();
}

void `$INSTANCE_NAME`_Enable(void) {
    // Take display out of reset
    `$INSTANCE_NAME``[LCD_Control]`Write(0x01);

    // Enable the SPI interface
    `$INSTANCE_NAME``[LCD_SPI]`Enable();

    // Default display settings
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_SET_START_LINE | 0);
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_ADC_SELECT | 1); // ADC reverse
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_COMMON_SELECT | 0); // Normal COM0-COM63
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_DISPLAY_REVERSE | 0); // Normal
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_SET_BIAS | 0); // 1/9 bias
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_POWER_CONTROL | 0x7); // Booster, regulator, follower on
    `$INSTANCE_NAME`_SendLongCommand(`$INSTANCE_NAME`_SET_BOOSTER_RATIO | 0x4); // 4x booster
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_V0_REGULATOR_RATIO | 0x7); // Regulator resistor ratio
    `$INSTANCE_NAME`_SendLongCommand(`$INSTANCE_NAME`_SET_VOLUME | 0x16); // Set contrast
    `$INSTANCE_NAME`_SendLongCommand(`$INSTANCE_NAME`_SET_STATIC_INDICATOR | 0); // No indicator
    `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_POWER | 1); // Power on.
}

void `$INSTANCE_NAME`_SendCommand(uint8 command) {
    set_state(STATE_COMMAND);
    `$INSTANCE_NAME``[LCD_SPI]`WriteTxData(command);
}

void `$INSTANCE_NAME`_SendLongCommand(uint16 command) {
    set_state(STATE_COMMAND);
    `$INSTANCE_NAME``[LCD_SPI]`WriteTxData((uint8)(command >> 8));
    `$INSTANCE_NAME``[LCD_SPI]`WriteTxData((uint8)(command & 0xff));
}

void _PutChar(char c) {
    uint8 i;
    
    if(column + 6 >= `$INSTANCE_NAME`_VISIBLE_COLUMNS) {
        column = 0;
        page = (page + 1) % (`$INSTANCE_NAME`_ROWS / 8);
    }
    
    // Draw the letter
    for(i = 0; i < 5; i++) {
        current_buffer->data[page * `$INSTANCE_NAME`_COLUMNS + column] = glcd_font[c * 5 + i];
        column++;
    }
    
    // Empty column between letters
    current_buffer->data[page * `$INSTANCE_NAME`_COLUMNS + column] = 0;
    column++;
}

`$INSTANCE_NAME`_buffer* `$INSTANCE_NAME`_Update(`$INSTANCE_NAME`_buffer *new_buffer, uint8 start_page, uint8 end_page) {
    `$INSTANCE_NAME`_buffer *ret = current_buffer;
    int i, j;

    current_buffer = new_buffer;
    
    for(i = start_page; i < end_page; i++) {
        // Set page and column
        `$INSTANCE_NAME`_SendCommand(`$INSTANCE_NAME`_SET_PAGE | (start_page & 0xF));
        `$INSTANCE_NAME`_SendLongCommand(`$INSTANCE_NAME`_SET_COLUMN | 0);

        // Switch to data mode
        set_state(STATE_DATA);
        
        // Send the page of data
        for(j = 0; j < `$INSTANCE_NAME`_COLUMNS; j++)
            `$INSTANCE_NAME``[LCD_SPI]`WriteTxData(current_buffer->data[page * `$INSTANCE_NAME`_COLUMNS + j]);
    }
    
    return ret;
}

int `$INSTANCE_NAME`_Busy(void) {
    return !(`$INSTANCE_NAME``[LCD_SPI]`ReadTxStatus() & (`$INSTANCE_NAME``[LCD_SPI]`STS_SPI_DONE | `$INSTANCE_NAME``[LCD_SPI]`STS_SPI_IDLE));
}

void `$INSTANCE_NAME`_PrintString(char *s) {
    char *c;
    
    for(c = s; *c != '\0'; c++)
        _PutChar(*c);
    
    `$INSTANCE_NAME`_Update(current_buffer, 0, 8);
}

void `$INSTANCE_NAME`_PutChar(char c) {
    _PutChar(c);
    `$INSTANCE_NAME`_Update(current_buffer, 0, 8);
}

void `$INSTANCE_NAME`_Position(uint8 r, uint8 c) {
    page = r;
    column = c;
}

void `$INSTANCE_NAME`_ClearDisplay() {
    memset(current_buffer->data, 0, sizeof(`$INSTANCE_NAME`_buffer));
    `$INSTANCE_NAME`_Update(current_buffer, 0, 8);
}

/* [] END OF FILE */
