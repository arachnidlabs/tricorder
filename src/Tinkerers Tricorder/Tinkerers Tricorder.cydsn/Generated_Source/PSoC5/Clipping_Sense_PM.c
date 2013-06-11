/*******************************************************************************
* File Name: Clipping_Sense.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Clipping_Sense.h"

static Clipping_Sense_backupStruct Clipping_Sense_backup;


/*******************************************************************************
* Function Name: Clipping_Sense_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Clipping_Sense_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Clipping_Sense_RestoreConfig
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
********************************************************************************/
void Clipping_Sense_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Clipping_Sense_Sleep
********************************************************************************
*
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
*  Clipping_Sense_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Clipping_Sense_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Clipping_Sense_ACT_PWR_EN == (Clipping_Sense_PWRMGR & Clipping_Sense_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Clipping_Sense_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Clipping_Sense_backup.enableState = 0u;
    }    
    
    Clipping_Sense_Stop();
    Clipping_Sense_SaveConfig();
}


/*******************************************************************************
* Function Name: Clipping_Sense_Wakeup
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
*  Clipping_Sense_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Clipping_Sense_Wakeup(void) 
{
    Clipping_Sense_RestoreConfig();
    
    if(Clipping_Sense_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Clipping_Sense_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
