/*******************************************************************************
* File Name: Measure_Mux.h
* Version 1.70
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_Measure_Mux_H)
#define CY_AMUX_Measure_Mux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void Measure_Mux_Start(void);
# define Measure_Mux_Init() Measure_Mux_Start()
void Measure_Mux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void Measure_Mux_Stop(void); */
/* void Measure_Mux_Select(uint8 channel); */
/* void Measure_Mux_Connect(uint8 channel); */
/* void Measure_Mux_Disconnect(uint8 channel); */
/* void Measure_Mux_DisconnectAll(void) */


/***************************************
*     Initial Parameter Constants
***************************************/

#define Measure_Mux_CHANNELS  2
#define Measure_Mux_MUXTYPE   1
#define Measure_Mux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define Measure_Mux_NULL_CHANNEL  0xFFu
#define Measure_Mux_MUX_SINGLE   1
#define Measure_Mux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if Measure_Mux_MUXTYPE == Measure_Mux_MUX_SINGLE
#if !Measure_Mux_ATMOSTONE
# define Measure_Mux_Connect(channel) Measure_Mux_Set(channel)
#endif
# define Measure_Mux_Disconnect(channel) Measure_Mux_Unset(channel)
#else
#if !Measure_Mux_ATMOSTONE
void Measure_Mux_Connect(uint8 channel) ;
#endif
void Measure_Mux_Disconnect(uint8 channel) ;
#endif

#if Measure_Mux_ATMOSTONE
# define Measure_Mux_Stop() Measure_Mux_DisconnectAll()
# define Measure_Mux_Select(channel) Measure_Mux_FastSelect(channel)
void Measure_Mux_DisconnectAll(void) ;
#else
# define Measure_Mux_Stop() Measure_Mux_Start()
void Measure_Mux_Select(uint8 channel) ;
# define Measure_Mux_DisconnectAll() Measure_Mux_Start()
#endif

#endif /* CY_AMUX_Measure_Mux_H */


/* [] END OF FILE */
