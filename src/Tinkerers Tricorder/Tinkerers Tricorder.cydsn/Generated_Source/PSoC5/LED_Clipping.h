/*******************************************************************************
* File Name: LED_Clipping.h  
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

#if !defined(CY_PINS_LED_Clipping_H) /* Pins LED_Clipping_H */
#define CY_PINS_LED_Clipping_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_Clipping_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_Clipping__PORT == 15 && ((LED_Clipping__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Clipping_Write(uint8 value) ;
void    LED_Clipping_SetDriveMode(uint8 mode) ;
uint8   LED_Clipping_ReadDataReg(void) ;
uint8   LED_Clipping_Read(void) ;
uint8   LED_Clipping_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_Clipping_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_Clipping_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_Clipping_DM_RES_UP          PIN_DM_RES_UP
#define LED_Clipping_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_Clipping_DM_OD_LO           PIN_DM_OD_LO
#define LED_Clipping_DM_OD_HI           PIN_DM_OD_HI
#define LED_Clipping_DM_STRONG          PIN_DM_STRONG
#define LED_Clipping_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_Clipping_MASK               LED_Clipping__MASK
#define LED_Clipping_SHIFT              LED_Clipping__SHIFT
#define LED_Clipping_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_Clipping_PS                     (* (reg8 *) LED_Clipping__PS)
/* Data Register */
#define LED_Clipping_DR                     (* (reg8 *) LED_Clipping__DR)
/* Port Number */
#define LED_Clipping_PRT_NUM                (* (reg8 *) LED_Clipping__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_Clipping_AG                     (* (reg8 *) LED_Clipping__AG)                       
/* Analog MUX bux enable */
#define LED_Clipping_AMUX                   (* (reg8 *) LED_Clipping__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_Clipping_BIE                    (* (reg8 *) LED_Clipping__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_Clipping_BIT_MASK               (* (reg8 *) LED_Clipping__BIT_MASK)
/* Bypass Enable */
#define LED_Clipping_BYP                    (* (reg8 *) LED_Clipping__BYP)
/* Port wide control signals */                                                   
#define LED_Clipping_CTL                    (* (reg8 *) LED_Clipping__CTL)
/* Drive Modes */
#define LED_Clipping_DM0                    (* (reg8 *) LED_Clipping__DM0) 
#define LED_Clipping_DM1                    (* (reg8 *) LED_Clipping__DM1)
#define LED_Clipping_DM2                    (* (reg8 *) LED_Clipping__DM2) 
/* Input Buffer Disable Override */
#define LED_Clipping_INP_DIS                (* (reg8 *) LED_Clipping__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_Clipping_LCD_COM_SEG            (* (reg8 *) LED_Clipping__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_Clipping_LCD_EN                 (* (reg8 *) LED_Clipping__LCD_EN)
/* Slew Rate Control */
#define LED_Clipping_SLW                    (* (reg8 *) LED_Clipping__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_Clipping_PRTDSI__CAPS_SEL       (* (reg8 *) LED_Clipping__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_Clipping_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_Clipping__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_Clipping_PRTDSI__OE_SEL0        (* (reg8 *) LED_Clipping__PRTDSI__OE_SEL0) 
#define LED_Clipping_PRTDSI__OE_SEL1        (* (reg8 *) LED_Clipping__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_Clipping_PRTDSI__OUT_SEL0       (* (reg8 *) LED_Clipping__PRTDSI__OUT_SEL0) 
#define LED_Clipping_PRTDSI__OUT_SEL1       (* (reg8 *) LED_Clipping__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_Clipping_PRTDSI__SYNC_OUT       (* (reg8 *) LED_Clipping__PRTDSI__SYNC_OUT) 


#if defined(LED_Clipping__INTSTAT)  /* Interrupt Registers */

    #define LED_Clipping_INTSTAT                (* (reg8 *) LED_Clipping__INTSTAT)
    #define LED_Clipping_SNAP                   (* (reg8 *) LED_Clipping__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_Clipping_H */


/* [] END OF FILE */
