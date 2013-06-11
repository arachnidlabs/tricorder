/*******************************************************************************
* File Name: drive_freq_range.h  
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

#if !defined(CY_PINS_drive_freq_range_H) /* Pins drive_freq_range_H */
#define CY_PINS_drive_freq_range_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "drive_freq_range_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 drive_freq_range__PORT == 15 && ((drive_freq_range__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    drive_freq_range_Write(uint8 value) ;
void    drive_freq_range_SetDriveMode(uint8 mode) ;
uint8   drive_freq_range_ReadDataReg(void) ;
uint8   drive_freq_range_Read(void) ;
uint8   drive_freq_range_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define drive_freq_range_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define drive_freq_range_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define drive_freq_range_DM_RES_UP          PIN_DM_RES_UP
#define drive_freq_range_DM_RES_DWN         PIN_DM_RES_DWN
#define drive_freq_range_DM_OD_LO           PIN_DM_OD_LO
#define drive_freq_range_DM_OD_HI           PIN_DM_OD_HI
#define drive_freq_range_DM_STRONG          PIN_DM_STRONG
#define drive_freq_range_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define drive_freq_range_MASK               drive_freq_range__MASK
#define drive_freq_range_SHIFT              drive_freq_range__SHIFT
#define drive_freq_range_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define drive_freq_range_PS                     (* (reg8 *) drive_freq_range__PS)
/* Data Register */
#define drive_freq_range_DR                     (* (reg8 *) drive_freq_range__DR)
/* Port Number */
#define drive_freq_range_PRT_NUM                (* (reg8 *) drive_freq_range__PRT) 
/* Connect to Analog Globals */                                                  
#define drive_freq_range_AG                     (* (reg8 *) drive_freq_range__AG)                       
/* Analog MUX bux enable */
#define drive_freq_range_AMUX                   (* (reg8 *) drive_freq_range__AMUX) 
/* Bidirectional Enable */                                                        
#define drive_freq_range_BIE                    (* (reg8 *) drive_freq_range__BIE)
/* Bit-mask for Aliased Register Access */
#define drive_freq_range_BIT_MASK               (* (reg8 *) drive_freq_range__BIT_MASK)
/* Bypass Enable */
#define drive_freq_range_BYP                    (* (reg8 *) drive_freq_range__BYP)
/* Port wide control signals */                                                   
#define drive_freq_range_CTL                    (* (reg8 *) drive_freq_range__CTL)
/* Drive Modes */
#define drive_freq_range_DM0                    (* (reg8 *) drive_freq_range__DM0) 
#define drive_freq_range_DM1                    (* (reg8 *) drive_freq_range__DM1)
#define drive_freq_range_DM2                    (* (reg8 *) drive_freq_range__DM2) 
/* Input Buffer Disable Override */
#define drive_freq_range_INP_DIS                (* (reg8 *) drive_freq_range__INP_DIS)
/* LCD Common or Segment Drive */
#define drive_freq_range_LCD_COM_SEG            (* (reg8 *) drive_freq_range__LCD_COM_SEG)
/* Enable Segment LCD */
#define drive_freq_range_LCD_EN                 (* (reg8 *) drive_freq_range__LCD_EN)
/* Slew Rate Control */
#define drive_freq_range_SLW                    (* (reg8 *) drive_freq_range__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define drive_freq_range_PRTDSI__CAPS_SEL       (* (reg8 *) drive_freq_range__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define drive_freq_range_PRTDSI__DBL_SYNC_IN    (* (reg8 *) drive_freq_range__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define drive_freq_range_PRTDSI__OE_SEL0        (* (reg8 *) drive_freq_range__PRTDSI__OE_SEL0) 
#define drive_freq_range_PRTDSI__OE_SEL1        (* (reg8 *) drive_freq_range__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define drive_freq_range_PRTDSI__OUT_SEL0       (* (reg8 *) drive_freq_range__PRTDSI__OUT_SEL0) 
#define drive_freq_range_PRTDSI__OUT_SEL1       (* (reg8 *) drive_freq_range__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define drive_freq_range_PRTDSI__SYNC_OUT       (* (reg8 *) drive_freq_range__PRTDSI__SYNC_OUT) 


#if defined(drive_freq_range__INTSTAT)  /* Interrupt Registers */

    #define drive_freq_range_INTSTAT                (* (reg8 *) drive_freq_range__INTSTAT)
    #define drive_freq_range_SNAP                   (* (reg8 *) drive_freq_range__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_drive_freq_range_H */


/* [] END OF FILE */
