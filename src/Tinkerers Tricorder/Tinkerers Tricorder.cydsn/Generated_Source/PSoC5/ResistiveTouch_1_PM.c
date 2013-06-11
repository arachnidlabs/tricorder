/*******************************************************************************
* File Name: ResistiveTouch_1_PM.c
* Version 1.20
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ResistiveTouch_1.h"
extern uint8 ResistiveTouch_1_enableVar;

ResistiveTouch_1_BACKUP_STRUCT ResistiveTouch_1_backup =
{
    0x0u, /* enableState */
};


/*******************************************************************************
* Function Name: ResistiveTouch_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the configuration of the DelSig ADC or SAR ADC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_SaveConfig(void) 
{
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR) 
        ResistiveTouch_1_ADC_SAR_SaveConfig();
    #else
        ResistiveTouch_1_ADC_SaveConfig();
    #endif  /* End  (ResistiveTouch_1_SAR_SELECT) */    
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the configuration of the DelSig ADC or SAR ADC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void ResistiveTouch_1_RestoreConfig(void) 
{
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR) 
        ResistiveTouch_1_ADC_SAR_RestoreConfig();
    #else
        ResistiveTouch_1_ADC_RestoreConfig();
    #endif  /* (ResistiveTouch_1_SAR_SELECT) */    
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Sleep
********************************************************************************
*
* Summary:
*  Prepares the DelSig ADC or SAR ADC for low power modes by calling 
*  SaveConfig and Stop functions.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_Sleep(void) 
{
    if(ResistiveTouch_1_enableVar == 1u)       
    {
        ResistiveTouch_1_backup.enableState = 1u;
        ResistiveTouch_1_Stop();
    }
    else /* The ResistiveTouch block is disabled */
    {
        ResistiveTouch_1_backup.enableState = 0u;
    }

    ResistiveTouch_1_SaveConfig();
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the DelSig ADC or SAR ADC after waking up from a low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_Wakeup(void)  
{
    ResistiveTouch_1_RestoreConfig();
    
    if(ResistiveTouch_1_backup.enableState != 0u)
    {
        /* Enable component's operation */
        ResistiveTouch_1_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */
