/*******************************************************************************
* File Name: SOC_Go.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SOC_Go.h"

#if !defined(SOC_Go_Sync_ctrl_reg__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
* Function Name: SOC_Go_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void SOC_Go_Write(uint8 control) 
{
    SOC_Go_Control = control;
}


/*******************************************************************************
* Function Name: SOC_Go_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 SOC_Go_Read(void) 
{
    return SOC_Go_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
