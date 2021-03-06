/*******************************************************************************
* File Name: Drive_Out_P01.c  
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
#include "Drive_Out_P01.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Drive_Out_P01__PORT == 15 && ((Drive_Out_P01__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Drive_Out_P01_Write
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
void Drive_Out_P01_Write(uint8 value) 
{
    uint8 staticBits = (Drive_Out_P01_DR & (uint8)(~Drive_Out_P01_MASK));
    Drive_Out_P01_DR = staticBits | ((uint8)(value << Drive_Out_P01_SHIFT) & Drive_Out_P01_MASK);
}


/*******************************************************************************
* Function Name: Drive_Out_P01_SetDriveMode
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
void Drive_Out_P01_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Drive_Out_P01_0, mode);
}


/*******************************************************************************
* Function Name: Drive_Out_P01_Read
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
*  Macro Drive_Out_P01_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Drive_Out_P01_Read(void) 
{
    return (Drive_Out_P01_PS & Drive_Out_P01_MASK) >> Drive_Out_P01_SHIFT;
}


/*******************************************************************************
* Function Name: Drive_Out_P01_ReadDataReg
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
uint8 Drive_Out_P01_ReadDataReg(void) 
{
    return (Drive_Out_P01_DR & Drive_Out_P01_MASK) >> Drive_Out_P01_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Drive_Out_P01_INTSTAT) 

    /*******************************************************************************
    * Function Name: Drive_Out_P01_ClearInterrupt
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
    uint8 Drive_Out_P01_ClearInterrupt(void) 
    {
        return (Drive_Out_P01_INTSTAT & Drive_Out_P01_MASK) >> Drive_Out_P01_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
