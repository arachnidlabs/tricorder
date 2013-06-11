/*******************************************************************************
* File Name: ResistiveTouch_1.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the 
*  ResistiveTouch component.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RESISTIVE_TOUCH_ResistiveTouch_1_H)
#define CY_RESISTIVE_TOUCH_ResistiveTouch_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice_trm.h"
#include "CyLib.h"
#include "project.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ResistiveTouch_1_SAR_SELECT (1u)

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */

#if !defined (CY_PSOC5A)
    #error Component ResistiveTouch_v1_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5A) */


/***************************************
*       Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct _ResistiveTouch_1_backupStruct
{
    uint8  enableState;
} ResistiveTouch_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
****************************************/

void ResistiveTouch_1_Start(void) ;
void ResistiveTouch_1_Stop(void) ;
void ResistiveTouch_1_Init(void) ; 
void ResistiveTouch_1_Enable(void) ;
void ResistiveTouch_1_ActivateX(void) ;
void ResistiveTouch_1_ActivateY(void);
int16 ResistiveTouch_1_Measure(void) ;
uint8 ResistiveTouch_1_TouchDetect(void) ;

void ResistiveTouch_1_SaveConfig(void) ;
void ResistiveTouch_1_RestoreConfig(void) ;
void ResistiveTouch_1_Sleep(void) ; 
void ResistiveTouch_1_Wakeup(void) ; 

/* Macros for emWinGraphics Library */
#define CYTOUCH_START()         ResistiveTouch_1_Start() 
#define CYTOUCH_STOP()          ResistiveTouch_1_Stop()
#define CYTOUCH_MEASURE()       ResistiveTouch_1_Measure()
#define CYTOUCH_ACTIVATE_X()    ResistiveTouch_1_ActivateX()
#define CYTOUCH_ACTIVATE_Y()    ResistiveTouch_1_ActivateY()
#define CYTOUCH_TOUCHED()       ResistiveTouch_1_TouchDetect()


/***************************************
*       Constants
***************************************/

/* SAR_SELECT definitions */
#define ResistiveTouch_1_SAR    (1u)
#define ResistiveTouch_1_DSIGMA (0u)

/* AMUX channel definitions */
#define ResistiveTouch_1_AMUX_XP_CHAN   (0u)
#define ResistiveTouch_1_AMUX_YP_CHAN   (1u)
#define ResistiveTouch_1_AMUX_NO_CHAN   (-1)


#endif /* CY_RESIST_TOUCH_ResistiveTouch_1_H */


/* [] END OF FILE */
