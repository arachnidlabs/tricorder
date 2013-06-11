/*******************************************************************************
* File Name: Drive_In.c  
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
#include "Drive_In.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Drive_In__PORT == 15 && ((Drive_In__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Drive_In_Write
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
void Drive_In_Write(uint8 value) 
{
    uint8 staticBits = (Drive_In_DR & (uint8)(~Drive_In_MASK));
    Drive_In_DR = staticBits | ((uint8)(value << Drive_In_SHIFT) & Drive_In_MASK);
}


/*******************************************************************************
* Function Name: Drive_In_SetDriveMode
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
void Drive_In_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Drive_In_0, mode);
}


/*******************************************************************************
* Function Name: Drive_In_Read
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
*  Macro Drive_In_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Drive_In_Read(void) 
{
    return (Drive_In_PS & Drive_In_MASK) >> Drive_In_SHIFT;
}


/*******************************************************************************
* Function Name: Drive_In_ReadDataReg
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
uint8 Drive_In_ReadDataReg(void) 
{
    return (Drive_In_DR & Drive_In_MASK) >> Drive_In_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Drive_In_INTSTAT) 

    /*******************************************************************************
    * Function Name: Drive_In_ClearInterrupt
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
    uint8 Drive_In_ClearInterrupt(void) 
    {
        return (Drive_In_INTSTAT & Drive_In_MASK) >> Drive_In_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
