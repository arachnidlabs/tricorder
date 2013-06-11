/*******************************************************************************
* File Name: Button_Mode.h  
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

#if !defined(CY_PINS_Button_Mode_H) /* Pins Button_Mode_H */
#define CY_PINS_Button_Mode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_Mode_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_Mode__PORT == 15 && ((Button_Mode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Mode_Write(uint8 value) ;
void    Button_Mode_SetDriveMode(uint8 mode) ;
uint8   Button_Mode_ReadDataReg(void) ;
uint8   Button_Mode_Read(void) ;
uint8   Button_Mode_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_Mode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_Mode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_Mode_DM_RES_UP          PIN_DM_RES_UP
#define Button_Mode_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_Mode_DM_OD_LO           PIN_DM_OD_LO
#define Button_Mode_DM_OD_HI           PIN_DM_OD_HI
#define Button_Mode_DM_STRONG          PIN_DM_STRONG
#define Button_Mode_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_Mode_MASK               Button_Mode__MASK
#define Button_Mode_SHIFT              Button_Mode__SHIFT
#define Button_Mode_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_Mode_PS                     (* (reg8 *) Button_Mode__PS)
/* Data Register */
#define Button_Mode_DR                     (* (reg8 *) Button_Mode__DR)
/* Port Number */
#define Button_Mode_PRT_NUM                (* (reg8 *) Button_Mode__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_Mode_AG                     (* (reg8 *) Button_Mode__AG)                       
/* Analog MUX bux enable */
#define Button_Mode_AMUX                   (* (reg8 *) Button_Mode__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_Mode_BIE                    (* (reg8 *) Button_Mode__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_Mode_BIT_MASK               (* (reg8 *) Button_Mode__BIT_MASK)
/* Bypass Enable */
#define Button_Mode_BYP                    (* (reg8 *) Button_Mode__BYP)
/* Port wide control signals */                                                   
#define Button_Mode_CTL                    (* (reg8 *) Button_Mode__CTL)
/* Drive Modes */
#define Button_Mode_DM0                    (* (reg8 *) Button_Mode__DM0) 
#define Button_Mode_DM1                    (* (reg8 *) Button_Mode__DM1)
#define Button_Mode_DM2                    (* (reg8 *) Button_Mode__DM2) 
/* Input Buffer Disable Override */
#define Button_Mode_INP_DIS                (* (reg8 *) Button_Mode__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_Mode_LCD_COM_SEG            (* (reg8 *) Button_Mode__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_Mode_LCD_EN                 (* (reg8 *) Button_Mode__LCD_EN)
/* Slew Rate Control */
#define Button_Mode_SLW                    (* (reg8 *) Button_Mode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_Mode_PRTDSI__CAPS_SEL       (* (reg8 *) Button_Mode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_Mode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_Mode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_Mode_PRTDSI__OE_SEL0        (* (reg8 *) Button_Mode__PRTDSI__OE_SEL0) 
#define Button_Mode_PRTDSI__OE_SEL1        (* (reg8 *) Button_Mode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_Mode_PRTDSI__OUT_SEL0       (* (reg8 *) Button_Mode__PRTDSI__OUT_SEL0) 
#define Button_Mode_PRTDSI__OUT_SEL1       (* (reg8 *) Button_Mode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_Mode_PRTDSI__SYNC_OUT       (* (reg8 *) Button_Mode__PRTDSI__SYNC_OUT) 


#if defined(Button_Mode__INTSTAT)  /* Interrupt Registers */

    #define Button_Mode_INTSTAT                (* (reg8 *) Button_Mode__INTSTAT)
    #define Button_Mode_SNAP                   (* (reg8 *) Button_Mode__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Button_Mode_H */


/* [] END OF FILE */
