/*******************************************************************************
* File Name: BoostConv.c
* Version 4.0
*
* Description:
*  This file provides the source code to the API for the Boost Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BoostConv.h"

uint8 BoostConv_initVar = 0u;
static BoostConv_BACKUP_STRUCT BoostConv_backup = {BoostConv_INIT_VOUT,
                                                                 BoostConv_BOOSTMODE_ACTIVE};


/*******************************************************************************
* Function Name: BoostConv_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default BoostConv configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_Init(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    #if (CY_PSOC3)
        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_CONTROL_REG1;
        tmp = BoostConv_CONTROL_REG1;
        /* Enables mode control from xmode[1:0] instead of control register 1 */
        BoostConv_CONTROL_REG1 = tmp | BoostConv_PWMEXT_ENABLE;
    #endif /* CY_PSOC3 */

    (void) BoostConv_CONTROL_REG2;
    tmp = BoostConv_CONTROL_REG2;

    #if (0u != BoostConv_DISABLE_AUTO_BATTERY)
        BoostConv_CONTROL_REG2 = tmp | BoostConv_AUTO_BATTERY_DISABLE;
    #else
        BoostConv_CONTROL_REG2 = tmp & ((uint8) (~BoostConv_AUTO_BATTERY_DISABLE));
    #endif /* (0u != BoostConv_DISABLE_AUTO_BATTERY) */

    CyExitCriticalSection(enableInterrupts);

    #if (CY_PSOC3)
        BoostConv_SelExtClk(BoostConv_EXTCLK_SRC);
        BoostConv_SelFreq(BoostConv_FREQUENCY);
    #else /* CY_PSOC5LP */
        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_CONTROL_REG1;
        tmp = BoostConv_CONTROL_REG1;

        BoostConv_CONTROL_REG1 = (tmp & ((uint8) (~BoostConv_FREQ_MASK))) |
                                                         BoostConv__SWITCH_FREQ_400KHZ;
    #endif /* CY_PSOC3 */


    BoostConv_SelVoltage(BoostConv_INIT_VOUT);
    BoostConv_SetMode(BoostConv_BOOSTMODE_ACTIVE);
}


/*******************************************************************************
* Function Name: BoostConv_Start
********************************************************************************
*
* Summary:
*  Starts the BoostConv component and puts the boost block into Active
*  mode. The component is in this state when the chip powers up. This is the
*  preferred method to begin component operation. BoostConv_Start()
*  sets the initVar variable, calls the BoostConv_Init() function, and
*  then calls the BoostConv_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  BoostConv_initVar - used to check initial configuration, modified on
*  first function call.
*
* Side Effect:
*  If the initVar variable is already set, this function: 1) sets init value
*  of target output voltage (from customizer) and mode (Active mode) or
*  restores target output voltage and mode saved by BoostConv_Stop()
*  function; 2) calls the BoostConv_Enable() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BoostConv_Start(void) 
{
    uint16 timeout = BoostConv_STARTUP_TIMEOUT;
    uint8 tmp;

    do
    {
        CyDelayUs(1u);
        tmp = BoostConv_ReadStatus();
        timeout--;

    } while ((0u != timeout) && (BoostConv_RDY != (tmp & BoostConv_RDY)));

    tmp = BoostConv_ReadStatus();

    if (BoostConv_RDY == (tmp & BoostConv_RDY))
    {
        if (0u == BoostConv_initVar)
        {
            BoostConv_Init();
            BoostConv_initVar = 1u;
        }
        else
        {
            BoostConv_SelVoltage(BoostConv_backup.selVoltage);
            BoostConv_SetMode(BoostConv_backup.mode);
        }

        BoostConv_Enable();
    }
    else
    {
        /* Boost internal circuits have not been initialized.
         * Halt CPU in debug mode.
         */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: BoostConv_Stop
********************************************************************************
*
* Summary:
*  Saves boost converter target output voltage and mode. Disables
*  the BoostConv component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effect:
* Turns off power to the boost converter circuitry. For PSoC 3 sets the boost
* converter to Standby mode, for PSoC 5LP to Sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BoostConv_Stop(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG0;
    tmp = BoostConv_CONTROL_REG0;

    BoostConv_backup.mode = (tmp & BoostConv_MODE_MASK) >> BoostConv_MODE_SHIFT;
    BoostConv_backup.selVoltage = tmp & BoostConv_VOLTAGE_MASK;

    CyExitCriticalSection(enableInterrupts);

    BoostConv_SelVoltage(BoostConv_VOUT_OFF);
    #if (CY_PSOC3)
        BoostConv_SetMode(BoostConv_BOOSTMODE_STANDBY);
    #endif /* CY_PSOC3 */
    #if (CY_PSOC5LP)
        BoostConv_SetMode(BoostConv_BOOSTMODE_SLEEP);
    #endif /* CY_PSOC5LP */
    BoostConv_Disable();
}


