/*******************************************************************************
* File Name: LCD_1_LCD_Control.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_1_LCD_Control.h"

#if !defined(LCD_1_LCD_Control_Sync_ctrl_reg__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
* Function Name: LCD_1_LCD_Control_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_1_LCD_Control_Write(uint8 control) 
{
    LCD_1_LCD_Control_Control = control;
}


/*******************************************************************************
* Function Name: LCD_1_LCD_Control_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 LCD_1_LCD_Control_Read(void) 
{
    return LCD_1_LCD_Control_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
