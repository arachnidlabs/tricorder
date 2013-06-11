/*******************************************************************************
* File Name: lcd_reset.c  
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
#include "lcd_reset.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 lcd_reset__PORT == 15 && ((lcd_reset__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: lcd_reset_Write
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
void lcd_reset_Write(uint8 value) 
{
    uint8 staticBits = (lcd_reset_DR & (uint8)(~lcd_reset_MASK));
    lcd_reset_DR = staticBits | ((uint8)(value << lcd_reset_SHIFT) & lcd_reset_MASK);
}


/*******************************************************************************
* Function Name: lcd_reset_SetDriveMode
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
void lcd_reset_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(lcd_reset_0, mode);
}


/*******************************************************************************
* Function Name: lcd_reset_Read
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
*  Macro lcd_reset_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 lcd_reset_Read(void) 
{
    return (lcd_reset_PS & lcd_reset_MASK) >> lcd_reset_SHIFT;
}


/*******************************************************************************
* Function Name: lcd_reset_ReadDataReg
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
uint8 lcd_reset_ReadDataReg(void) 
{
    return (lcd_reset_DR & lcd_reset_MASK) >> lcd_reset_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(lcd_reset_INTSTAT) 

    /*******************************************************************************
    * Function Name: lcd_reset_ClearInterrupt
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
    uint8 lcd_reset_ClearInterrupt(void) 
    {
        return (lcd_reset_INTSTAT & lcd_reset_MASK) >> lcd_reset_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
