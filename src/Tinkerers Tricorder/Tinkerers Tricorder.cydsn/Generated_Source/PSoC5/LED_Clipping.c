/*******************************************************************************
* File Name: LED_Clipping.c  
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
#include "LED_Clipping.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LED_Clipping__PORT == 15 && ((LED_Clipping__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LED_Clipping_Write
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
void LED_Clipping_Write(uint8 value) 
{
    uint8 staticBits = (LED_Clipping_DR & (uint8)(~LED_Clipping_MASK));
    LED_Clipping_DR = staticBits | ((uint8)(value << LED_Clipping_SHIFT) & LED_Clipping_MASK);
}


/*******************************************************************************
* Function Name: LED_Clipping_SetDriveMode
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
void LED_Clipping_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LED_Clipping_0, mode);
}


/*******************************************************************************
* Function Name: LED_Clipping_Read
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
*  Macro LED_Clipping_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LED_Clipping_Read(void) 
{
    return (LED_Clipping_PS & LED_Clipping_MASK) >> LED_Clipping_SHIFT;
}


/*******************************************************************************
* Function Name: LED_Clipping_ReadDataReg
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
uint8 LED_Clipping_ReadDataReg(void) 
{
    return (LED_Clipping_DR & LED_Clipping_MASK) >> LED_Clipping_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LED_Clipping_INTSTAT) 

    /*******************************************************************************
    * Function Name: LED_Clipping_ClearInterrupt
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
    uint8 LED_Clipping_ClearInterrupt(void) 
    {
        return (LED_Clipping_INTSTAT & LED_Clipping_MASK) >> LED_Clipping_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
