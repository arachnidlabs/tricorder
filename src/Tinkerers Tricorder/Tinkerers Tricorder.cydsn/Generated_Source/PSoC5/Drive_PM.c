/*******************************************************************************
* File Name: Drive_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Drive.h"

static Drive_BACKUP_STRUCT  Drive_backup;


/*******************************************************************************  
* Function Name: Drive_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Drive_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Drive_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Drive_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Drive_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Drive_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Drive_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Drive_PM_ACT_CFG_REG & Drive_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Drive_backup.enableState = 1u;
         /* Stops the component */
         Drive_Stop();
    }
    else
    {
        /* Component is disabled */
        Drive_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Drive_SaveConfig();
}


/*******************************************************************************  
* Function Name: Drive_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Drive_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Drive_Wakeup(void) 
{
    /* Restore the user configuration */
    Drive_RestoreConfig();

    /* Enables the component operation */
    if(Drive_backup.enableState == 1u)
    {
        Drive_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
