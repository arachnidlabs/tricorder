/*******************************************************************************
* File Name: tia_range.c  
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
#include "tia_range.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 tia_range__PORT == 15 && ((tia_range__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: tia_range_Write
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
void tia_range_Write(uint8 value) 
{
    uint8 staticBits = (tia_range_DR & (uint8)(~tia_range_MASK));
    tia_range_DR = staticBits | ((uint8)(value << tia_range_SHIFT) & tia_range_MASK);
}


/*******************************************************************************
* Function Name: tia_range_SetDriveMode
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
void tia_range_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(tia_range_0, mode);
}


/*******************************************************************************
* Function Name: tia_range_Read
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
*  Macro tia_range_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 tia_range_Read(void) 
{
    return (tia_range_PS & tia_range_MASK) >> tia_range_SHIFT;
}


/*******************************************************************************
* Function Name: tia_range_ReadDataReg
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
uint8 tia_range_ReadDataReg(void) 
{
    return (tia_range_DR & tia_range_MASK) >> tia_range_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(tia_range_INTSTAT) 

    /*******************************************************************************
    * Function Name: tia_range_ClearInterrupt
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
    uint8 tia_range_ClearInterrupt(void) 
    {
        return (tia_range_INTSTAT & tia_range_MASK) >> tia_range_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
