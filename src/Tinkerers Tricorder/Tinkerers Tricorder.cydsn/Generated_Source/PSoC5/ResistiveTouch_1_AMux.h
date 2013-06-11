/*******************************************************************************
* File Name: ResistiveTouch_1_AMux.h
* Version 1.70
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_ResistiveTouch_1_AMux_H)
#define CY_AMUXSEQ_ResistiveTouch_1_AMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void ResistiveTouch_1_AMux_Start(void);
void ResistiveTouch_1_AMux_Init(void);
void ResistiveTouch_1_AMux_Stop(void);
void ResistiveTouch_1_AMux_Next(void);
void ResistiveTouch_1_AMux_DisconnectAll(void);
int8 ResistiveTouch_1_AMux_GetChannel(void);


/***************************************
*     Initial Parameter Constants
***************************************/
#define ResistiveTouch_1_AMux_CHANNELS  2
#define ResistiveTouch_1_AMux_MUXTYPE   1


/***************************************
*             API Constants
***************************************/

#define ResistiveTouch_1_AMux_MUX_SINGLE   1
#define ResistiveTouch_1_AMux_MUX_DIFF     2

#endif /* CY_AMUXSEQ_ResistiveTouch_1_AMux_H */


/* [] END OF FILE */
