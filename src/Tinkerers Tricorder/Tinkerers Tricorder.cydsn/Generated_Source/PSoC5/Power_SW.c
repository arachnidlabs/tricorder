/*******************************************************************************
* File Name: Power_SW.c  
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
#include "Power_SW.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Power_SW__PORT == 15 && ((Power_SW__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Power_SW_Write
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
void Power_SW_Write(uint8 value) 
{
    uint8 staticBits = (Power_SW_DR & (uint8)(~Power_SW_MASK));
    Power_SW_DR = staticBits | ((uint8)(value << Power_SW_SHIFT) & Power_SW_MASK);
}


/*******************************************************************************
* Function Name: Power_SW_SetDriveMode
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
void Power_SW_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Power_SW_0, mode);
}


/*******************************************************************************
* Function Name: Power_SW_Read
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
*  Macro Power_SW_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Power_SW_Read(void) 
{
    return (Power_SW_PS & Power_SW_MASK) >> Power_SW_SHIFT;
}


/*******************************************************************************
* Function Name: Power_SW_ReadDataReg
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
uint8 Power_SW_ReadDataReg(void) 
{
    return (Power_SW_DR & Power_SW_MASK) >> Power_SW_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Power_SW_INTSTAT) 

    /*******************************************************************************
    * Function Name: Power_SW_ClearInterrupt
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
    uint8 Power_SW_ClearInterrupt(void) 
    {
        return (Power_SW_INTSTAT & Power_SW_MASK) >> Power_SW_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
