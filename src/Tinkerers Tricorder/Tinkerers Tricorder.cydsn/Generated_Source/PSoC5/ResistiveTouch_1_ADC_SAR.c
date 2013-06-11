/*******************************************************************************
* File Name: ResistiveTouch_1_ADC_SAR.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "ResistiveTouch_1_ADC_SAR.h"

#if(ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK)
    #include "ResistiveTouch_1_ADC_SAR_theACLK.h"
#endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void ResistiveTouch_1_ADC_SAR_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 ResistiveTouch_1_ADC_SAR_initVar = 0u;
volatile int16 ResistiveTouch_1_ADC_SAR_offset;
volatile int16 ResistiveTouch_1_ADC_SAR_countsPerVolt;   /* Gain compensation */
volatile int16 ResistiveTouch_1_ADC_SAR_shift;


/***************************************
* Local data allocation
***************************************/
#if(CY_PSOC5A)
    static uint8 ResistiveTouch_1_ADC_SAR_resolution;
#endif /* End CY_PSOC5A */


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component and enables the
*  power.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ResistiveTouch_1_ADC_SAR_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  ResistiveTouch_1_ADC_SAR_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of ResistiveTouch_1_ADC_SAR_Start() routine, or the user may call
*  ResistiveTouch_1_ADC_SAR_Init() and ResistiveTouch_1_ADC_SAR_Enable() as done in the
*  ResistiveTouch_1_ADC_SAR_Start() routine.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(ResistiveTouch_1_ADC_SAR_initVar == 0u)
    {
        ResistiveTouch_1_ADC_SAR_Init();
        ResistiveTouch_1_ADC_SAR_initVar = 1u;
    }
    ResistiveTouch_1_ADC_SAR_Enable();
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ResistiveTouch_1_ADC_SAR_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ResistiveTouch_1_ADC_SAR_offset variable is initialized to 0.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK)
        ResistiveTouch_1_ADC_SAR_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK */

    #if(ResistiveTouch_1_ADC_SAR_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(ResistiveTouch_1_ADC_SAR_INTC_NUMBER, ResistiveTouch_1_ADC_SAR_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(ResistiveTouch_1_ADC_SAR_INTC_NUMBER, &ResistiveTouch_1_ADC_SAR_ISR);
    #endif   /* End ResistiveTouch_1_ADC_SAR_IRQ_REMOVE */        

    /* Enable IRQ mode*/
    ResistiveTouch_1_ADC_SAR_SAR_CSR1_REG |= ResistiveTouch_1_ADC_SAR_SAR_IRQ_MASK_EN | ResistiveTouch_1_ADC_SAR_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    ResistiveTouch_1_ADC_SAR_SetResolution(ResistiveTouch_1_ADC_SAR_DEFAULT_RESOLUTION);
    ResistiveTouch_1_ADC_SAR_offset = 0;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    ResistiveTouch_1_ADC_SAR_PWRMGR_SAR_REG |= ResistiveTouch_1_ADC_SAR_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    ResistiveTouch_1_ADC_SAR_STBY_PWRMGR_SAR_REG |= ResistiveTouch_1_ADC_SAR_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK)
        ResistiveTouch_1_ADC_SAR_PWRMGR_CLK_REG |= ResistiveTouch_1_ADC_SAR_ACT_PWR_CLK_EN;
        ResistiveTouch_1_ADC_SAR_STBY_PWRMGR_CLK_REG |= ResistiveTouch_1_ADC_SAR_STBY_PWR_CLK_EN;
    #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = ResistiveTouch_1_ADC_SAR_SAR_CSR3_REG;
    #if(CY_PSOC5A) /* Make sure that full power is applied for VREF buffer */
        tmpReg &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_PWR_CTRL_VREF_DIV_BY4;
    #endif /* CY_PSOC5A */
    tmpReg |= ResistiveTouch_1_ADC_SAR_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__EXT_REF) || \
        (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= ResistiveTouch_1_ADC_SAR_SAR_EN_BUF_VREF_EN;
    #endif /* ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__EXT_REF */
    ResistiveTouch_1_ADC_SAR_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VNEG_VDDA_DIFF)
        #if(ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__EXT_REF)
            ResistiveTouch_1_ADC_SAR_SAR_CSR6_REG = ResistiveTouch_1_ADC_SAR_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            ResistiveTouch_1_ADC_SAR_SAR_CSR6_REG = ResistiveTouch_1_ADC_SAR_VDDA_VREF;           /* S7 */
        #endif /* ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__INT_REF_NOT_BYPASSED)
            ResistiveTouch_1_ADC_SAR_SAR_CSR6_REG = ResistiveTouch_1_ADC_SAR_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            ResistiveTouch_1_ADC_SAR_SAR_CSR6_REG = ResistiveTouch_1_ADC_SAR_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE == ResistiveTouch_1_ADC_SAR__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(ResistiveTouch_1_ADC_SAR_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        ResistiveTouch_1_ADC_SAR_SAR_CSR5_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        ResistiveTouch_1_ADC_SAR_SAR_CSR5_REG |= ResistiveTouch_1_ADC_SAR_SAR_DLY_INC;
    #endif /* ResistiveTouch_1_ADC_SAR_CLOCK_FREQUENCY > (ResistiveTouch_1_ADC_SAR_MAX_FREQUENCY / 2) */

     /* Delay control for comparator latch enable, low delay, (Default for 1MSPS) */
    #if(ResistiveTouch_1_ADC_SAR_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        ResistiveTouch_1_ADC_SAR_SAR_CSR5_REG |= ResistiveTouch_1_ADC_SAR_SAR_DCEN;
    #else /* Delay control for comparator latch enable, high delay (for <500ksps)*/
        ResistiveTouch_1_ADC_SAR_SAR_CSR5_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_DCEN;
    #endif /* ResistiveTouch_1_ADC_SAR_CLOCK_FREQUENCY > (ResistiveTouch_1_ADC_SAR_MAX_FREQUENCY / 2) */

    /* Set default power and other configurations for control register 0 in multiple lines */
    ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG = (uint8)((uint8)ResistiveTouch_1_ADC_SAR_DEFAULT_POWER << ResistiveTouch_1_ADC_SAR_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (ResistiveTouch_1_ADC_SAR_DEFAULT_REFERENCE != ResistiveTouch_1_ADC_SAR__EXT_REF))
        | ResistiveTouch_1_ADC_SAR_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__FREE_RUNNING)      /* If triggered mode */
        | ResistiveTouch_1_ADC_SAR_SAR_MX_SOF_UDB           /* source: UDB */
        | ResistiveTouch_1_ADC_SAR_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    /* Enable clock for SAR ADC*/
    ResistiveTouch_1_ADC_SAR_SAR_CLK_REG |= ResistiveTouch_1_ADC_SAR_SAR_MX_CLK_EN;

    #if(CY_PSOC5A)
        /* Software Reset */
        ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG |= ResistiveTouch_1_ADC_SAR_SAR_RESET_SOFT_ACTIVE;
        CyDelayUs(2u); /* 2us delay is required for the lowest 1Mhz clock connected to SAR */
        ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_RESET_SOFT_ACTIVE;
    #else
        CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */
    #endif /* End CY_PSOC5A */

    #if(ResistiveTouch_1_ADC_SAR_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(ResistiveTouch_1_ADC_SAR_INTC_NUMBER);
    #endif   /* End ResistiveTouch_1_ADC_SAR_IRQ_REMOVE */        

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_Stop
********************************************************************************
*
* Summary:
*  Stops convertion and reduce the power to the minimum.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_SOF_START_CONV;

    #if(CY_PSOC5A)
        /* Leave the SAR block powered and reduce the power to the minimum */
        ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG |= ResistiveTouch_1_ADC_SAR_ICONT_LV_3;
         /* Disconnect Bypass Cap */
        ResistiveTouch_1_ADC_SAR_SAR_CSR6_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_INT_BYPASS_EXT_VREF;
        /* Disable reference buffer and reduce the reference power to the minimum */
        ResistiveTouch_1_ADC_SAR_SAR_CSR3_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_EN_BUF_VREF_EN; /*VCM buffer is absent in PSOC5A*/
        ResistiveTouch_1_ADC_SAR_SAR_CSR3_REG |= ResistiveTouch_1_ADC_SAR_SAR_PWR_CTRL_VREF_DIV_BY4;
    #else
        /* Disable the SAR ADC block in Active Power Mode */
        ResistiveTouch_1_ADC_SAR_PWRMGR_SAR_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_ACT_PWR_SAR_EN;
        /* Disable the SAR ADC in Standby Power Mode */
        ResistiveTouch_1_ADC_SAR_STBY_PWRMGR_SAR_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_STBY_PWR_SAR_EN;
    #endif /* End CY_PSOC5A */

    /* This is only valid if there is an internal clock */
    #if(ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK)
        ResistiveTouch_1_ADC_SAR_PWRMGR_CLK_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_ACT_PWR_CLK_EN;
        ResistiveTouch_1_ADC_SAR_STBY_PWRMGR_CLK_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_STBY_PWR_CLK_EN;
    #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_SetPower
