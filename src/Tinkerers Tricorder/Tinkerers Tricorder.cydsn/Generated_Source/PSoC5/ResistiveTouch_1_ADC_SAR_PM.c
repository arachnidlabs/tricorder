/*******************************************************************************
* File Name: ResistiveTouch_1_ADC_SAR_PM.c
* Version 2.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ResistiveTouch_1_ADC_SAR.h"


/***************************************
* Local data allocation
***************************************/

static ResistiveTouch_1_ADC_SAR_BACKUP_STRUCT  ResistiveTouch_1_ADC_SAR_backup =
{
    ResistiveTouch_1_ADC_SAR_DISABLED
};


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_backup - modified.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Sleep(void)
{
    if((ResistiveTouch_1_ADC_SAR_PWRMGR_SAR_REG  & ResistiveTouch_1_ADC_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG & ResistiveTouch_1_ADC_SAR_SAR_SOF_START_CONV) != 0u)
        {
            ResistiveTouch_1_ADC_SAR_backup.enableState = ResistiveTouch_1_ADC_SAR_ENABLED | ResistiveTouch_1_ADC_SAR_STARTED;
        }
        else
        {
            ResistiveTouch_1_ADC_SAR_backup.enableState = ResistiveTouch_1_ADC_SAR_ENABLED;
        }
        ResistiveTouch_1_ADC_SAR_Stop();
    }
    else
    {
        ResistiveTouch_1_ADC_SAR_backup.enableState = ResistiveTouch_1_ADC_SAR_DISABLED;
    }
    /*ResistiveTouch_1_ADC_SAR_SaveConfig();*/
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_backup - used.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Wakeup(void)
{
    /*ResistiveTouch_1_ADC_SAR_RestoreConfig();*/
    if(ResistiveTouch_1_ADC_SAR_backup.enableState != ResistiveTouch_1_ADC_SAR_DISABLED)
    {
        ResistiveTouch_1_ADC_SAR_Enable();
        #if(ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__HARDWARE_TRIGGER)
            if((ResistiveTouch_1_ADC_SAR_backup.enableState & ResistiveTouch_1_ADC_SAR_STARTED) != 0u)
            {
                ResistiveTouch_1_ADC_SAR_StartConvert();
            }
        #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__HARDWARE_TRIGGER */
        
    }
}


/* [] END OF FILE */