/*******************************************************************************
* Function Name: BoostConv_Enable
********************************************************************************
*
* Summary:
*  This function enables the boost only when it is in Active mode. By default
*  this is enabled.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_Enable(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG1;
    tmp = BoostConv_CONTROL_REG1;

    BoostConv_CONTROL_REG1 = tmp | BoostConv_BOOST_ENABLE;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_Disable
********************************************************************************
*
* Summary:
*  This function disables the boost.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_Disable(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG1;
    tmp = BoostConv_CONTROL_REG1;

    BoostConv_CONTROL_REG1 = tmp & ((uint8) (~BoostConv_BOOST_ENABLE));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_SetMode
********************************************************************************
*
* Summary:
*  This function sets the mode of the Boost: Active, and Standby for PSoC 3 or
*  Sleep for PSoC 5LP.
*
* Parameters:
*  mode: Mode of operation.
*
* Return:
*  None.
*
* Side Effect:
*  PSoC 3:
*   1) For Standby mode, this function enables automatic thump mode
*   and sets the switching frequency clock source to the 32-kHz external clock.
*   2) For Active mode this function disables automatic thump mode.
*
*******************************************************************************/
void BoostConv_SetMode(uint8 mode) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    #if (CY_PSOC3)
        if (0u == mode)
        {
            /* Parameter value is incompatible with PSoC 3 device.
             * Halt CPU in debug mode.
             */
            CYASSERT(0u != 0u);
        }
    #endif /* CY_PSOC3 */
    #if (CY_PSOC5LP)
        if (1u == mode)
        {
            /* Parameter value is incompatible with PSoC 5LP device.
             * Halt CPU in debug mode.
             */
            CYASSERT(0u != 0u);
        }
    #endif /* CY_PSOC5LP */

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG0;
    tmp = BoostConv_CONTROL_REG0;

    BoostConv_CONTROL_REG0 = (tmp & ((uint8) (~BoostConv_MODE_MASK))) |
                                    (BoostConv_MODE_MASK & ((uint8) (mode << BoostConv_MODE_SHIFT)));

    CyExitCriticalSection(enableInterrupts);

    #if (CY_PSOC3)
        if (mode == BoostConv_BOOSTMODE_STANDBY)
        {
           BoostConv_SelFreq(BoostConv__SWITCH_FREQ_32KHZ);
           BoostConv_EnableAutoThump();
        }
        else /* mode == BoostConv_BOOSTMODE_ACTIVE */
        {
            BoostConv_DisableAutoThump();
        }
    #endif /* CY_PSOC3 */
}


