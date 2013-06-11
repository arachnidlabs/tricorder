/*******************************************************************************
* File Name: IDrive.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the 8-bit Current 
*  DAC (IDAC8) User Module.
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

#include "cytypes.h"
#include "IDrive.h"   

#if (CY_PSOC5A)
    #include <CyLib.h>
#endif /* CY_PSOC5A */


uint8 IDrive_initVar = 0u;


#if (CY_PSOC5A)
    static IDrive_LOWPOWER_BACKUP_STRUCT  IDrive_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore control register in Enable()
   API. This valid only for PSoC5A */
#if (CY_PSOC5A)
    static uint8 IDrive_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: IDrive_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_Init(void) 
{
    IDrive_CR0 = (IDrive_MODE_I | IDrive_DEFAULT_RANGE );

    /* Set default data source */
    #if(IDrive_DEFAULT_DATA_SRC != 0u )    
        IDrive_CR1 = (IDrive_DEFAULT_CNTL | IDrive_DACBUS_ENABLE);
    #else
        IDrive_CR1 = (IDrive_DEFAULT_CNTL | IDrive_DACBUS_DISABLE);
    #endif /* (IDrive_DEFAULT_DATA_SRC != 0u ) */
    
    /*Controls polarity from UDB Control*/
    #if(IDrive_DEFAULT_POLARITY == IDrive_HARDWARE_CONTROLLED)
        IDrive_CR1 |= IDrive_IDIR_SRC_UDB;
    #else
        IDrive_CR1 |= IDrive_DEFAULT_POLARITY;
    #endif/* (IDrive_DEFAULT_POLARITY == IDrive_HARDWARE_CONTROLLED) */
    /*Controls Current Source from UDB Control*/
    #if(IDrive_HARDWARE_ENABLE != 0u ) 
        IDrive_CR1 |= IDrive_IDIR_CTL_UDB;
    #endif /* (IDrive_HARDWARE_ENABLE != 0u ) */ 
    
    /* Set default strobe mode */
    #if(IDrive_DEFAULT_STRB != 0u)
        IDrive_Strobe |= IDrive_STRB_EN;
    #endif /* (IDrive_DEFAULT_STRB != 0u) */
    
    /* Set default speed */
    IDrive_SetSpeed(IDrive_DEFAULT_SPEED);
    
    /* Set proper DAC trim */
    IDrive_DacTrim();
    
}


/*******************************************************************************
* Function Name: IDrive_Enable
********************************************************************************
* Summary:
*  Enable the IDAC8
* 
* Parameters:
*  void:
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_Enable(void) 
{
    IDrive_PWRMGR |= IDrive_ACT_PWR_EN;
    IDrive_STBY_PWRMGR |= IDrive_STBY_PWR_EN;

    /* This is to restore the value of register CR0 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(IDrive_restoreReg == 1u)
        {
            IDrive_CR0 = IDrive_lowPowerBackup.DACCR0Reg;

            /* Clear the flag */
            IDrive_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: IDrive_Start
********************************************************************************
* Summary:
*  Set power level then turn on IDAC8.
*
* Parameters:  
*  power: Sets power level between off (0) and (3) high power
*
* Return:
*  (void)
*
* Global variables:
*  IDrive_initVar: Is modified when this function is called for 
*   the first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void IDrive_Start(void) 
{
    /* Hardware initiazation only needs to occur the first time */
    if ( IDrive_initVar == 0u)  
    {
        IDrive_Init();
        
        IDrive_initVar = 1u;
    }
   
    /* Enable power to DAC */
    IDrive_Enable();

    /* Set default value */
    IDrive_SetValue(IDrive_DEFAULT_DATA);

}


/*******************************************************************************
* Function Name: IDrive_Stop
********************************************************************************
* Summary:
*  Powers down IDAC8 to lowest power state.
*
* Parameters:
*  (void)
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_Stop(void) 
{
    /* Disble power to DAC */
    IDrive_PWRMGR &= (uint8)(~IDrive_ACT_PWR_EN);
    IDrive_STBY_PWRMGR &= (uint8)(~IDrive_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
    
        /* Set the global variable  */
        IDrive_restoreReg = 1u;

        /* Save the control register and then Clear it. */
        IDrive_lowPowerBackup.DACCR0Reg = IDrive_CR0;
        IDrive_CR0 = (IDrive_MODE_I | IDrive_RANGE_3 | IDrive_HS_HIGHSPEED);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: IDrive_SetSpeed
********************************************************************************
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    IDrive_CR0 &= (uint8)(~IDrive_HS_MASK);
    IDrive_CR0 |=  ( speed & IDrive_HS_MASK);
}


/*******************************************************************************
* Function Name: IDrive_SetPolarity
********************************************************************************
* Summary:
*  Sets IDAC to Sink or Source current.
*  
* Parameters:
*  Polarity: Sets the IDAC to Sink or Source 
*  0x00 - Source
*  0x04 - Sink
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
#if(IDrive_DEFAULT_POLARITY != IDrive_HARDWARE_CONTROLLED)
    void IDrive_SetPolarity(uint8 polarity) 
    {
        IDrive_CR1 &= (uint8)(~IDrive_IDIR_MASK);                /* clear polarity bit */
        IDrive_CR1 |= (polarity & IDrive_IDIR_MASK);             /* set new value */
    
        IDrive_DacTrim();
    }
#endif/*(IDrive_DEFAULT_POLARITY != IDrive_HARDWARE_CONTROLLED)*/


/*******************************************************************************
* Function Name: IDrive_SetRange
********************************************************************************
* Summary:
*  Set current range
*
* Parameters:
*  Range: Sets on of four valid ranges.
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_SetRange(uint8 range) 
{
    IDrive_CR0 &= (uint8)(~IDrive_RANGE_MASK);       /* Clear existing mode */
    IDrive_CR0 |= ( range & IDrive_RANGE_MASK );     /*  Set Range  */
    IDrive_DacTrim();
}


/*******************************************************************************
* Function Name: IDrive_SetValue
********************************************************************************
* Summary:
*  Set DAC value
*
* Parameters:
*  value: Sets DAC value between 0 and 255.
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void IDrive_SetValue(uint8 value) 
{

    #if (CY_PSOC5A)
        uint8 IDrive_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    IDrive_Data = value;         /*  Set Value  */
    
    /* PSOC5A silicons require a double write */
    #if (CY_PSOC5A)
        IDrive_Data = value;
        CyExitCriticalSection(IDrive_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: IDrive_DacTrim
********************************************************************************
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  None
*
* Return:
*  (void) 
*
* Theory:
*  Trim values for the IDAC blocks are stored in the "Customer Table" area in 
*  Row 1 of the Hidden Flash.  There are 8 bytes of trim data for each 
*  IDAC block.
*  The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* Side Effects:
*
*******************************************************************************/
void IDrive_DacTrim(void) 
{
    uint8 mode;

    mode = ((IDrive_CR0 & IDrive_RANGE_MASK) >> 1u);
    
    if((IDrive_IDIR_MASK & IDrive_CR1) == IDrive_IDIR_SINK)
    {
        mode++;
    }

    IDrive_TR = CY_GET_XTND_REG8((uint8 *)(IDrive_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
