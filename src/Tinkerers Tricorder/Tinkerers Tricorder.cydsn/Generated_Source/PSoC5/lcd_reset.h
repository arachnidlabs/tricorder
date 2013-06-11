/*******************************************************************************
* File Name: lcd_reset.h  
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

#if !defined(CY_PINS_lcd_reset_H) /* Pins lcd_reset_H */
#define CY_PINS_lcd_reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "lcd_reset_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 lcd_reset__PORT == 15 && ((lcd_reset__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    lcd_reset_Write(uint8 value) ;
void    lcd_reset_SetDriveMode(uint8 mode) ;
uint8   lcd_reset_ReadDataReg(void) ;
uint8   lcd_reset_Read(void) ;
uint8   lcd_reset_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define lcd_reset_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define lcd_reset_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define lcd_reset_DM_RES_UP          PIN_DM_RES_UP
#define lcd_reset_DM_RES_DWN         PIN_DM_RES_DWN
#define lcd_reset_DM_OD_LO           PIN_DM_OD_LO
#define lcd_reset_DM_OD_HI           PIN_DM_OD_HI
#define lcd_reset_DM_STRONG          PIN_DM_STRONG
#define lcd_reset_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define lcd_reset_MASK               lcd_reset__MASK
#define lcd_reset_SHIFT              lcd_reset__SHIFT
#define lcd_reset_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lcd_reset_PS                     (* (reg8 *) lcd_reset__PS)
/* Data Register */
#define lcd_reset_DR                     (* (reg8 *) lcd_reset__DR)
/* Port Number */
#define lcd_reset_PRT_NUM                (* (reg8 *) lcd_reset__PRT) 
/* Connect to Analog Globals */                                                  
#define lcd_reset_AG                     (* (reg8 *) lcd_reset__AG)                       
/* Analog MUX bux enable */
#define lcd_reset_AMUX                   (* (reg8 *) lcd_reset__AMUX) 
/* Bidirectional Enable */                                                        
#define lcd_reset_BIE                    (* (reg8 *) lcd_reset__BIE)
/* Bit-mask for Aliased Register Access */
#define lcd_reset_BIT_MASK               (* (reg8 *) lcd_reset__BIT_MASK)
/* Bypass Enable */
#define lcd_reset_BYP                    (* (reg8 *) lcd_reset__BYP)
/* Port wide control signals */                                                   
#define lcd_reset_CTL                    (* (reg8 *) lcd_reset__CTL)
/* Drive Modes */
#define lcd_reset_DM0                    (* (reg8 *) lcd_reset__DM0) 
#define lcd_reset_DM1                    (* (reg8 *) lcd_reset__DM1)
#define lcd_reset_DM2                    (* (reg8 *) lcd_reset__DM2) 
/* Input Buffer Disable Override */
#define lcd_reset_INP_DIS                (* (reg8 *) lcd_reset__INP_DIS)
/* LCD Common or Segment Drive */
#define lcd_reset_LCD_COM_SEG            (* (reg8 *) lcd_reset__LCD_COM_SEG)
/* Enable Segment LCD */
#define lcd_reset_LCD_EN                 (* (reg8 *) lcd_reset__LCD_EN)
/* Slew Rate Control */
#define lcd_reset_SLW                    (* (reg8 *) lcd_reset__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define lcd_reset_PRTDSI__CAPS_SEL       (* (reg8 *) lcd_reset__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define lcd_reset_PRTDSI__DBL_SYNC_IN    (* (reg8 *) lcd_reset__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define lcd_reset_PRTDSI__OE_SEL0        (* (reg8 *) lcd_reset__PRTDSI__OE_SEL0) 
#define lcd_reset_PRTDSI__OE_SEL1        (* (reg8 *) lcd_reset__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define lcd_reset_PRTDSI__OUT_SEL0       (* (reg8 *) lcd_reset__PRTDSI__OUT_SEL0) 
#define lcd_reset_PRTDSI__OUT_SEL1       (* (reg8 *) lcd_reset__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define lcd_reset_PRTDSI__SYNC_OUT       (* (reg8 *) lcd_reset__PRTDSI__SYNC_OUT) 


#if defined(lcd_reset__INTSTAT)  /* Interrupt Registers */

    #define lcd_reset_INTSTAT                (* (reg8 *) lcd_reset__INTSTAT)
    #define lcd_reset_SNAP                   (* (reg8 *) lcd_reset__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_lcd_reset_H */


/* [] END OF FILE */
