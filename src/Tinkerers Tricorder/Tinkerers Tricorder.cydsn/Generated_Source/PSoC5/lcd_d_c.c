/*******************************************************************************
* File Name: LCD_D_C.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LCD_D_C.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LCD_D_C__PORT == 15 && ((LCD_D_C__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LCD_D_C_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void LCD_D_C_Write(uint8 value) 
{
    uint8 staticBits = (LCD_D_C_DR & (uint8)(~LCD_D_C_MASK));
    LCD_D_C_DR = staticBits | ((uint8)(value << LCD_D_C_SHIFT) & LCD_D_C_MASK);
}


/*******************************************************************************
* Function Name: LCD_D_C_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void LCD_D_C_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LCD_D_C_0, mode);
}


/*******************************************************************************
* Function Name: LCD_D_C_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro LCD_D_C_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LCD_D_C_Read(void) 
{
    return (LCD_D_C_PS & LCD_D_C_MASK) >> LCD_D_C_SHIFT;
}


/*******************************************************************************
* Function Name: LCD_D_C_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 LCD_D_C_ReadDataReg(void) 
{
    return (LCD_D_C_DR & LCD_D_C_MASK) >> LCD_D_C_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LCD_D_C_INTSTAT) 

    /*******************************************************************************
    * Function Name: LCD_D_C_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 LCD_D_C_ClearInterrupt(void) 
    {
        return (LCD_D_C_INTSTAT & LCD_D_C_MASK) >> LCD_D_C_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
