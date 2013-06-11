/*******************************************************************************
* File Name: Button_Mode.c  
* Version 1.80
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
#include "Button_Mode.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Button_Mode__PORT == 15 && ((Button_Mode__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Button_Mode_Write
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
void Button_Mode_Write(uint8 value) 
{
    uint8 staticBits = (Button_Mode_DR & (uint8)(~Button_Mode_MASK));
    Button_Mode_DR = staticBits | ((uint8)(value << Button_Mode_SHIFT) & Button_Mode_MASK);
}


/*******************************************************************************
* Function Name: Button_Mode_SetDriveMode
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
void Button_Mode_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Button_Mode_0, mode);
}


/*******************************************************************************
* Function Name: Button_Mode_Read
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
*  Macro Button_Mode_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Button_Mode_Read(void) 
{
    return (Button_Mode_PS & Button_Mode_MASK) >> Button_Mode_SHIFT;
}


/*******************************************************************************
* Function Name: Button_Mode_ReadDataReg
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
uint8 Button_Mode_ReadDataReg(void) 
{
    return (Button_Mode_DR & Button_Mode_MASK) >> Button_Mode_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Button_Mode_INTSTAT) 

    /*******************************************************************************
    * Function Name: Button_Mode_ClearInterrupt
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
    uint8 Button_Mode_ClearInterrupt(void) 
    {
        return (Button_Mode_INTSTAT & Button_Mode_MASK) >> Button_Mode_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