********************************************************************************
*
* Summary:
*  Sets the Power mode.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Half power
*  2 ->    1/3rd power
*  3 ->    Quarter power.
*
* Return:
*  None.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= ResistiveTouch_1_ADC_SAR_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG & (uint8)~ResistiveTouch_1_ADC_SAR_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << ResistiveTouch_1_ADC_SAR_SAR_POWER_SHIFT);
    ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* remember resolution for the GetResult APIs */
    #if(CY_PSOC5A)
        ResistiveTouch_1_ADC_SAR_resolution = resolution;
    #endif /* End CY_PSOC5A */

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_12:
            tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_12BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_10:
            /* Use 12bits for PSoC5 production silicon and shift the
            *  results for lower resolution in GetResult16() API
            */
            #if(CY_PSOC5A)
                tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_12BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_10BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_8:
            #if(CY_PSOC5A)
                tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_12BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            #else
                tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_8BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            #endif /* End CY_PSOC5A */
            break;
        default:
            tmpReg = ResistiveTouch_1_ADC_SAR_SAR_RESOLUTION_12BIT | ResistiveTouch_1_ADC_SAR_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    ResistiveTouch_1_ADC_SAR_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    ResistiveTouch_1_ADC_SAR_CalcGain(resolution);
}


#if(ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: ResistiveTouch_1_ADC_SAR_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Starts ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a 
    *  software version of the SOC. Here every conversion has to be triggered by 
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the 
    *  external pin to the internal SOF generation. Application should not call 
    *  StartConvert if external source used for SOF.
    *******************************************************************************/
    void ResistiveTouch_1_ADC_SAR_StartConvert(void)
    {
        #if(ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__FREE_RUNNING)  /* If software triggered mode */
            ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE */

        /* Start the conversion */
        ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG |= ResistiveTouch_1_ADC_SAR_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: ResistiveTouch_1_ADC_SAR_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Stops ADC conversion using the given mode. The API is available in the 
    *  free running and the software trigger mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *  This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function set a software version of the SOC 
    *  to low level and switch SOF source to hardware SOF input.
    *
    *******************************************************************************/
    void ResistiveTouch_1_ADC_SAR_StopConvert(void)
    {
        /* Stop all conversions */
        ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG &= (uint8)~ResistiveTouch_1_ADC_SAR_SAR_SOF_START_CONV;

        #if(ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            ResistiveTouch_1_ADC_SAR_SAR_CSR0_REG |= ResistiveTouch_1_ADC_SAR_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE */

    }

#endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_CONV_MODE != ResistiveTouch_1_ADC_SAR__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:
*  retMode:  Wait mode,
*   0 if return with answer imediately.
*   1 if wait until conversion is complete, then return.
*
* Return:
*  (uint8)  0 =>  Conversion not complete.
*           1 =>  Conversion complete.
*
*******************************************************************************/
uint8 ResistiveTouch_1_ADC_SAR_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = ResistiveTouch_1_ADC_SAR_SAR_CSR1_REG & ResistiveTouch_1_ADC_SAR_SAR_EOF_1;
    } while ((status != ResistiveTouch_1_ADC_SAR_SAR_EOF_1) && (retMode == ResistiveTouch_1_ADC_SAR_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == ResistiveTouch_1_ADC_SAR_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(ResistiveTouch_1_ADC_SAR_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*  ResistiveTouch_1_ADC_SAR_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  ResistiveTouch_1_ADC_SAR_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int8 ResistiveTouch_1_ADC_SAR_GetResult8( void )
{

    #if(CY_PSOC5A)

        uint16 res;

        res = CY_GET_REG16(ResistiveTouch_1_ADC_SAR_SAR_WRK_PTR);

        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (ResistiveTouch_1_ADC_SAR_resolution)
        {
            case (uint8)ResistiveTouch_1_ADC_SAR__BITS_10:
                res >>= 2u;
                break;
            case (uint8)ResistiveTouch_1_ADC_SAR__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
        return( (int8)((int16)res - ResistiveTouch_1_ADC_SAR_shift) );
    #else
        return( (int8)ResistiveTouch_1_ADC_SAR_SAR_WRK0_REG - (int8)ResistiveTouch_1_ADC_SAR_shift);
    #endif /* End CY_PSOC5A */

}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_GetResult16
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA registers.
*  ResistiveTouch_1_ADC_SAR_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  ADC result. WORD value which has the converted 12bits. In the differential
*  input mode the SAR ADC outputs digitally converted data in binary offset
*  scheme, this function converts the data into 2's compliment form.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_shift - used to convert the ADC counts to the 2's
*  compliment form.
*  ResistiveTouch_1_ADC_SAR_resolution - used to shift the results for lower
*   resolution.
*
*******************************************************************************/
int16 ResistiveTouch_1_ADC_SAR_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(ResistiveTouch_1_ADC_SAR_SAR_WRK_PTR);

    #if(CY_PSOC5A)
        /* Use 12bits for PSoC5 production silicon and shift the results for lower resolution in this API */
        switch (ResistiveTouch_1_ADC_SAR_resolution)
        {
            case (uint8)ResistiveTouch_1_ADC_SAR__BITS_10:
                res >>= 2u;
                break;
            case (uint8)ResistiveTouch_1_ADC_SAR__BITS_8:
                res >>= 4u;
                break;
            default: /* Do not shift for 12 bits */
                break;
        }
    #endif /* End CY_PSOC5A */

    return( (int16)res - ResistiveTouch_1_ADC_SAR_shift );
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:
*  int16: Offset in counts
*
* Return:
*  None.
*
* Global Variables:
*  The ResistiveTouch_1_ADC_SAR_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the ResistiveTouch_1_ADC_SAR_CountsTo_Volts,
*  ResistiveTouch_1_ADC_SAR_CountsTo_mVolts, ResistiveTouch_1_ADC_SAR_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_SetOffset(int16 offset)
{
    ResistiveTouch_1_ADC_SAR_offset = offset;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2's compliment form.
*  ResistiveTouch_1_ADC_SAR_countsPerVolt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void ResistiveTouch_1_ADC_SAR_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
         (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
         (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_12:
            counts = (int32)ResistiveTouch_1_ADC_SAR_SAR_WRK_MAX;
            #if(!((ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC)) )
                diff_zero = ResistiveTouch_1_ADC_SAR_SAR_DIFF_SHIFT;
            #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */
            break;
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_10:
            counts = (int32)(ResistiveTouch_1_ADC_SAR_SAR_WRK_MAX >> 2u);
            #if(!((ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC)) )
                diff_zero = ResistiveTouch_1_ADC_SAR_SAR_DIFF_SHIFT >> 2u;
            #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */
            break;
        case (uint8)ResistiveTouch_1_ADC_SAR__BITS_8:
            counts = (int32)(ResistiveTouch_1_ADC_SAR_SAR_WRK_MAX >> 4u);
            #if(!((ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC)) )
                diff_zero = ResistiveTouch_1_ADC_SAR_SAR_DIFF_SHIFT >> 4u;
            #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
                 (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    counts *= 1000; /* To avoid float point arithmetic*/
    ResistiveTouch_1_ADC_SAR_countsPerVolt = (int16)(counts / ResistiveTouch_1_ADC_SAR_DEFAULT_REF_VOLTAGE_MV / 2);

    #if( (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSS_TO_VREF) || \
         (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDDA) || \
         (ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE == ResistiveTouch_1_ADC_SAR__VSSA_TO_VDAC) )
        ResistiveTouch_1_ADC_SAR_shift = 0;
    #else
        ResistiveTouch_1_ADC_SAR_shift = diff_zero;
    #endif /* End ResistiveTouch_1_ADC_SAR_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:
*  int16  adcGain  counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_countsPerVolt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_SetGain(int16 adcGain)
{
    ResistiveTouch_1_ADC_SAR_countsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int16  Result in mVolts
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_offset variable used.
*  ResistiveTouch_1_ADC_SAR_countsPerVolt variable used.
*
*******************************************************************************/
int16 ResistiveTouch_1_ADC_SAR_CountsTo_mVolts(int16 adcCounts)
{

    int16 mVolts;

    /* Subtract ADC offset */
    adcCounts -= ResistiveTouch_1_ADC_SAR_offset;

    mVolts = (int16)(( (int32)adcCounts * 1000 ) / ResistiveTouch_1_ADC_SAR_countsPerVolt) ;

    return( mVolts );
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to micro Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  int32  Result in micro Volts
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_offset variable used.
*  ResistiveTouch_1_ADC_SAR_countsPerVolt variable used.
*
*******************************************************************************/
int32 ResistiveTouch_1_ADC_SAR_CountsTo_uVolts(int16 adcCounts)
{

    int32 uVolts;

    /* Subtract ADC offset */
    adcCounts -= ResistiveTouch_1_ADC_SAR_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 1 million. It is multiplied on 500000 and later on 2 to
    *  to avoid 32bit arithmetic overflows.
    */
    uVolts = (( (int32)adcCounts * 500000 ) / ResistiveTouch_1_ADC_SAR_countsPerVolt) * 2;

    return( uVolts );
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_CountsTo_Volts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to Volts
*
* Parameters:
*  int16  adcCounts   Reading from ADC.
*
* Return:
*  float  Result in mVolts
*
* Global Variables:
*  ResistiveTouch_1_ADC_SAR_offset variable used.
*  ResistiveTouch_1_ADC_SAR_countsPerVolt variable used.
*
*******************************************************************************/
float32 ResistiveTouch_1_ADC_SAR_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;

    /* Subtract ADC offset */
    adcCounts -= ResistiveTouch_1_ADC_SAR_offset;

    volts = (float32)adcCounts / (float32)ResistiveTouch_1_ADC_SAR_countsPerVolt;

    return( volts );
}


/* [] END OF FILE */
