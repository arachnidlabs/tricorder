/*******************************************************************************
* File Name: tia_range.h  
* Version 1.90
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

#if !defined(CY_PINS_tia_range_H) /* Pins tia_range_H */
#define CY_PINS_tia_range_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "tia_range_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 tia_range__PORT == 15 && ((tia_range__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    tia_range_Write(uint8 value) ;
void    tia_range_SetDriveMode(uint8 mode) ;
uint8   tia_range_ReadDataReg(void) ;
uint8   tia_range_Read(void) ;
uint8   tia_range_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define tia_range_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define tia_range_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define tia_range_DM_RES_UP          PIN_DM_RES_UP
#define tia_range_DM_RES_DWN         PIN_DM_RES_DWN
#define tia_range_DM_OD_LO           PIN_DM_OD_LO
#define tia_range_DM_OD_HI           PIN_DM_OD_HI
#define tia_range_DM_STRONG          PIN_DM_STRONG
#define tia_range_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define tia_range_MASK               tia_range__MASK
#define tia_range_SHIFT              tia_range__SHIFT
#define tia_range_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define tia_range_PS                     (* (reg8 *) tia_range__PS)
/* Data Register */
#define tia_range_DR                     (* (reg8 *) tia_range__DR)
/* Port Number */
#define tia_range_PRT_NUM                (* (reg8 *) tia_range__PRT) 
/* Connect to Analog Globals */                                                  
#define tia_range_AG                     (* (reg8 *) tia_range__AG)                       
/* Analog MUX bux enable */
#define tia_range_AMUX                   (* (reg8 *) tia_range__AMUX) 
/* Bidirectional Enable */                                                        
#define tia_range_BIE                    (* (reg8 *) tia_range__BIE)
/* Bit-mask for Aliased Register Access */
#define tia_range_BIT_MASK               (* (reg8 *) tia_range__BIT_MASK)
/* Bypass Enable */
#define tia_range_BYP                    (* (reg8 *) tia_range__BYP)
/* Port wide control signals */                                                   
#define tia_range_CTL                    (* (reg8 *) tia_range__CTL)
/* Drive Modes */
#define tia_range_DM0                    (* (reg8 *) tia_range__DM0) 
#define tia_range_DM1                    (* (reg8 *) tia_range__DM1)
#define tia_range_DM2                    (* (reg8 *) tia_range__DM2) 
/* Input Buffer Disable Override */
#define tia_range_INP_DIS                (* (reg8 *) tia_range__INP_DIS)
/* LCD Common or Segment Drive */
#define tia_range_LCD_COM_SEG            (* (reg8 *) tia_range__LCD_COM_SEG)
/* Enable Segment LCD */
#define tia_range_LCD_EN                 (* (reg8 *) tia_range__LCD_EN)
/* Slew Rate Control */
#define tia_range_SLW                    (* (reg8 *) tia_range__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define tia_range_PRTDSI__CAPS_SEL       (* (reg8 *) tia_range__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define tia_range_PRTDSI__DBL_SYNC_IN    (* (reg8 *) tia_range__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define tia_range_PRTDSI__OE_SEL0        (* (reg8 *) tia_range__PRTDSI__OE_SEL0) 
#define tia_range_PRTDSI__OE_SEL1        (* (reg8 *) tia_range__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define tia_range_PRTDSI__OUT_SEL0       (* (reg8 *) tia_range__PRTDSI__OUT_SEL0) 
#define tia_range_PRTDSI__OUT_SEL1       (* (reg8 *) tia_range__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define tia_range_PRTDSI__SYNC_OUT       (* (reg8 *) tia_range__PRTDSI__SYNC_OUT) 


#if defined(tia_range__INTSTAT)  /* Interrupt Registers */

    #define tia_range_INTSTAT                (* (reg8 *) tia_range__INTSTAT)
    #define tia_range_SNAP                   (* (reg8 *) tia_range__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_tia_range_H */


/* [] END OF FILE */
