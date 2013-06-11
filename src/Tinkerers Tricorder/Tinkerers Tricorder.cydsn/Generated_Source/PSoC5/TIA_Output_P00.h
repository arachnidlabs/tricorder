/*******************************************************************************
* File Name: TIA_Output_P00.h  
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

#if !defined(CY_PINS_TIA_Output_P00_H) /* Pins TIA_Output_P00_H */
#define CY_PINS_TIA_Output_P00_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TIA_Output_P00_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TIA_Output_P00__PORT == 15 && ((TIA_Output_P00__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TIA_Output_P00_Write(uint8 value) ;
void    TIA_Output_P00_SetDriveMode(uint8 mode) ;
uint8   TIA_Output_P00_ReadDataReg(void) ;
uint8   TIA_Output_P00_Read(void) ;
uint8   TIA_Output_P00_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TIA_Output_P00_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TIA_Output_P00_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TIA_Output_P00_DM_RES_UP          PIN_DM_RES_UP
#define TIA_Output_P00_DM_RES_DWN         PIN_DM_RES_DWN
#define TIA_Output_P00_DM_OD_LO           PIN_DM_OD_LO
#define TIA_Output_P00_DM_OD_HI           PIN_DM_OD_HI
#define TIA_Output_P00_DM_STRONG          PIN_DM_STRONG
#define TIA_Output_P00_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TIA_Output_P00_MASK               TIA_Output_P00__MASK
#define TIA_Output_P00_SHIFT              TIA_Output_P00__SHIFT
#define TIA_Output_P00_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TIA_Output_P00_PS                     (* (reg8 *) TIA_Output_P00__PS)
/* Data Register */
#define TIA_Output_P00_DR                     (* (reg8 *) TIA_Output_P00__DR)
/* Port Number */
#define TIA_Output_P00_PRT_NUM                (* (reg8 *) TIA_Output_P00__PRT) 
/* Connect to Analog Globals */                                                  
#define TIA_Output_P00_AG                     (* (reg8 *) TIA_Output_P00__AG)                       
/* Analog MUX bux enable */
#define TIA_Output_P00_AMUX                   (* (reg8 *) TIA_Output_P00__AMUX) 
/* Bidirectional Enable */                                                        
#define TIA_Output_P00_BIE                    (* (reg8 *) TIA_Output_P00__BIE)
/* Bit-mask for Aliased Register Access */
#define TIA_Output_P00_BIT_MASK               (* (reg8 *) TIA_Output_P00__BIT_MASK)
/* Bypass Enable */
#define TIA_Output_P00_BYP                    (* (reg8 *) TIA_Output_P00__BYP)
/* Port wide control signals */                                                   
#define TIA_Output_P00_CTL                    (* (reg8 *) TIA_Output_P00__CTL)
/* Drive Modes */
#define TIA_Output_P00_DM0                    (* (reg8 *) TIA_Output_P00__DM0) 
#define TIA_Output_P00_DM1                    (* (reg8 *) TIA_Output_P00__DM1)
#define TIA_Output_P00_DM2                    (* (reg8 *) TIA_Output_P00__DM2) 
/* Input Buffer Disable Override */
#define TIA_Output_P00_INP_DIS                (* (reg8 *) TIA_Output_P00__INP_DIS)
/* LCD Common or Segment Drive */
#define TIA_Output_P00_LCD_COM_SEG            (* (reg8 *) TIA_Output_P00__LCD_COM_SEG)
/* Enable Segment LCD */
#define TIA_Output_P00_LCD_EN                 (* (reg8 *) TIA_Output_P00__LCD_EN)
/* Slew Rate Control */
#define TIA_Output_P00_SLW                    (* (reg8 *) TIA_Output_P00__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TIA_Output_P00_PRTDSI__CAPS_SEL       (* (reg8 *) TIA_Output_P00__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TIA_Output_P00_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TIA_Output_P00__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TIA_Output_P00_PRTDSI__OE_SEL0        (* (reg8 *) TIA_Output_P00__PRTDSI__OE_SEL0) 
#define TIA_Output_P00_PRTDSI__OE_SEL1        (* (reg8 *) TIA_Output_P00__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TIA_Output_P00_PRTDSI__OUT_SEL0       (* (reg8 *) TIA_Output_P00__PRTDSI__OUT_SEL0) 
#define TIA_Output_P00_PRTDSI__OUT_SEL1       (* (reg8 *) TIA_Output_P00__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TIA_Output_P00_PRTDSI__SYNC_OUT       (* (reg8 *) TIA_Output_P00__PRTDSI__SYNC_OUT) 


#if defined(TIA_Output_P00__INTSTAT)  /* Interrupt Registers */

    #define TIA_Output_P00_INTSTAT                (* (reg8 *) TIA_Output_P00__INTSTAT)
    #define TIA_Output_P00_SNAP                   (* (reg8 *) TIA_Output_P00__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TIA_Output_P00_H */


/* [] END OF FILE */
