/*******************************************************************************
* File Name: Button_Freq.h  
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

#if !defined(CY_PINS_Button_Freq_H) /* Pins Button_Freq_H */
#define CY_PINS_Button_Freq_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_Freq_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_Freq__PORT == 15 && ((Button_Freq__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Freq_Write(uint8 value) ;
void    Button_Freq_SetDriveMode(uint8 mode) ;
uint8   Button_Freq_ReadDataReg(void) ;
uint8   Button_Freq_Read(void) ;
uint8   Button_Freq_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_Freq_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_Freq_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_Freq_DM_RES_UP          PIN_DM_RES_UP
#define Button_Freq_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_Freq_DM_OD_LO           PIN_DM_OD_LO
#define Button_Freq_DM_OD_HI           PIN_DM_OD_HI
#define Button_Freq_DM_STRONG          PIN_DM_STRONG
#define Button_Freq_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_Freq_MASK               Button_Freq__MASK
#define Button_Freq_SHIFT              Button_Freq__SHIFT
#define Button_Freq_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_Freq_PS                     (* (reg8 *) Button_Freq__PS)
/* Data Register */
#define Button_Freq_DR                     (* (reg8 *) Button_Freq__DR)
/* Port Number */
#define Button_Freq_PRT_NUM                (* (reg8 *) Button_Freq__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_Freq_AG                     (* (reg8 *) Button_Freq__AG)                       
/* Analog MUX bux enable */
#define Button_Freq_AMUX                   (* (reg8 *) Button_Freq__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_Freq_BIE                    (* (reg8 *) Button_Freq__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_Freq_BIT_MASK               (* (reg8 *) Button_Freq__BIT_MASK)
/* Bypass Enable */
#define Button_Freq_BYP                    (* (reg8 *) Button_Freq__BYP)
/* Port wide control signals */                                                   
#define Button_Freq_CTL                    (* (reg8 *) Button_Freq__CTL)
/* Drive Modes */
#define Button_Freq_DM0                    (* (reg8 *) Button_Freq__DM0) 
#define Button_Freq_DM1                    (* (reg8 *) Button_Freq__DM1)
#define Button_Freq_DM2                    (* (reg8 *) Button_Freq__DM2) 
/* Input Buffer Disable Override */
#define Button_Freq_INP_DIS                (* (reg8 *) Button_Freq__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_Freq_LCD_COM_SEG            (* (reg8 *) Button_Freq__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_Freq_LCD_EN                 (* (reg8 *) Button_Freq__LCD_EN)
/* Slew Rate Control */
#define Button_Freq_SLW                    (* (reg8 *) Button_Freq__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_Freq_PRTDSI__CAPS_SEL       (* (reg8 *) Button_Freq__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_Freq_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_Freq__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_Freq_PRTDSI__OE_SEL0        (* (reg8 *) Button_Freq__PRTDSI__OE_SEL0) 
#define Button_Freq_PRTDSI__OE_SEL1        (* (reg8 *) Button_Freq__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_Freq_PRTDSI__OUT_SEL0       (* (reg8 *) Button_Freq__PRTDSI__OUT_SEL0) 
#define Button_Freq_PRTDSI__OUT_SEL1       (* (reg8 *) Button_Freq__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_Freq_PRTDSI__SYNC_OUT       (* (reg8 *) Button_Freq__PRTDSI__SYNC_OUT) 


#if defined(Button_Freq__INTSTAT)  /* Interrupt Registers */

    #define Button_Freq_INTSTAT                (* (reg8 *) Button_Freq__INTSTAT)
    #define Button_Freq_SNAP                   (* (reg8 *) Button_Freq__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Button_Freq_H */


/* [] END OF FILE */
