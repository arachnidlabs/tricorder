/*******************************************************************************
* File Name: TIA_Input.c  
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
#include "TIA_Input.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TIA_Input__PORT == 15 && ((TIA_Input__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TIA_Input_Write
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
void TIA_Input_Write(uint8 value) 
{
    uint8 staticBits = (TIA_Input_DR & (uint8)(~TIA_Input_MASK));
    TIA_Input_DR = staticBits | ((uint8)(value << TIA_Input_SHIFT) & TIA_Input_MASK);
}


/*******************************************************************************
* Function Name: TIA_Input_SetDriveMode
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
void TIA_Input_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TIA_Input_0, mode);
}


/*******************************************************************************
* Function Name: TIA_Input_Read
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
*  Macro TIA_Input_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TIA_Input_Read(void) 
{
    return (TIA_Input_PS & TIA_Input_MASK) >> TIA_Input_SHIFT;
}


/*******************************************************************************
* Function Name: TIA_Input_ReadDataReg
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
uint8 TIA_Input_ReadDataReg(void) 
{
    return (TIA_Input_DR & TIA_Input_MASK) >> TIA_Input_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TIA_Input_INTSTAT) 

    /*******************************************************************************
    * Function Name: TIA_Input_ClearInterrupt
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
    uint8 TIA_Input_ClearInterrupt(void) 
    {
        return (TIA_Input_INTSTAT & TIA_Input_MASK) >> TIA_Input_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
