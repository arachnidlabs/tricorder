/*******************************************************************************
* File Name: Quadrature_Clock.c  
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
#include "Quadrature_Clock.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Quadrature_Clock__PORT == 15 && ((Quadrature_Clock__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Quadrature_Clock_Write
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
void Quadrature_Clock_Write(uint8 value) 
{
    uint8 staticBits = (Quadrature_Clock_DR & (uint8)(~Quadrature_Clock_MASK));
    Quadrature_Clock_DR = staticBits | ((uint8)(value << Quadrature_Clock_SHIFT) & Quadrature_Clock_MASK);
}


/*******************************************************************************
* Function Name: Quadrature_Clock_SetDriveMode
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
void Quadrature_Clock_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Quadrature_Clock_0, mode);
}


/*******************************************************************************
* Function Name: Quadrature_Clock_Read
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
*  Macro Quadrature_Clock_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Quadrature_Clock_Read(void) 
{
    return (Quadrature_Clock_PS & Quadrature_Clock_MASK) >> Quadrature_Clock_SHIFT;
}


/*******************************************************************************
* Function Name: Quadrature_Clock_ReadDataReg
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
uint8 Quadrature_Clock_ReadDataReg(void) 
{
    return (Quadrature_Clock_DR & Quadrature_Clock_MASK) >> Quadrature_Clock_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Quadrature_Clock_INTSTAT) 

    /*******************************************************************************
    * Function Name: Quadrature_Clock_ClearInterrupt
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
    uint8 Quadrature_Clock_ClearInterrupt(void) 
    {
        return (Quadrature_Clock_INTSTAT & Quadrature_Clock_MASK) >> Quadrature_Clock_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
