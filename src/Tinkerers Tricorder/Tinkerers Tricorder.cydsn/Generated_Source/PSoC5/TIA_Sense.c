/*******************************************************************************
* File Name: TIA_Sense.c  
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
#include "TIA_Sense.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TIA_Sense__PORT == 15 && ((TIA_Sense__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TIA_Sense_Write
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
void TIA_Sense_Write(uint8 value) 
{
    uint8 staticBits = (TIA_Sense_DR & (uint8)(~TIA_Sense_MASK));
    TIA_Sense_DR = staticBits | ((uint8)(value << TIA_Sense_SHIFT) & TIA_Sense_MASK);
}


/*******************************************************************************
* Function Name: TIA_Sense_SetDriveMode
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
void TIA_Sense_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TIA_Sense_0, mode);
}


/*******************************************************************************
* Function Name: TIA_Sense_Read
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
*  Macro TIA_Sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TIA_Sense_Read(void) 
{
    return (TIA_Sense_PS & TIA_Sense_MASK) >> TIA_Sense_SHIFT;
}


/*******************************************************************************
* Function Name: TIA_Sense_ReadDataReg
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
uint8 TIA_Sense_ReadDataReg(void) 
{
    return (TIA_Sense_DR & TIA_Sense_MASK) >> TIA_Sense_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TIA_Sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: TIA_Sense_ClearInterrupt
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
    uint8 TIA_Sense_ClearInterrupt(void) 
    {
        return (TIA_Sense_INTSTAT & TIA_Sense_MASK) >> TIA_Sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
