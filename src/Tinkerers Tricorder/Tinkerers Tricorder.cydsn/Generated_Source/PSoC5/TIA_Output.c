/*******************************************************************************
* File Name: TIA_Output.c  
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
#include "TIA_Output.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TIA_Output__PORT == 15 && ((TIA_Output__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TIA_Output_Write
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
void TIA_Output_Write(uint8 value) 
{
    uint8 staticBits = (TIA_Output_DR & (uint8)(~TIA_Output_MASK));
    TIA_Output_DR = staticBits | ((uint8)(value << TIA_Output_SHIFT) & TIA_Output_MASK);
}


/*******************************************************************************
* Function Name: TIA_Output_SetDriveMode
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
void TIA_Output_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TIA_Output_0, mode);
}


/*******************************************************************************
* Function Name: TIA_Output_Read
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
*  Macro TIA_Output_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TIA_Output_Read(void) 
{
    return (TIA_Output_PS & TIA_Output_MASK) >> TIA_Output_SHIFT;
}


/*******************************************************************************
* Function Name: TIA_Output_ReadDataReg
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
uint8 TIA_Output_ReadDataReg(void) 
{
    return (TIA_Output_DR & TIA_Output_MASK) >> TIA_Output_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TIA_Output_INTSTAT) 

    /*******************************************************************************
    * Function Name: TIA_Output_ClearInterrupt
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
    uint8 TIA_Output_ClearInterrupt(void) 
    {
        return (TIA_Output_INTSTAT & TIA_Output_MASK) >> TIA_Output_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
