/*******************************************************************************
* File Name: Divider.h  
* Version 2.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Divider_H)
#define CY_PWM_Divider_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Divider_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Divider_Resolution 16u
#define Divider_UsingFixedFunction 1u
#define Divider_DeadBandMode 0u
#define Divider_KillModeMinTime 0u
#define Divider_KillMode 1u
#define Divider_PWMMode 0u
#define Divider_PWMModeIsCenterAligned 0u
#define Divider_DeadBandUsed 0u
#define Divider_DeadBand2_4 0u
#if !defined(Divider_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define Divider_UseStatus 1u
#else
    #define Divider_UseStatus 0u
#endif /* !defined(Divider_PWMUDB_sSTSReg_stsreg__REMOVED) */
#if !defined(Divider_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define Divider_UseControl 1u
#else
    #define Divider_UseControl 0u
#endif /* !defined(Divider_PWMUDB_sCTRLReg_ctrlreg__REMOVED) */
#define Divider_UseOneCompareMode 1u
#define Divider_MinimumKillTime 1u
#define Divider_EnableMode 0u

#define Divider_CompareMode1SW 0u
#define Divider_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Divider__B_PWM__DISABLED 0
#define Divider__B_PWM__ASYNCHRONOUS 1
#define Divider__B_PWM__SINGLECYCLE 2
#define Divider__B_PWM__LATCHED 3
#define Divider__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Divider__B_PWM__DBMDISABLED 0
#define Divider__B_PWM__DBM_2_4_CLOCKS 1
#define Divider__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Divider__B_PWM__ONE_OUTPUT 0
#define Divider__B_PWM__TWO_OUTPUTS 1
#define Divider__B_PWM__DUAL_EDGE 2
#define Divider__B_PWM__CENTER_ALIGN 3
#define Divider__B_PWM__DITHER 5
#define Divider__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Divider__B_PWM__LESS_THAN 1
#define Divider__B_PWM__LESS_THAN_OR_EQUAL 2
#define Divider__B_PWM__GREATER_THAN 3
#define Divider__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Divider__B_PWM__EQUAL 0
#define Divider__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!Divider_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (Divider_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (Divider_UseStatus) */
            #if(Divider_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif /* (Divider_UseOneCompareMode) */
            
            /* Backup for Deadband parameters */
            #if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS || \
                Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(Divider_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (Divider_KillModeMinTime) */
            
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!Divider_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif /* (!Divider_PWMModeIsCenterAligned) */
            #if (Divider_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (Divider_UseStatus) */
            
            /* Backup for Deadband parameters */
            #if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS || \
                Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(Divider_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (Divider_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        
        /* Backup control register */
        #if(Divider_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Divider_UseControl) */
        
    #endif /* (!Divider_UsingFixedFunction) */
   
}Divider_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    Divider_Start(void) ;
void    Divider_Stop(void) ;

#if (Divider_UseStatus || Divider_UsingFixedFunction)
    void  Divider_SetInterruptMode(uint8 interruptMode) ;
    uint8 Divider_ReadStatusRegister(void) ;
#endif /* (Divider_UseStatus || Divider_UsingFixedFunction) */

#define Divider_GetInterruptSource() Divider_ReadStatusRegister()

#if (Divider_UseControl)
    uint8 Divider_ReadControlRegister(void) ; 
    void  Divider_WriteControlRegister(uint8 control) ;
#endif /* (Divider_UseControl) */

#if (Divider_UseOneCompareMode)
   #if (Divider_CompareMode1SW)
       void    Divider_SetCompareMode(uint8 comparemode) ;
   #endif /* (Divider_CompareMode1SW) */
#else
    #if (Divider_CompareMode1SW)
        void    Divider_SetCompareMode1(uint8 comparemode) ;
    #endif /* (Divider_CompareMode1SW) */
    #if (Divider_CompareMode2SW)
        void    Divider_SetCompareMode2(uint8 comparemode) ;
    #endif /* (Divider_CompareMode2SW) */
#endif /* (Divider_UseOneCompareMode) */

#if (!Divider_UsingFixedFunction)
    uint16   Divider_ReadCounter(void) ;
    uint16 Divider_ReadCapture(void) ;
    
	#if (Divider_UseStatus)
	        void Divider_ClearFIFO(void) ;
	#endif /* (Divider_UseStatus) */

    void    Divider_WriteCounter(uint16 counter) ;
#endif /* (!Divider_UsingFixedFunction) */

void    Divider_WritePeriod(uint16 period) ;
uint16 Divider_ReadPeriod(void) ;

#if (Divider_UseOneCompareMode)
    void    Divider_WriteCompare(uint16 compare) ;
    uint16 Divider_ReadCompare(void) ; 
#else
    void    Divider_WriteCompare1(uint16 compare) ;
    uint16 Divider_ReadCompare1(void) ; 
    void    Divider_WriteCompare2(uint16 compare) ;
    uint16 Divider_ReadCompare2(void) ; 
#endif /* (Divider_UseOneCompareMode) */


#if (Divider_DeadBandUsed)
    void    Divider_WriteDeadTime(uint8 deadtime) ;
    uint8   Divider_ReadDeadTime(void) ;
#endif /* (Divider_DeadBandUsed) */

#if ( Divider_KillModeMinTime)
    void Divider_WriteKillTime(uint8 killtime) ;
    uint8 Divider_ReadKillTime(void) ; 
#endif /* ( Divider_KillModeMinTime) */

void Divider_Init(void) ;
void Divider_Enable(void) ;
void Divider_Sleep(void) ;
void Divider_Wakeup(void) ;
void Divider_SaveConfig(void) ;
void Divider_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Divider_INIT_PERIOD_VALUE        1u
#define Divider_INIT_COMPARE_VALUE1      1u
#define Divider_INIT_COMPARE_VALUE2      63u
#define Divider_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << Divider_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << Divider_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << Divider_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << Divider_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Divider_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << Divider_CTRL_CMPMODE2_SHIFT)
#define Divider_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << Divider_CTRL_CMPMODE1_SHIFT)
#define Divider_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (Divider_UsingFixedFunction)
   #define Divider_PERIOD_LSB          (*(reg16 *) Divider_PWMHW__PER0)
   #define Divider_PERIOD_LSB_PTR      ( (reg16 *) Divider_PWMHW__PER0)
   #define Divider_COMPARE1_LSB        (*(reg16 *) Divider_PWMHW__CNT_CMP0)
   #define Divider_COMPARE1_LSB_PTR    ( (reg16 *) Divider_PWMHW__CNT_CMP0)
   #define Divider_COMPARE2_LSB        0x00u
   #define Divider_COMPARE2_LSB_PTR    0x00u
   #define Divider_COUNTER_LSB         (*(reg16 *) Divider_PWMHW__CNT_CMP0)
   #define Divider_COUNTER_LSB_PTR     ( (reg16 *) Divider_PWMHW__CNT_CMP0)
   #define Divider_CAPTURE_LSB         (*(reg16 *) Divider_PWMHW__CAP0)
   #define Divider_CAPTURE_LSB_PTR     ( (reg16 *) Divider_PWMHW__CAP0)
   #define Divider_RT1                 (*(reg8 *)  Divider_PWMHW__RT1)
   #define Divider_RT1_PTR             ( (reg8 *)  Divider_PWMHW__RT1)
      
#else
   #if (Divider_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(Divider_PWMModeIsCenterAligned)
	       #define Divider_PERIOD_LSB      (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
	       #define Divider_PERIOD_LSB_PTR   ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #else
	       #define Divider_PERIOD_LSB      (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__F0_REG)
	       #define Divider_PERIOD_LSB_PTR   ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__F0_REG)
	   #endif /* (Divider_PWMModeIsCenterAligned) */
	   
	   #define Divider_COMPARE1_LSB    (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D0_REG)
	   #define Divider_COMPARE1_LSB_PTR ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D0_REG)
	   #define Divider_COMPARE2_LSB    (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #define Divider_COMPARE2_LSB_PTR ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #define Divider_COUNTERCAP_LSB   (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__A1_REG)
	   #define Divider_COUNTERCAP_LSB_PTR ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__A1_REG)
	   #define Divider_COUNTER_LSB     (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__A0_REG)
	   #define Divider_COUNTER_LSB_PTR  ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__A0_REG)
	   #define Divider_CAPTURE_LSB     (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__F1_REG)
	   #define Divider_CAPTURE_LSB_PTR  ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(Divider_PWMModeIsCenterAligned)
		       #define Divider_PERIOD_LSB      (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
		       #define Divider_PERIOD_LSB_PTR   ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #else
		       #define Divider_PERIOD_LSB      (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__F0_REG)
		       #define Divider_PERIOD_LSB_PTR   ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__F0_REG)
		    #endif /* (Divider_PWMModeIsCenterAligned) */
		   
		    #define Divider_COMPARE1_LSB    (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D0_REG)
		    #define Divider_COMPARE1_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D0_REG)
		    #define Divider_COMPARE2_LSB    (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #define Divider_COMPARE2_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #define Divider_COUNTERCAP_LSB   (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__A1_REG)
		    #define Divider_COUNTERCAP_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__A1_REG)
		    #define Divider_COUNTER_LSB     (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__A0_REG)
		    #define Divider_COUNTER_LSB_PTR  ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__A0_REG)
		    #define Divider_CAPTURE_LSB     (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__F1_REG)
		    #define Divider_CAPTURE_LSB_PTR  ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__F1_REG)
		#else
			#if(Divider_PWMModeIsCenterAligned)
		       #define Divider_PERIOD_LSB      (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		       #define Divider_PERIOD_LSB_PTR   ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define Divider_PERIOD_LSB      (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
		       #define Divider_PERIOD_LSB_PTR   ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (Divider_PWMModeIsCenterAligned) */
		   
		    #define Divider_COMPARE1_LSB    (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
		    #define Divider_COMPARE1_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
		    #define Divider_COMPARE2_LSB    (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #define Divider_COMPARE2_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #define Divider_COUNTERCAP_LSB   (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
		    #define Divider_COUNTERCAP_LSB_PTR ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
		    #define Divider_COUNTER_LSB     (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
		    #define Divider_COUNTER_LSB_PTR  ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
		    #define Divider_CAPTURE_LSB     (*(reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
		    #define Divider_CAPTURE_LSB_PTR  ((reg16 *) Divider_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define Divider_AUX_CONTROLDP1    (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Divider_AUX_CONTROLDP1_PTR  ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Divider_Resolution == 8) */
   
   #define Divider_AUX_CONTROLDP0      (*(reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Divider_AUX_CONTROLDP0_PTR  ((reg8 *) Divider_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Divider_UsingFixedFunction) */
   
#if(Divider_KillModeMinTime )
    #define Divider_KILLMODEMINTIME      (*(reg8 *) Divider_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Divider_KILLMODEMINTIME_PTR   ((reg8 *) Divider_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Divider_KillModeMinTime ) */

#if(Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS)
    #define Divider_DEADBAND_COUNT      (*(reg8 *) Divider_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Divider_DEADBAND_COUNT_PTR  ((reg8 *) Divider_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Divider_DEADBAND_LSB_PTR    ((reg8 *) Divider_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Divider_DEADBAND_LSB        (*(reg8 *) Divider_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Divider_DeadBandMode == Divider__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Divider_UsingFixedFunction)
        #define Divider_DEADBAND_COUNT        (*(reg8 *) Divider_PWMHW__CFG0) 
        #define Divider_DEADBAND_COUNT_PTR     ((reg8 *) Divider_PWMHW__CFG0)
        #define Divider_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Divider_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Divider_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Divider_DEADBAND_COUNT        (*(reg8 *) Divider_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define Divider_DEADBAND_COUNT_PTR     ((reg8 *) Divider_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define Divider_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Divider_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define Divider_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (Divider_UsingFixedFunction) */
#endif /* (Divider_DeadBandMode == Divider__B_PWM__DBM_256_CLOCKS) */



#if (Divider_UsingFixedFunction)
    #define Divider_STATUS                (*(reg8 *) Divider_PWMHW__SR0)
    #define Divider_STATUS_PTR            ((reg8 *) Divider_PWMHW__SR0)
    #define Divider_STATUS_MASK           (*(reg8 *) Divider_PWMHW__SR0)
    #define Divider_STATUS_MASK_PTR       ((reg8 *) Divider_PWMHW__SR0)
    #define Divider_CONTROL               (*(reg8 *) Divider_PWMHW__CFG0)
    #define Divider_CONTROL_PTR           ((reg8 *) Divider_PWMHW__CFG0)    
    #define Divider_CONTROL2              (*(reg8 *) Divider_PWMHW__CFG1)    
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define Divider_CONTROL3              (*(reg8 *) Divider_PWMHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Divider_GLOBAL_ENABLE         (*(reg8 *) Divider_PWMHW__PM_ACT_CFG)
    #define Divider_GLOBAL_ENABLE_PTR       ( (reg8 *) Divider_PWMHW__PM_ACT_CFG)
    #define Divider_GLOBAL_STBY_ENABLE      (*(reg8 *) Divider_PWMHW__PM_STBY_CFG)
    #define Divider_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) Divider_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Divider_BLOCK_EN_MASK          Divider_PWMHW__PM_ACT_MSK
    #define Divider_BLOCK_STBY_EN_MASK     Divider_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define Divider_CTRL_ENABLE_SHIFT      0x00u
    
    #if(CY_PSOC5A)
        #define Divider_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define Divider_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    #define Divider_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define Divider_CFG0_MODE              0x02u   /*  Set to compare mode */
    /* #define Divider_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define Divider_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define Divider_CTRL_ENABLE            (uint8)((uint8)0x01u << Divider_CTRL_ENABLE_SHIFT)
    #define Divider_CTRL_RESET             (uint8)((uint8)0x01u << Divider_CTRL_RESET_SHIFT)
    #define Divider_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Divider_CTRL_CMPMODE2_SHIFT)
    #if(CY_PSOC5A)
        #define Divider_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Divider_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define Divider_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Divider_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Divider_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define Divider_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Divider_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define Divider_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define Divider_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define Divider_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define Divider_STATUS_TC_INT_EN_MASK_SHIFT            (Divider_STATUS_TC_SHIFT - 4u)
    #define Divider_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define Divider_STATUS_CMP1_INT_EN_MASK_SHIFT          (Divider_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define Divider_STATUS_TC              (uint8)((uint8)0x01u << Divider_STATUS_TC_SHIFT)
    #define Divider_STATUS_CMP1            (uint8)((uint8)0x01u << Divider_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define Divider_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Divider_STATUS_TC >> 4u)
    #define Divider_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Divider_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP*/
    #define Divider_RT1_SHIFT             0x04u
    #define Divider_RT1_MASK              (uint8)((uint8)0x03u << Divider_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define Divider_SYNC                  (uint8)((uint8)0x03u << Divider_RT1_SHIFT)
    #define Divider_SYNCDSI_SHIFT         0x00u
    #define Divider_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Divider_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define Divider_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Divider_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define Divider_STATUS                (*(reg8 *) Divider_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define Divider_STATUS_PTR            ((reg8 *) Divider_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define Divider_STATUS_MASK           (*(reg8 *) Divider_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define Divider_STATUS_MASK_PTR       ((reg8 *) Divider_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define Divider_STATUS_AUX_CTRL       (*(reg8 *) Divider_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Divider_CONTROL               (*(reg8 *) Divider_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Divider_CONTROL_PTR           ((reg8 *) Divider_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define Divider_CTRL_ENABLE_SHIFT      0x07u
    #define Divider_CTRL_RESET_SHIFT       0x06u
    #define Divider_CTRL_CMPMODE2_SHIFT    0x03u
    #define Divider_CTRL_CMPMODE1_SHIFT    0x00u
    #define Divider_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define Divider_CTRL_ENABLE            (uint8)((uint8)0x01u << Divider_CTRL_ENABLE_SHIFT)
    #define Divider_CTRL_RESET             (uint8)((uint8)0x01u << Divider_CTRL_RESET_SHIFT)
    #define Divider_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Divider_CTRL_CMPMODE2_SHIFT)
    #define Divider_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Divider_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define Divider_STATUS_KILL_SHIFT          0x05u
    #define Divider_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define Divider_STATUS_FIFOFULL_SHIFT      0x03u  
    #define Divider_STATUS_TC_SHIFT            0x02u
    #define Divider_STATUS_CMP2_SHIFT          0x01u
    #define Divider_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Divider_STATUS_KILL_INT_EN_MASK_SHIFT          Divider_STATUS_KILL_SHIFT          
    #define Divider_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    Divider_STATUS_FIFONEMPTY_SHIFT    
    #define Divider_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      Divider_STATUS_FIFOFULL_SHIFT        
    #define Divider_STATUS_TC_INT_EN_MASK_SHIFT            Divider_STATUS_TC_SHIFT            
    #define Divider_STATUS_CMP2_INT_EN_MASK_SHIFT          Divider_STATUS_CMP2_SHIFT          
    #define Divider_STATUS_CMP1_INT_EN_MASK_SHIFT          Divider_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define Divider_STATUS_KILL            (uint8)((uint8)0x00u << Divider_STATUS_KILL_SHIFT )
    #define Divider_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Divider_STATUS_FIFOFULL_SHIFT)
    #define Divider_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Divider_STATUS_FIFONEMPTY_SHIFT)
    #define Divider_STATUS_TC              (uint8)((uint8)0x01u << Divider_STATUS_TC_SHIFT)
    #define Divider_STATUS_CMP2            (uint8)((uint8)0x01u << Divider_STATUS_CMP2_SHIFT) 
    #define Divider_STATUS_CMP1            (uint8)((uint8)0x01u << Divider_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Divider_STATUS_KILL_INT_EN_MASK            Divider_STATUS_KILL
    #define Divider_STATUS_FIFOFULL_INT_EN_MASK        Divider_STATUS_FIFOFULL
    #define Divider_STATUS_FIFONEMPTY_INT_EN_MASK      Divider_STATUS_FIFONEMPTY
    #define Divider_STATUS_TC_INT_EN_MASK              Divider_STATUS_TC
    #define Divider_STATUS_CMP2_INT_EN_MASK            Divider_STATUS_CMP2
    #define Divider_STATUS_CMP1_INT_EN_MASK            Divider_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define Divider_AUX_CTRL_FIFO0_CLR     0x01u
    #define Divider_AUX_CTRL_FIFO1_CLR     0x02u
    #define Divider_AUX_CTRL_FIFO0_LVL     0x04u
    #define Divider_AUX_CTRL_FIFO1_LVL     0x08u
    #define Divider_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* Divider_UsingFixedFunction */

#endif  /* CY_PWM_Divider_H */


/* [] END OF FILE */
