/*******************************************************************************
* File Name: TIA_Input_P05.h  
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

#if !defined(CY_PINS_TIA_Input_P05_H) /* Pins TIA_Input_P05_H */
#define CY_PINS_TIA_Input_P05_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TIA_Input_P05_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TIA_Input_P05__PORT == 15 && ((TIA_Input_P05__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TIA_Input_P05_Write(uint8 value) ;
void    TIA_Input_P05_SetDriveMode(uint8 mode) ;
uint8   TIA_Input_P05_ReadDataReg(void) ;
uint8   TIA_Input_P05_Read(void) ;
uint8   TIA_Input_P05_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TIA_Input_P05_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TIA_Input_P05_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TIA_Input_P05_DM_RES_UP          PIN_DM_RES_UP
#define TIA_Input_P05_DM_RES_DWN         PIN_DM_RES_DWN
#define TIA_Input_P05_DM_OD_LO           PIN_DM_OD_LO
#define TIA_Input_P05_DM_OD_HI           PIN_DM_OD_HI
#define TIA_Input_P05_DM_STRONG          PIN_DM_STRONG
#define TIA_Input_P05_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TIA_Input_P05_MASK               TIA_Input_P05__MASK
#define TIA_Input_P05_SHIFT              TIA_Input_P05__SHIFT
#define TIA_Input_P05_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TIA_Input_P05_PS                     (* (reg8 *) TIA_Input_P05__PS)
/* Data Register */
#define TIA_Input_P05_DR                     (* (reg8 *) TIA_Input_P05__DR)
/* Port Number */
#define TIA_Input_P05_PRT_NUM                (* (reg8 *) TIA_Input_P05__PRT) 
/* Connect to Analog Globals */                                                  
#define TIA_Input_P05_AG                     (* (reg8 *) TIA_Input_P05__AG)                       
/* Analog MUX bux enable */
#define TIA_Input_P05_AMUX                   (* (reg8 *) TIA_Input_P05__AMUX) 
/* Bidirectional Enable */                                                        
#define TIA_Input_P05_BIE                    (* (reg8 *) TIA_Input_P05__BIE)
/* Bit-mask for Aliased Register Access */
#define TIA_Input_P05_BIT_MASK               (* (reg8 *) TIA_Input_P05__BIT_MASK)
/* Bypass Enable */
#define TIA_Input_P05_BYP                    (* (reg8 *) TIA_Input_P05__BYP)
/* Port wide control signals */                                                   
#define TIA_Input_P05_CTL                    (* (reg8 *) TIA_Input_P05__CTL)
/* Drive Modes */
#define TIA_Input_P05_DM0                    (* (reg8 *) TIA_Input_P05__DM0) 
#define TIA_Input_P05_DM1                    (* (reg8 *) TIA_Input_P05__DM1)
#define TIA_Input_P05_DM2                    (* (reg8 *) TIA_Input_P05__DM2) 
/* Input Buffer Disable Override */
#define TIA_Input_P05_INP_DIS                (* (reg8 *) TIA_Input_P05__INP_DIS)
/* LCD Common or Segment Drive */
#define TIA_Input_P05_LCD_COM_SEG            (* (reg8 *) TIA_Input_P05__LCD_COM_SEG)
/* Enable Segment LCD */
#define TIA_Input_P05_LCD_EN                 (* (reg8 *) TIA_Input_P05__LCD_EN)
/* Slew Rate Control */
#define TIA_Input_P05_SLW                    (* (reg8 *) TIA_Input_P05__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TIA_Input_P05_PRTDSI__CAPS_SEL       (* (reg8 *) TIA_Input_P05__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TIA_Input_P05_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TIA_Input_P05__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TIA_Input_P05_PRTDSI__OE_SEL0        (* (reg8 *) TIA_Input_P05__PRTDSI__OE_SEL0) 
#define TIA_Input_P05_PRTDSI__OE_SEL1        (* (reg8 *) TIA_Input_P05__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TIA_Input_P05_PRTDSI__OUT_SEL0       (* (reg8 *) TIA_Input_P05__PRTDSI__OUT_SEL0) 
#define TIA_Input_P05_PRTDSI__OUT_SEL1       (* (reg8 *) TIA_Input_P05__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TIA_Input_P05_PRTDSI__SYNC_OUT       (* (reg8 *) TIA_Input_P05__PRTDSI__SYNC_OUT) 


#if defined(TIA_Input_P05__INTSTAT)  /* Interrupt Registers */

    #define TIA_Input_P05_INTSTAT                (* (reg8 *) TIA_Input_P05__INTSTAT)
    #define TIA_Input_P05_SNAP                   (* (reg8 *) TIA_Input_P05__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TIA_Input_P05_H */


/* [] END OF FILE */
