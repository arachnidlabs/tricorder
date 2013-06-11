/*******************************************************************************
* File Name: LCD_LCD_SPI_PM.c
* Version 2.40
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_LCD_SPI_PVT.h"

static LCD_LCD_SPI_BACKUP_STRUCT LCD_LCD_SPI_backup =
{
    LCD_LCD_SPI_DISABLED,
    LCD_LCD_SPI_BITCTR_INIT,
    #if(CY_UDB_V0)
        LCD_LCD_SPI_TX_INIT_INTERRUPTS_MASK,
        LCD_LCD_SPI_RX_INIT_INTERRUPTS_MASK
    #endif /* CY_UDB_V0 */
};


/*******************************************************************************
* Function Name: LCD_LCD_SPI_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_LCD_SPI_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_LCD_SPI_SaveConfig(void) 
{
    /* Store Status Mask registers */
    #if(CY_UDB_V0)
       LCD_LCD_SPI_backup.cntrPeriod      = LCD_LCD_SPI_COUNTER_PERIOD_REG;
       LCD_LCD_SPI_backup.saveSrTxIntMask = LCD_LCD_SPI_TX_STATUS_MASK_REG;
       LCD_LCD_SPI_backup.saveSrRxIntMask = LCD_LCD_SPI_RX_STATUS_MASK_REG;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: LCD_LCD_SPI_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_LCD_SPI_backup - used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*  LCD_LCD_SPI_STATUS_MASK_REG and LCD_LCD_SPI_COUNTER_PERIOD_REG.
*
*******************************************************************************/
void LCD_LCD_SPI_RestoreConfig(void) 
{
    /* Restore the data, saved by SaveConfig() function */
    #if(CY_UDB_V0)
        LCD_LCD_SPI_COUNTER_PERIOD_REG = LCD_LCD_SPI_backup.cntrPeriod;
        LCD_LCD_SPI_TX_STATUS_MASK_REG = ((uint8) LCD_LCD_SPI_backup.saveSrTxIntMask);
        LCD_LCD_SPI_RX_STATUS_MASK_REG = ((uint8) LCD_LCD_SPI_backup.saveSrRxIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: LCD_LCD_SPI_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_LCD_SPI_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_LCD_SPI_Sleep(void) 
{
    /* Save components enable state */
    LCD_LCD_SPI_backup.enableState = ((uint8) LCD_LCD_SPI_IS_ENABLED);

    LCD_LCD_SPI_Stop();
    LCD_LCD_SPI_SaveConfig();
}


/*******************************************************************************
* Function Name: LCD_LCD_SPI_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_LCD_SPI_backup - used when non-retention registers are restored.
*  LCD_LCD_SPI_txBufferWrite - modified every function call - resets to
*  zero.
*  LCD_LCD_SPI_txBufferRead - modified every function call - resets to
*  zero.
*  LCD_LCD_SPI_rxBufferWrite - modified every function call - resets to
*  zero.
*  LCD_LCD_SPI_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_LCD_SPI_Wakeup(void) 
{
    LCD_LCD_SPI_RestoreConfig();

    #if(LCD_LCD_SPI_RX_SOFTWARE_BUF_ENABLED)
        LCD_LCD_SPI_rxBufferFull  = 0u;
        LCD_LCD_SPI_rxBufferRead  = 0u;
        LCD_LCD_SPI_rxBufferWrite = 0u;
    #endif /* (LCD_LCD_SPI_RX_SOFTWARE_BUF_ENABLED) */

    #if(LCD_LCD_SPI_TX_SOFTWARE_BUF_ENABLED)
        LCD_LCD_SPI_txBufferFull  = 0u;
        LCD_LCD_SPI_txBufferRead  = 0u;
        LCD_LCD_SPI_txBufferWrite = 0u;
    #endif /* (LCD_LCD_SPI_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    LCD_LCD_SPI_ClearFIFO();

    /* Restore components block enable state */
    if(0u != LCD_LCD_SPI_backup.enableState)
    {
        LCD_LCD_SPI_Enable();
    }
}


/* [] END OF FILE */
