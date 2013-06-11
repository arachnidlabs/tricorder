/*******************************************************************************
* File Name: ResistiveTouch_1.c
* Version 1.20
*
* Description:
*  This file provides the source code of scanning APIs for the Resistive Touch 
*  component.
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

uint8 ResistiveTouch_1_initVar = 0u;
uint8 ResistiveTouch_1_measureVar = 0u;
volatile uint8 ResistiveTouch_1_enableVar = 0u;


/*******************************************************************************
* Function Name: ResistiveTouch_1_Init
********************************************************************************
*
* Summary:
*  Calls the Init functions of the DelSig ADC or SAR ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_Init(void) 
{
    /* Amux component initialization */
    ResistiveTouch_1_AMux_Init();
    
    /* ADC component initialization */
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR)
        ResistiveTouch_1_ADC_SAR_Init();
    #else
        ResistiveTouch_1_ADC_Init();
    #endif  /* (ResistiveTouch_1_SAR_SELECT) */
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Start
********************************************************************************
*
* Summary:
*  Calls ResistiveTouct_Init() and ResistiveTouch_Enable() APIs.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* Global variables:
*  ResistiveTouch_1_initVar - used to indicate enable/disable component state.
*
*******************************************************************************/
void ResistiveTouch_1_Start(void)  
{
    /* Call Init function */
    if(ResistiveTouch_1_initVar == 0u)
    {    
        /* Call Init function */
        ResistiveTouch_1_Init();
        ResistiveTouch_1_initVar = 1u;
    }

    /* Call Enable function */
   ResistiveTouch_1_Enable();
   
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Stop
********************************************************************************
*
* Summary:
*  Stops the DelSig ADC or SAR ADC and stops the AMux component.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* Global variables:
*  ResistiveTouch_1_enableVar - used to check initial configuration, modified on 
*  first function call.
*
*******************************************************************************/
void ResistiveTouch_1_Stop(void)  
{
    /* Stop ADC component */
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR) 
        ResistiveTouch_1_ADC_SAR_Stop();
    
    #else
        ResistiveTouch_1_ADC_Stop();
    
    #endif  /* (ResistiveTouch_1_SAR_SELECT) */
    
    /* Stop AMux component */
    ResistiveTouch_1_AMux_Stop();

    /* Clear variable Enable */
    ResistiveTouch_1_enableVar = 0u;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Enable
********************************************************************************
*
* Summary:
*  Enables the DelSig ADC or SAR ADC and enables the AMux component.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* 
* Global variables:
*  ResistiveTouch_1_initVar - used to indicate enable/disable component state.
*
*******************************************************************************/
void ResistiveTouch_1_Enable(void)  
{
    /* Enable ADC component */
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR) 
        ResistiveTouch_1_ADC_SAR_Enable();

    #else
        ResistiveTouch_1_ADC_Enable();

    #endif  /* (ResistiveTouch_1_SAR_SELECT) */
    
    /* Set variable Enable */
   ResistiveTouch_1_enableVar = 1u;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ActivateX
********************************************************************************
*
* Summary: 
*  Configures the pins for measurement of Y-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_ActivateX(void) 
{
    /* Pins configuration for Y measure */
    CyPins_SetPinDriveMode(ResistiveTouch_1_ym_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_1_yp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_1_xp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_1_xm_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if Channel 0 not selected */
    if(ResistiveTouch_1_AMux_GetChannel() != ResistiveTouch_1_AMUX_XP_CHAN)
    {
        ResistiveTouch_1_AMux_Next();
    }
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ActivateY
********************************************************************************
*
* Summary: 
*  Configures the pins for measurement of X-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_1_ActivateY(void) 
{
    /* Pins configuration for X measure */
    CyPins_SetPinDriveMode(ResistiveTouch_1_xm_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_1_xp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_1_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_1_ym_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if Channel 1 not selected */
    if(ResistiveTouch_1_AMux_GetChannel() == ResistiveTouch_1_AMUX_XP_CHAN)
    {
        ResistiveTouch_1_AMux_Next();
    }
    /* Switch AMux to Channel 1 if disconnected */
    else if(ResistiveTouch_1_AMux_GetChannel() == ResistiveTouch_1_AMUX_NO_CHAN)
    {
        ResistiveTouch_1_AMux_Next();
        ResistiveTouch_1_AMux_Next();
    }
    else
    {
        /* Nothing to do */
    }
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_TouchDetect
********************************************************************************
*
* Summary:
*  Determines if the screen is pressed.
*
* Parameters:
*  None
*
* Return:
*  uint8: the touch state
*  0 - untouched
*  1 - touched
* 
* Global variables:
*  ResistiveTouch_1_measureVar - used to indicate measure function call.
*

*******************************************************************************/
uint8 ResistiveTouch_1_TouchDetect(void) 
{
    uint8 val = 0u;

     /* Pin configuration for touch detect */    
    CyPins_SetPinDriveMode(ResistiveTouch_1_xp_0, PIN_DM_STRONG);

    /* Set delay for signal stabilization */
    CyDelayUs(5u);

    /* Pin configuration for touch detect */
    CyPins_SetPinDriveMode(ResistiveTouch_1_xp_0, PIN_DM_RES_UP);
    
        /* Switch AMux if Channel 0 not selected */
    if(ResistiveTouch_1_AMux_GetChannel() != ResistiveTouch_1_AMUX_XP_CHAN)
    {
        ResistiveTouch_1_AMux_Next();
    }

    /* Pin configuration for touch detect */
    CyPins_SetPinDriveMode(ResistiveTouch_1_xm_0, PIN_DM_ALG_HIZ);

    /* Pin configuration for touch detect */
    CyPins_SetPinDriveMode(ResistiveTouch_1_yp_0, PIN_DM_ALG_HIZ);
    
    /* Pin configuration for touch detect */    
    CyPins_SetPinDriveMode(ResistiveTouch_1_ym_0, PIN_DM_STRONG);

    /* If Measure not happend cofigure pins for TouchDetect */
    if (ResistiveTouch_1_measureVar == 0u)
    {
        /* Set delay for signal stabilization */
        CyDelayUs(20u);
    }
    else
    {
        /* Clear variable Measure */
        ResistiveTouch_1_measureVar = 0u;  
        
        /* Set delay for signal stabilization */
        CyDelayUs(8u);        
    }
   
    /* Set variable val to 1 if touch detected */
    if( ResistiveTouch_1_Measure() <= 0x777u)
    {
        val = 1u; 
    }
    
    return (val);
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_Measure
********************************************************************************
*
* Summary:
*  Returns the result of the A/D converter.
*
* Parameters:
*  None
*
* Return:
*  int16: the result of the ADC conversion.
* 
* Global variables:
*  ResistiveTouch_1_measureVar - used to indicate measure function call.
*
*******************************************************************************/
int16 ResistiveTouch_1_Measure(void) 
{
    int16   ADC_Result;
    
    /* Start ADC convert & get result */
    #if(ResistiveTouch_1_SAR_SELECT == ResistiveTouch_1_SAR) 
        
        ResistiveTouch_1_ADC_SAR_StartConvert();
        ResistiveTouch_1_ADC_SAR_IsEndConversion(ResistiveTouch_1_ADC_SAR_WAIT_FOR_RESULT);

        ADC_Result = ResistiveTouch_1_ADC_SAR_GetResult16();
    
    #else
        /* Start ADC convert & get result */
        ResistiveTouch_1_ADC_StartConvert();
        ResistiveTouch_1_ADC_IsEndConversion(ResistiveTouch_1_ADC_WAIT_FOR_RESULT);
        
        ADC_Result = ResistiveTouch_1_ADC_GetResult16();
    
    #endif  /* (ResistiveTouch_1_SAR_SELECT) */
    
    /* Set variable Measure */
   ResistiveTouch_1_measureVar = 1u;
    
    return (ADC_Result);
}


/* [] END OF FILE */
