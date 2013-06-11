/*******************************************************************************
* File Name: IDrive.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "IDrive.h"

static IDrive_backupStruct IDrive_backup;


/*******************************************************************************
* Function Name: IDrive_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDrive_SaveConfig(void) 
{
    if (!((IDrive_CR1 & IDrive_SRC_MASK) == IDrive_SRC_UDB))
    {
        IDrive_backup.data_value = IDrive_Data;
    }
}


/*******************************************************************************
* Function Name: IDrive_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDrive_RestoreConfig(void) 
{
    if (!((IDrive_CR1 & IDrive_SRC_MASK) == IDrive_SRC_UDB))
    {
        if((IDrive_Strobe & IDrive_STRB_MASK) == IDrive_STRB_EN)
        {
            IDrive_Strobe &= (uint8)(~IDrive_STRB_MASK);
            IDrive_Data = IDrive_backup.data_value;
            IDrive_Strobe |= IDrive_STRB_EN;
        }
        else
        {
            IDrive_Data = IDrive_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: IDrive_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  IDrive_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IDrive_Sleep(void) 
{
    if(IDrive_ACT_PWR_EN == (IDrive_PWRMGR & IDrive_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        IDrive_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        IDrive_backup.enableState = 0u;
    }

    IDrive_Stop();
    IDrive_SaveConfig();
}


/*******************************************************************************
* Function Name: IDrive_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  IDrive_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IDrive_Wakeup(void) 
{
    IDrive_RestoreConfig();
    
    if(IDrive_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        IDrive_Enable();
        
        /* Set the data register */
        IDrive_SetValue(IDrive_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
