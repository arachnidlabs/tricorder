/*******************************************************************************
* File Name: TIA_Output.h  
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

#if !defined(CY_PINS_TIA_Output_H) /* Pins TIA_Output_H */
#define CY_PINS_TIA_Output_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TIA_Output_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TIA_Output__PORT == 15 && ((TIA_Output__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TIA_Output_Write(uint8 value) ;
void    TIA_Output_SetDriveMode(uint8 mode) ;
uint8   TIA_Output_ReadDataReg(void) ;
uint8   TIA_Output_Read(void) ;
uint8   TIA_Output_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TIA_Output_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TIA_Output_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TIA_Output_DM_RES_UP          PIN_DM_RES_UP
#define TIA_Output_DM_RES_DWN         PIN_DM_RES_DWN
#define TIA_Output_DM_OD_LO           PIN_DM_OD_LO
#define TIA_Output_DM_OD_HI           PIN_DM_OD_HI
#define TIA_Output_DM_STRONG          PIN_DM_STRONG
#define TIA_Output_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TIA_Output_MASK               TIA_Output__MASK
#define TIA_Output_SHIFT              TIA_Output__SHIFT
#define TIA_Output_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TIA_Output_PS                     (* (reg8 *) TIA_Output__PS)
/* Data Register */
#define TIA_Output_DR                     (* (reg8 *) TIA_Output__DR)
/* Port Number */
#define TIA_Output_PRT_NUM                (* (reg8 *) TIA_Output__PRT) 
/* Connect to Analog Globals */                                                  
#define TIA_Output_AG                     (* (reg8 *) TIA_Output__AG)                       
/* Analog MUX bux enable */
#define TIA_Output_AMUX                   (* (reg8 *) TIA_Output__AMUX) 
/* Bidirectional Enable */                                                        
#define TIA_Output_BIE                    (* (reg8 *) TIA_Output__BIE)
/* Bit-mask for Aliased Register Access */
#define TIA_Output_BIT_MASK               (* (reg8 *) TIA_Output__BIT_MASK)
/* Bypass Enable */
#define TIA_Output_BYP                    (* (reg8 *) TIA_Output__BYP)
/* Port wide control signals */                                                   
#define TIA_Output_CTL                    (* (reg8 *) TIA_Output__CTL)
/* Drive Modes */
#define TIA_Output_DM0                    (* (reg8 *) TIA_Output__DM0) 
#define TIA_Output_DM1                    (* (reg8 *) TIA_Output__DM1)
#define TIA_Output_DM2                    (* (reg8 *) TIA_Output__DM2) 
/* Input Buffer Disable Override */
#define TIA_Output_INP_DIS                (* (reg8 *) TIA_Output__INP_DIS)
/* LCD Common or Segment Drive */
#define TIA_Output_LCD_COM_SEG            (* (reg8 *) TIA_Output__LCD_COM_SEG)
/* Enable Segment LCD */
#define TIA_Output_LCD_EN                 (* (reg8 *) TIA_Output__LCD_EN)
/* Slew Rate Control */
#define TIA_Output_SLW                    (* (reg8 *) TIA_Output__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TIA_Output_PRTDSI__CAPS_SEL       (* (reg8 *) TIA_Output__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TIA_Output_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TIA_Output__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TIA_Output_PRTDSI__OE_SEL0        (* (reg8 *) TIA_Output__PRTDSI__OE_SEL0) 
#define TIA_Output_PRTDSI__OE_SEL1        (* (reg8 *) TIA_Output__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TIA_Output_PRTDSI__OUT_SEL0       (* (reg8 *) TIA_Output__PRTDSI__OUT_SEL0) 
#define TIA_Output_PRTDSI__OUT_SEL1       (* (reg8 *) TIA_Output__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TIA_Output_PRTDSI__SYNC_OUT       (* (reg8 *) TIA_Output__PRTDSI__SYNC_OUT) 


#if defined(TIA_Output__INTSTAT)  /* Interrupt Registers */

    #define TIA_Output_INTSTAT                (* (reg8 *) TIA_Output__INTSTAT)
    #define TIA_Output_SNAP                   (* (reg8 *) TIA_Output__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TIA_Output_H */


/* [] END OF FILE */
