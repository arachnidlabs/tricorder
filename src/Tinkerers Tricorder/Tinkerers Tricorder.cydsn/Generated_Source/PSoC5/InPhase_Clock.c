/*******************************************************************************
* File Name: InPhase_Clock.c  
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
#include "InPhase_Clock.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 InPhase_Clock__PORT == 15 && ((InPhase_Clock__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: InPhase_Clock_Write
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
void InPhase_Clock_Write(uint8 value) 
{
    uint8 staticBits = (InPhase_Clock_DR & (uint8)(~InPhase_Clock_MASK));
    InPhase_Clock_DR = staticBits | ((uint8)(value << InPhase_Clock_SHIFT) & InPhase_Clock_MASK);
}


/*******************************************************************************
* Function Name: InPhase_Clock_SetDriveMode
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
void InPhase_Clock_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(InPhase_Clock_0, mode);
}


/*******************************************************************************
* Function Name: InPhase_Clock_Read
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
*  Macro InPhase_Clock_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 InPhase_Clock_Read(void) 
{
    return (InPhase_Clock_PS & InPhase_Clock_MASK) >> InPhase_Clock_SHIFT;
}


/*******************************************************************************
* Function Name: InPhase_Clock_ReadDataReg
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
uint8 InPhase_Clock_ReadDataReg(void) 
{
    return (InPhase_Clock_DR & InPhase_Clock_MASK) >> InPhase_Clock_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(InPhase_Clock_INTSTAT) 

    /*******************************************************************************
    * Function Name: InPhase_Clock_ClearInterrupt
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
    uint8 InPhase_Clock_ClearInterrupt(void) 
    {
        return (InPhase_Clock_INTSTAT & InPhase_Clock_MASK) >> InPhase_Clock_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
