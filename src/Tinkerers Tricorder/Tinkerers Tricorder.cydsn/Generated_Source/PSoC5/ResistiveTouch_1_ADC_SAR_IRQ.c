/*******************************************************************************
* File Name: ResistiveTouch_1_ADC_SAR_IRQ.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <ResistiveTouch_1_ADC_SAR_IRQ.H>

#if !defined(ResistiveTouch_1_ADC_SAR_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ResistiveTouch_1_ADC_SAR_IRQ_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_Start(void)
{
    /* For all we know the interrupt is active. */
    ResistiveTouch_1_ADC_SAR_IRQ_Disable();

    /* Set the ISR to point to the ResistiveTouch_1_ADC_SAR_IRQ Interrupt. */
    ResistiveTouch_1_ADC_SAR_IRQ_SetVector(&ResistiveTouch_1_ADC_SAR_IRQ_Interrupt);

    /* Set the priority. */
    ResistiveTouch_1_ADC_SAR_IRQ_SetPriority((uint8)ResistiveTouch_1_ADC_SAR_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ResistiveTouch_1_ADC_SAR_IRQ_Enable();
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ResistiveTouch_1_ADC_SAR_IRQ_Disable();

    /* Set the ISR to point to the ResistiveTouch_1_ADC_SAR_IRQ Interrupt. */
    ResistiveTouch_1_ADC_SAR_IRQ_SetVector(address);

    /* Set the priority. */
    ResistiveTouch_1_ADC_SAR_IRQ_SetPriority((uint8)ResistiveTouch_1_ADC_SAR_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ResistiveTouch_1_ADC_SAR_IRQ_Enable();
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_Stop(void)
{
    /* Disable this interrupt. */
    ResistiveTouch_1_ADC_SAR_IRQ_Disable();

    /* Set the ISR to point to the passive one. */
    ResistiveTouch_1_ADC_SAR_IRQ_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for ResistiveTouch_1_ADC_SAR_IRQ.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(ResistiveTouch_1_ADC_SAR_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ResistiveTouch_1_ADC_SAR_IRQ_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ResistiveTouch_1_ADC_SAR_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use ResistiveTouch_1_ADC_SAR_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)ResistiveTouch_1_ADC_SAR_IRQ__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress ResistiveTouch_1_ADC_SAR_IRQ_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)ResistiveTouch_1_ADC_SAR_IRQ__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling ResistiveTouch_1_ADC_SAR_IRQ_Start
*   or ResistiveTouch_1_ADC_SAR_IRQ_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   ResistiveTouch_1_ADC_SAR_IRQ_Start or ResistiveTouch_1_ADC_SAR_IRQ_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_SetPriority(uint8 priority)
{
    *ResistiveTouch_1_ADC_SAR_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 ResistiveTouch_1_ADC_SAR_IRQ_GetPriority(void)
{
    uint8 priority;


    priority = *ResistiveTouch_1_ADC_SAR_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_Enable(void)
{
    /* Enable the general interrupt. */
    *ResistiveTouch_1_ADC_SAR_IRQ_INTC_SET_EN = ResistiveTouch_1_ADC_SAR_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 ResistiveTouch_1_ADC_SAR_IRQ_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*ResistiveTouch_1_ADC_SAR_IRQ_INTC_SET_EN & (uint32)ResistiveTouch_1_ADC_SAR_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_Disable(void)
{
    /* Disable the general interrupt. */
    *ResistiveTouch_1_ADC_SAR_IRQ_INTC_CLR_EN = ResistiveTouch_1_ADC_SAR_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_SetPending(void)
{
    *ResistiveTouch_1_ADC_SAR_IRQ_INTC_SET_PD = ResistiveTouch_1_ADC_SAR_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: ResistiveTouch_1_ADC_SAR_IRQ_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ResistiveTouch_1_ADC_SAR_IRQ_ClearPending(void)
{
    *ResistiveTouch_1_ADC_SAR_IRQ_INTC_CLR_PD = ResistiveTouch_1_ADC_SAR_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
