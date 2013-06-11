/*******************************************************************************
* File Name: InPhase_Clock.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_InPhase_Clock_H) /* Pins InPhase_Clock_H */
#define CY_PINS_InPhase_Clock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "InPhase_Clock_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 InPhase_Clock__PORT == 15 && ((InPhase_Clock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    InPhase_Clock_Write(uint8 value) ;
void    InPhase_Clock_SetDriveMode(uint8 mode) ;
uint8   InPhase_Clock_ReadDataReg(void) ;
uint8   InPhase_Clock_Read(void) ;
uint8   InPhase_Clock_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define InPhase_Clock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define InPhase_Clock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define InPhase_Clock_DM_RES_UP          PIN_DM_RES_UP
#define InPhase_Clock_DM_RES_DWN         PIN_DM_RES_DWN
#define InPhase_Clock_DM_OD_LO           PIN_DM_OD_LO
#define InPhase_Clock_DM_OD_HI           PIN_DM_OD_HI
#define InPhase_Clock_DM_STRONG          PIN_DM_STRONG
#define InPhase_Clock_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define InPhase_Clock_MASK               InPhase_Clock__MASK
#define InPhase_Clock_SHIFT              InPhase_Clock__SHIFT
#define InPhase_Clock_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define InPhase_Clock_PS                     (* (reg8 *) InPhase_Clock__PS)
/* Data Register */
#define InPhase_Clock_DR                     (* (reg8 *) InPhase_Clock__DR)
/* Port Number */
#define InPhase_Clock_PRT_NUM                (* (reg8 *) InPhase_Clock__PRT) 
/* Connect to Analog Globals */                                                  
#define InPhase_Clock_AG                     (* (reg8 *) InPhase_Clock__AG)                       
/* Analog MUX bux enable */
#define InPhase_Clock_AMUX                   (* (reg8 *) InPhase_Clock__AMUX) 
/* Bidirectional Enable */                                                        
#define InPhase_Clock_BIE                    (* (reg8 *) InPhase_Clock__BIE)
/* Bit-mask for Aliased Register Access */
#define InPhase_Clock_BIT_MASK               (* (reg8 *) InPhase_Clock__BIT_MASK)
/* Bypass Enable */
#define InPhase_Clock_BYP                    (* (reg8 *) InPhase_Clock__BYP)
/* Port wide control signals */                                                   
#define InPhase_Clock_CTL                    (* (reg8 *) InPhase_Clock__CTL)
/* Drive Modes */
#define InPhase_Clock_DM0                    (* (reg8 *) InPhase_Clock__DM0) 
#define InPhase_Clock_DM1                    (* (reg8 *) InPhase_Clock__DM1)
#define InPhase_Clock_DM2                    (* (reg8 *) InPhase_Clock__DM2) 
/* Input Buffer Disable Override */
#define InPhase_Clock_INP_DIS                (* (reg8 *) InPhase_Clock__INP_DIS)
/* LCD Common or Segment Drive */
#define InPhase_Clock_LCD_COM_SEG            (* (reg8 *) InPhase_Clock__LCD_COM_SEG)
/* Enable Segment LCD */
#define InPhase_Clock_LCD_EN                 (* (reg8 *) InPhase_Clock__LCD_EN)
/* Slew Rate Control */
#define InPhase_Clock_SLW                    (* (reg8 *) InPhase_Clock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define InPhase_Clock_PRTDSI__CAPS_SEL       (* (reg8 *) InPhase_Clock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define InPhase_Clock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) InPhase_Clock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define InPhase_Clock_PRTDSI__OE_SEL0        (* (reg8 *) InPhase_Clock__PRTDSI__OE_SEL0) 
#define InPhase_Clock_PRTDSI__OE_SEL1        (* (reg8 *) InPhase_Clock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define InPhase_Clock_PRTDSI__OUT_SEL0       (* (reg8 *) InPhase_Clock__PRTDSI__OUT_SEL0) 
#define InPhase_Clock_PRTDSI__OUT_SEL1       (* (reg8 *) InPhase_Clock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define InPhase_Clock_PRTDSI__SYNC_OUT       (* (reg8 *) InPhase_Clock__PRTDSI__SYNC_OUT) 


#if defined(InPhase_Clock__INTSTAT)  /* Interrupt Registers */

    #define InPhase_Clock_INTSTAT                (* (reg8 *) InPhase_Clock__INTSTAT)
    #define InPhase_Clock_SNAP                   (* (reg8 *) InPhase_Clock__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_InPhase_Clock_H */


/* [] END OF FILE */
