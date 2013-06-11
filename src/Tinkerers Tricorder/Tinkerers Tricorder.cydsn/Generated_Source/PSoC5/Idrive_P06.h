/*******************************************************************************
* File Name: Idrive_P06.h  
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

#if !defined(CY_PINS_Idrive_P06_H) /* Pins Idrive_P06_H */
#define CY_PINS_Idrive_P06_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Idrive_P06_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Idrive_P06__PORT == 15 && ((Idrive_P06__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Idrive_P06_Write(uint8 value) ;
void    Idrive_P06_SetDriveMode(uint8 mode) ;
uint8   Idrive_P06_ReadDataReg(void) ;
uint8   Idrive_P06_Read(void) ;
uint8   Idrive_P06_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Idrive_P06_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Idrive_P06_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Idrive_P06_DM_RES_UP          PIN_DM_RES_UP
#define Idrive_P06_DM_RES_DWN         PIN_DM_RES_DWN
#define Idrive_P06_DM_OD_LO           PIN_DM_OD_LO
#define Idrive_P06_DM_OD_HI           PIN_DM_OD_HI
#define Idrive_P06_DM_STRONG          PIN_DM_STRONG
#define Idrive_P06_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Idrive_P06_MASK               Idrive_P06__MASK
#define Idrive_P06_SHIFT              Idrive_P06__SHIFT
#define Idrive_P06_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Idrive_P06_PS                     (* (reg8 *) Idrive_P06__PS)
/* Data Register */
#define Idrive_P06_DR                     (* (reg8 *) Idrive_P06__DR)
/* Port Number */
#define Idrive_P06_PRT_NUM                (* (reg8 *) Idrive_P06__PRT) 
/* Connect to Analog Globals */                                                  
#define Idrive_P06_AG                     (* (reg8 *) Idrive_P06__AG)                       
/* Analog MUX bux enable */
#define Idrive_P06_AMUX                   (* (reg8 *) Idrive_P06__AMUX) 
/* Bidirectional Enable */                                                        
#define Idrive_P06_BIE                    (* (reg8 *) Idrive_P06__BIE)
/* Bit-mask for Aliased Register Access */
#define Idrive_P06_BIT_MASK               (* (reg8 *) Idrive_P06__BIT_MASK)
/* Bypass Enable */
#define Idrive_P06_BYP                    (* (reg8 *) Idrive_P06__BYP)
/* Port wide control signals */                                                   
#define Idrive_P06_CTL                    (* (reg8 *) Idrive_P06__CTL)
/* Drive Modes */
#define Idrive_P06_DM0                    (* (reg8 *) Idrive_P06__DM0) 
#define Idrive_P06_DM1                    (* (reg8 *) Idrive_P06__DM1)
#define Idrive_P06_DM2                    (* (reg8 *) Idrive_P06__DM2) 
/* Input Buffer Disable Override */
#define Idrive_P06_INP_DIS                (* (reg8 *) Idrive_P06__INP_DIS)
/* LCD Common or Segment Drive */
#define Idrive_P06_LCD_COM_SEG            (* (reg8 *) Idrive_P06__LCD_COM_SEG)
/* Enable Segment LCD */
#define Idrive_P06_LCD_EN                 (* (reg8 *) Idrive_P06__LCD_EN)
/* Slew Rate Control */
#define Idrive_P06_SLW                    (* (reg8 *) Idrive_P06__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Idrive_P06_PRTDSI__CAPS_SEL       (* (reg8 *) Idrive_P06__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Idrive_P06_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Idrive_P06__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Idrive_P06_PRTDSI__OE_SEL0        (* (reg8 *) Idrive_P06__PRTDSI__OE_SEL0) 
#define Idrive_P06_PRTDSI__OE_SEL1        (* (reg8 *) Idrive_P06__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Idrive_P06_PRTDSI__OUT_SEL0       (* (reg8 *) Idrive_P06__PRTDSI__OUT_SEL0) 
#define Idrive_P06_PRTDSI__OUT_SEL1       (* (reg8 *) Idrive_P06__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Idrive_P06_PRTDSI__SYNC_OUT       (* (reg8 *) Idrive_P06__PRTDSI__SYNC_OUT) 


#if defined(Idrive_P06__INTSTAT)  /* Interrupt Registers */

    #define Idrive_P06_INTSTAT                (* (reg8 *) Idrive_P06__INTSTAT)
    #define Idrive_P06_SNAP                   (* (reg8 *) Idrive_P06__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Idrive_P06_H */


/* [] END OF FILE */
