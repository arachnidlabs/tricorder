/*******************************************************************************
* File Name: Drive_Out_P01.h  
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

#if !defined(CY_PINS_Drive_Out_P01_H) /* Pins Drive_Out_P01_H */
#define CY_PINS_Drive_Out_P01_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Drive_Out_P01_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Drive_Out_P01__PORT == 15 && ((Drive_Out_P01__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Drive_Out_P01_Write(uint8 value) ;
void    Drive_Out_P01_SetDriveMode(uint8 mode) ;
uint8   Drive_Out_P01_ReadDataReg(void) ;
uint8   Drive_Out_P01_Read(void) ;
uint8   Drive_Out_P01_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Drive_Out_P01_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Drive_Out_P01_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Drive_Out_P01_DM_RES_UP          PIN_DM_RES_UP
#define Drive_Out_P01_DM_RES_DWN         PIN_DM_RES_DWN
#define Drive_Out_P01_DM_OD_LO           PIN_DM_OD_LO
#define Drive_Out_P01_DM_OD_HI           PIN_DM_OD_HI
#define Drive_Out_P01_DM_STRONG          PIN_DM_STRONG
#define Drive_Out_P01_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Drive_Out_P01_MASK               Drive_Out_P01__MASK
#define Drive_Out_P01_SHIFT              Drive_Out_P01__SHIFT
#define Drive_Out_P01_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Drive_Out_P01_PS                     (* (reg8 *) Drive_Out_P01__PS)
/* Data Register */
#define Drive_Out_P01_DR                     (* (reg8 *) Drive_Out_P01__DR)
/* Port Number */
#define Drive_Out_P01_PRT_NUM                (* (reg8 *) Drive_Out_P01__PRT) 
/* Connect to Analog Globals */                                                  
#define Drive_Out_P01_AG                     (* (reg8 *) Drive_Out_P01__AG)                       
/* Analog MUX bux enable */
#define Drive_Out_P01_AMUX                   (* (reg8 *) Drive_Out_P01__AMUX) 
/* Bidirectional Enable */                                                        
#define Drive_Out_P01_BIE                    (* (reg8 *) Drive_Out_P01__BIE)
/* Bit-mask for Aliased Register Access */
#define Drive_Out_P01_BIT_MASK               (* (reg8 *) Drive_Out_P01__BIT_MASK)
/* Bypass Enable */
#define Drive_Out_P01_BYP                    (* (reg8 *) Drive_Out_P01__BYP)
/* Port wide control signals */                                                   
#define Drive_Out_P01_CTL                    (* (reg8 *) Drive_Out_P01__CTL)
/* Drive Modes */
#define Drive_Out_P01_DM0                    (* (reg8 *) Drive_Out_P01__DM0) 
#define Drive_Out_P01_DM1                    (* (reg8 *) Drive_Out_P01__DM1)
#define Drive_Out_P01_DM2                    (* (reg8 *) Drive_Out_P01__DM2) 
/* Input Buffer Disable Override */
#define Drive_Out_P01_INP_DIS                (* (reg8 *) Drive_Out_P01__INP_DIS)
/* LCD Common or Segment Drive */
#define Drive_Out_P01_LCD_COM_SEG            (* (reg8 *) Drive_Out_P01__LCD_COM_SEG)
/* Enable Segment LCD */
#define Drive_Out_P01_LCD_EN                 (* (reg8 *) Drive_Out_P01__LCD_EN)
/* Slew Rate Control */
#define Drive_Out_P01_SLW                    (* (reg8 *) Drive_Out_P01__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Drive_Out_P01_PRTDSI__CAPS_SEL       (* (reg8 *) Drive_Out_P01__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Drive_Out_P01_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Drive_Out_P01__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Drive_Out_P01_PRTDSI__OE_SEL0        (* (reg8 *) Drive_Out_P01__PRTDSI__OE_SEL0) 
#define Drive_Out_P01_PRTDSI__OE_SEL1        (* (reg8 *) Drive_Out_P01__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Drive_Out_P01_PRTDSI__OUT_SEL0       (* (reg8 *) Drive_Out_P01__PRTDSI__OUT_SEL0) 
#define Drive_Out_P01_PRTDSI__OUT_SEL1       (* (reg8 *) Drive_Out_P01__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Drive_Out_P01_PRTDSI__SYNC_OUT       (* (reg8 *) Drive_Out_P01__PRTDSI__SYNC_OUT) 


#if defined(Drive_Out_P01__INTSTAT)  /* Interrupt Registers */

    #define Drive_Out_P01_INTSTAT                (* (reg8 *) Drive_Out_P01__INTSTAT)
    #define Drive_Out_P01_SNAP                   (* (reg8 *) Drive_Out_P01__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Drive_Out_P01_H */


/* [] END OF FILE */