/*******************************************************************************
* Function Name: BoostConv_SelVoltage
********************************************************************************
*
* Summary:
*  This function selects the target output voltage the boost converter will
*  maintain.
*
* Parameters:
*  voltage: Desired output voltage.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_SelVoltage(uint8 voltage) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG0;
    tmp = BoostConv_CONTROL_REG0;

    BoostConv_CONTROL_REG0 = (tmp & ((uint8) (~BoostConv_VOLTAGE_MASK))) |
                                            (BoostConv_VOLTAGE_MASK & voltage);

    CyExitCriticalSection(enableInterrupts);
}


#if (CY_PSOC3)

    /*******************************************************************************
    * Function Name: BoostConv_SelFreq
    ********************************************************************************
    *
    * Summary:
    *  This function sets the frequency to one of the 2 possible values:
    *  400kHz (which is generated internal to the Boost Converter block with a
    *  dedicated oscillator) or 32kHz (which comes from the chips ECO-32kHz or
    *  ILO-32kHz). The 32kHz frequency is only applicable for PSoC 3.
    *
    * Parameters:
    *  frequency: Desired switching frequency.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_SelFreq(uint8 frequency) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_CONTROL_REG1;
        tmp = BoostConv_CONTROL_REG1;

        BoostConv_CONTROL_REG1 = (tmp & ((uint8) (~BoostConv_FREQ_MASK))) |
                                                (BoostConv_FREQ_MASK & frequency);

        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: BoostConv_SelExtClk
    ********************************************************************************
    *
    * Summary:
    *  This function sets the source of 32kHz frequency: the chips ECO-32kHz
    *  or ILO-32kHz.
    *
    * Parameters:
    *  source: source of 32kHz frequency.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void  BoostConv_SelExtClk(uint8 source) 
    {
        BoostConv_CONTROL_REG4 = (BoostConv_CONTROL_REG4 & ((uint8) (~BoostConv_EXTCLK_SRC_MASK)))
                                        | (BoostConv_EXTCLK_SRC_MASK &
                                        ((uint8) (source << BoostConv_EXTCLK_SRC_SHIFT)));
    }


    /*******************************************************************************
    * Function Name: BoostConv_EnableAutoThump
    ********************************************************************************
    *
    * Summary:
    *  This function enables automatic thump mode (only available when Boost is
    *  in Standby mode)
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_EnableAutoThump(void) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_CONTROL_REG2;
        tmp = BoostConv_CONTROL_REG2;

        BoostConv_CONTROL_REG2 = tmp | BoostConv_AUTO_THUMP_ENABLE;

        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: BoostConv_DisableAutoThump
    ********************************************************************************
    *
    * Summary:
    *  This function disables automatic thump mode (only available when Boost is
    *  in Standby mode)
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_DisableAutoThump(void) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_CONTROL_REG2;
        tmp = BoostConv_CONTROL_REG2;

        BoostConv_CONTROL_REG2 = tmp & ((uint8) (~BoostConv_AUTO_THUMP_ENABLE));

        CyExitCriticalSection(enableInterrupts);
    }

#endif /* CY_PSOC3 */


/*******************************************************************************
* Function Name: BoostConv_ManualThump
********************************************************************************
*
* Summary:
*  This function forces a single pulse of the boost converter switch
*  transistors.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Thump - produces one ~500ns pulse when set. Must be reset to 0 before another
*  pulse can be generated. It should not re-set the bit until after the 500ns
*  pulse has expired. Used for discrete switch control.
*
* Side Effects:
*  This routine writes a "0" followed by a "1" to the bit 7 "thump" bit in the
*  boost block BOOST_CR0 register.
*
*******************************************************************************/
void BoostConv_ManualThump(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation  and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_CONTROL_REG0;
    tmp = BoostConv_CONTROL_REG0;

    BoostConv_CONTROL_REG0 = tmp | BoostConv_MANUAL_THUMP_ENABLE;
    CyDelayUs(1u);
    BoostConv_CONTROL_REG0 = tmp & ((uint8) (~BoostConv_MANUAL_THUMP_ENABLE));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_ReadStatus
********************************************************************************
*
* Summary:
*  This function returns the contents of the boost block status register.
*
* Parameters:
*  None.
*
* Return:
*  Boost block status register.
*
*******************************************************************************/
uint8 BoostConv_ReadStatus(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_STATUS_REG;
    tmp = BoostConv_STATUS_REG;

    CyExitCriticalSection(enableInterrupts);

    return (tmp);
}


/*******************************************************************************
* Function Name: BoostConv_EnableInt
********************************************************************************
*
* Summary:
*  This function enables the Boost block Output Under-Voltage interrupt
*  generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void  BoostConv_EnableInt(void) 
{
    BoostConv_CONTROL_REG4 |= BoostConv_INT_ENABLE_MASK;
}


/*******************************************************************************
* Function Name: BoostConv_DisableInt
********************************************************************************
*
* Summary:
*  This function disables the Boost block Output Under-Voltage interrupt
*  generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void  BoostConv_DisableInt(void) 
{
    BoostConv_CONTROL_REG4 &= (uint8) (~BoostConv_INT_ENABLE_MASK);
}


/*******************************************************************************
* Function Name: BoostConv_ReadIntStatus
********************************************************************************
*
* Summary:
*  This function returns the contents of the boost block interrupt status
*  register.
*
* Parameters:
*  None.
*
* Return:
*  Boost interrupt status register.
*
*******************************************************************************/
uint8 BoostConv_ReadIntStatus(void) 
{
    return (BoostConv_STATUS_REG2 & BoostConv_INT_ENABLE_MASK);
}


/* [] END OF FILE */
