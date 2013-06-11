/*******************************************************************************
* File Name: Divider_PM.c
* Version 2.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
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
#include "Divider.h"

static Divider_backupStruct Divider_backup;


/*******************************************************************************
* Function Name: Divider_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Divider_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Divider_SaveConfig(void) 
{
    
    #if(!Divider_UsingFixedFunction)
        #if (CY_PSOC5A)
            Divider_backup.PWMUdb = Divider_ReadCounter();
            Divider_backup.PWMPeriod = Divider_ReadPeriod();
            #if (Divider_UseStatus)
                Divider_backup.InterruptMaskValue = Divider_STATUS_MASK;
            #endif /* (Divider_UseStatus) */
            
            #if(Divider_UseOneCompareMode)
                Divider_backup.PWMCompareValue = Divider_ReadCompare();
            #else
                Divider_backup.PWMCompareValue1 = Divider_ReadCompare1();
                Divider_backup.PWMCompareValue2 = Divider_ReadCompare2();
            #endif /* (Divider_UseOneCompareMode) */
            
           #if(Divider_DeadBandUsed)
                Divider_backup.PWMdeadBandValue = Divider_ReadDeadTime();
            #endif /* (Divider_DeadBandUsed) */
          
            #if ( Divider_KillModeMinTime)
                Divider_backup.PWMKillCounterPeriod = Divider_ReadKillTime();
            #endif /* ( Divider_KillModeMinTime) */
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            #if(!Divider_PWMModeIsCenterAligned)
                Divider_backup.PWMPeriod = Divider_ReadPeriod();
            #endif /* (!Divider_PWMModeIsCenterAligned) */
            Divider_backup.PWMUdb = Divider_ReadCounter();
            #if (Divider_UseStatus)
                Divider_backup.InterruptMaskValue = Divider_STATUS_MASK;
            #endif /* (Divider_UseStatus) */
            
            #if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS || \
                Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
                Divider_backup.PWMdeadBandValue = Divider_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(Divider_KillModeMinTime)
                 Divider_backup.PWMKillCounterPeriod = Divider_ReadKillTime();
            #endif /* (Divider_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(Divider_UseControl)
            Divider_backup.PWMControlRegister = Divider_ReadControlRegister();
        #endif /* (Divider_UseControl) */
    #endif  /* (!Divider_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Divider_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Divider_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Divider_RestoreConfig(void) 
{
        #if(!Divider_UsingFixedFunction)
            #if (CY_PSOC5A)
                /* Interrupt State Backup for Critical Region*/
                uint8 Divider_interruptState;
                /* Enter Critical Region*/
                Divider_interruptState = CyEnterCriticalSection();
                #if (Divider_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    Divider_STATUS_AUX_CTRL |= Divider_STATUS_ACTL_INT_EN_MASK;
                    
                    Divider_STATUS_MASK = Divider_backup.InterruptMaskValue;
                #endif /* (Divider_UseStatus) */
                
                #if (Divider_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    Divider_AUX_CONTROLDP0 |= (Divider_AUX_CTRL_FIFO0_CLR);
                #else /* (Divider_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    Divider_AUX_CONTROLDP0 |= (Divider_AUX_CTRL_FIFO0_CLR);
                    Divider_AUX_CONTROLDP1 |= (Divider_AUX_CTRL_FIFO0_CLR);
                #endif /* (Divider_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(Divider_interruptState);
                
                Divider_WriteCounter(Divider_backup.PWMUdb);
                Divider_WritePeriod(Divider_backup.PWMPeriod);
                
                #if(Divider_UseOneCompareMode)
                    Divider_WriteCompare(Divider_backup.PWMCompareValue);
                #else
                    Divider_WriteCompare1(Divider_backup.PWMCompareValue1);
                    Divider_WriteCompare2(Divider_backup.PWMCompareValue2);
                #endif /* (Divider_UseOneCompareMode) */
                
               #if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS || \
                   Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
                    Divider_WriteDeadTime(Divider_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( Divider_KillModeMinTime)
                    Divider_WriteKillTime(Divider_backup.PWMKillCounterPeriod);
                #endif /* ( Divider_KillModeMinTime) */
            #endif /* (CY_PSOC5A) */
            
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if(!Divider_PWMModeIsCenterAligned)
                    Divider_WritePeriod(Divider_backup.PWMPeriod);
                #endif /* (!Divider_PWMModeIsCenterAligned) */
                Divider_WriteCounter(Divider_backup.PWMUdb);
                #if (Divider_UseStatus)
                    Divider_STATUS_MASK = Divider_backup.InterruptMaskValue;
                #endif /* (Divider_UseStatus) */
                
                #if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS || \
                    Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
                    Divider_WriteDeadTime(Divider_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(Divider_KillModeMinTime)
                    Divider_WriteKillTime(Divider_backup.PWMKillCounterPeriod);
                #endif /* (Divider_KillModeMinTime) */
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            
            #if(Divider_UseControl)
                Divider_WriteControlRegister(Divider_backup.PWMControlRegister); 
            #endif /* (Divider_UseControl) */
        #endif  /* (!Divider_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Divider_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Divider_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Divider_Sleep(void) 
{
    #if(Divider_UseControl)
        if(Divider_CTRL_ENABLE == (Divider_CONTROL & Divider_CTRL_ENABLE))
        {
            /*Component is enabled */
            Divider_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Divider_backup.PWMEnableState = 0u;
        }
    #endif /* (Divider_UseControl) */

    /* Stop component */
    Divider_Stop();
    
    /* Save registers configuration */
    Divider_SaveConfig();
}


/*******************************************************************************
* Function Name: Divider_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Divider_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Divider_Wakeup(void) 
{
     /* Restore registers values */
    Divider_RestoreConfig();
    
    if(Divider_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Divider_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
