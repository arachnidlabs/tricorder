/*******************************************************************************
* File Name: TIA.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TIA.h"

uint8 TIA_initVar = 0u;


/*******************************************************************************   
* Function Name: TIA_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  TIA_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TIA_Init(void) 
{
    TIA_SetPower(TIA_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: TIA_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TIA_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    TIA_PUMP_CR1_REG  |= (TIA_PUMP_CR1_CLKSEL | TIA_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    TIA_PM_ACT_CFG_REG |= TIA_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    TIA_PM_STBY_CFG_REG |= TIA_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   TIA_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIA_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void TIA_Start(void) 
{
    if(TIA_initVar == 0u)
    {
        TIA_initVar = 1u;
        TIA_Init();
    }

    TIA_Enable();
}


/*******************************************************************************
* Function Name: TIA_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TIA_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    TIA_PM_ACT_CFG_REG &= (uint8)(~TIA_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    TIA_PM_STBY_CFG_REG &= (uint8)(~TIA_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(TIA_PM_ACT_CFG_REG == 0u)
    {
        TIA_PUMP_CR1_REG &= (uint8)(~(TIA_PUMP_CR1_CLKSEL | TIA_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: TIA_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void TIA_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        TIA_CR_REG &= (uint8)(~TIA_PWR_MASK);
        TIA_CR_REG |= power & TIA_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(TIA_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
