/*******************************************************************************
* File Name: BoostConv.h
* Version 4.0
*
* Description:
*  This header file provides registers and constants associated with the
*  Boost component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOST_BoostConv_H)
#define CY_BOOST_BoostConv_H

#include "cyfitter.h"
#include "cydevice_trm.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component BoostConv_v4_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 BoostConv_initVar;


/***************************************
*     Data Struct Definitions
***************************************/

/* Chip Sleep Mode API Support */
typedef struct
{
    uint8 selVoltage;
    uint8 mode;
} BoostConv_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  BoostConv_Init(void) ;
void  BoostConv_Start(void) ;
void  BoostConv_Stop(void) ;
void  BoostConv_Enable(void) ;
void  BoostConv_Disable(void) ;
void  BoostConv_SetMode(uint8 mode) ;
void  BoostConv_SelVoltage(uint8 voltage) ;
void  BoostConv_ManualThump(void) ;
uint8 BoostConv_ReadStatus(void);
void  BoostConv_EnableInt(void) ;
void  BoostConv_DisableInt(void) ;
uint8 BoostConv_ReadIntStatus(void) ;

#if (CY_PSOC3)
    void  BoostConv_EnableAutoThump(void) ;
    void  BoostConv_DisableAutoThump(void) ;
    void  BoostConv_SelFreq(uint8 frequency) ;
    void  BoostConv_SelExtClk(uint8 source) ;
#endif /* CY_PSOC3 */


/***************************************
*         API Constants
***************************************/

/* Constants for SetMode function */

#define BoostConv_BOOSTMODE_ACTIVE       (0x03u)
#if (CY_PSOC3)
    #define BoostConv_BOOSTMODE_STANDBY  (0x01u)
#endif /* CY_PSOC3 */
#if (CY_PSOC5LP)
    #define BoostConv_BOOSTMODE_SLEEP    (0x00u)
#endif /* CY_PSOC5LP */

/* Constants for SelVoltage function */

#define BoostConv_VOUT_OFF               (0x00u)
#define BoostConv_VOUT_1_8V              (0x03u)
#define BoostConv_VOUT_1_9V              (0x04u)
#define BoostConv_VOUT_2_0V              (0x05u)
#define BoostConv_VOUT_2_1V              (0x06u)
#define BoostConv_VOUT_2_2V              (0x07u)
#define BoostConv_VOUT_2_3V              (0x08u)
#define BoostConv_VOUT_2_4V              (0x09u)
#define BoostConv_VOUT_2_5V              (0x0Au)
#define BoostConv_VOUT_2_6V              (0x0Bu)
#define BoostConv_VOUT_2_7V              (0x0Cu)
#define BoostConv_VOUT_2_8V              (0x0Du)
#define BoostConv_VOUT_2_9V              (0x0Eu)
#define BoostConv_VOUT_3_0V              (0x0Fu)
#define BoostConv_VOUT_3_1V              (0x10u)
#define BoostConv_VOUT_3_2V              (0x11u)
#define BoostConv_VOUT_3_3V              (0x12u)
#define BoostConv_VOUT_3_4V              (0x13u)
#define BoostConv_VOUT_3_5V              (0x14u)
#define BoostConv_VOUT_3_6V              (0x15u)
#define BoostConv_VOUT_4_0V              (0x16u)
#define BoostConv_VOUT_4_25V             (0x17u)
#define BoostConv_VOUT_4_5V              (0x18u)
#define BoostConv_VOUT_4_75V             (0x19u)
#define BoostConv_VOUT_5_0V              (0x1Au)
#define BoostConv_VOUT_5_25V             (0x1Bu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

/* Enumerated Types Boost_Frequency, Used in parameter Frequency */
#define BoostConv__SWITCH_FREQ_400KHZ    (1u)
#if (CY_PSOC3)
    #define BoostConv__SWITCH_FREQ_32KHZ (3u)
#endif /* CY_PSOC3 */

#if (CY_PSOC3)
    /* Enumerated Types Boost_ExtClk_Source, Used in parameter ExtClk_Source */
    #define BoostConv__EXTCLK_ECO 1
#define BoostConv__EXTCLK_ILO 2
#define BoostConv__EXTCLK_NONE 0

#endif /* CY_PSOC3 */


/***************************************
*      Initial Parameter Constants
***************************************/

#define BoostConv_INIT_VOUT              (26u)
#define BoostConv_FREQUENCY              (1u)
#define BoostConv_DISABLE_AUTO_BATTERY   (0u)

#if (CY_PSOC3)
    #define BoostConv_EXTCLK_SRC         (0u)
#endif /* CY_PSOC3 */


/***************************************
*             Registers
***************************************/

#define BoostConv_CONTROL_REG0           (* (reg8*) CYREG_BOOST_CR0)
#define BoostConv_CONTROL_REG0_PTR       (  (reg8*) CYREG_BOOST_CR0)
#define BoostConv_CONTROL_REG1           (* (reg8*) CYREG_BOOST_CR1)
#define BoostConv_CONTROL_REG1_PTR       (  (reg8*) CYREG_BOOST_CR1)
#define BoostConv_CONTROL_REG2           (* (reg8*) CYREG_BOOST_CR2)
#define BoostConv_CONTROL_REG2_PTR       (  (reg8*) CYREG_BOOST_CR2)
#define BoostConv_CONTROL_REG3           (* (reg8*) CYREG_BOOST_CR3)
#define BoostConv_CONTROL_REG3_PTR       (  (reg8*) CYREG_BOOST_CR3)
#define BoostConv_STATUS_REG             (* (reg8*) CYREG_BOOST_SR)
#define BoostConv_STATUS_REG_PTR         (  (reg8*) CYREG_BOOST_SR)
#define BoostConv_CONTROL_REG4           (* (reg8*) CYREG_BOOST_CR4)
#define BoostConv_CONTROL_REG4_PTR       (  (reg8*) CYREG_BOOST_CR4)
#define BoostConv_STATUS_REG2            (* (reg8*) CYREG_BOOST_SR2)
#define BoostConv_STATUS_REG2_PTR        (  (reg8*) CYREG_BOOST_SR2)


/***************************************
*        Register Constants
***************************************/

/* Boost.CR0 */
#define BoostConv_VOLTAGE_SHIFT             (0x00u)
#define BoostConv_VOLTAGE_MASK              ((uint8) (0x1Fu << BoostConv_VOLTAGE_SHIFT))

#define BoostConv_MODE_SHIFT                (0x05u)
#define BoostConv_MODE_MASK                 ((uint8) (0x03u << BoostConv_MODE_SHIFT))

#define BoostConv_MANUAL_THUMP_ENABLE_SHIFT (0x07u)
#define BoostConv_MANUAL_THUMP_ENABLE       ((uint8) (0x01u << BoostConv_AUTO_THUMP_ENABLE_SHIFT))

/* Boost.CR1 */
#define BoostConv_FREQ_SHIFT                (0x00u)
#define BoostConv_FREQ_MASK                 ((uint8) (0x03u << BoostConv_FREQ_SHIFT))

#if (CY_PSOC3)
    #define BoostConv_PWMEXT_ENABLE_SHIFT   (0x02u)
    #define BoostConv_PWMEXT_ENABLE         ((uint8) (0x01u << BoostConv_PWMEXT_ENABLE_SHIFT))
#endif /* CY_PSOC3 */

#define BoostConv_BOOST_ENABLE_SHIFT        (0x03u)
#define BoostConv_BOOST_ENABLE              ((uint8) (0x01u << BoostConv_BOOST_ENABLE_SHIFT))

/* Boost.CR2 */
#define BoostConv_AUTO_THUMP_ENABLE_SHIFT   (0x00u)
#define BoostConv_AUTO_THUMP_ENABLE         ((uint8) (0x01u << BoostConv_AUTO_THUMP_ENABLE_SHIFT))

/* enables external precision 800mv referance */
#define BoostConv_PRECISION_REF_ENABLE_SHIFT (0x03u)
#define BoostConv_PRECISION_REF_ENABLE       ((uint8) (0x01u << BoostConv_PRECISION_REF_ENABLE_SHIFT))

/* disables auto battery connect to output when Vin=Vsel */
#define BoostConv_AUTO_BATTERY_DISABLE_SHIFT (0x01u)
#define BoostConv_AUTO_BATTERY_DISABLE       ((uint8) (0x01u << BoostConv_AUTO_BATTERY_DISABLE_SHIFT))

/* Boost.SR */
#define BoostConv_RDY_SHIFT                 (0x07u)
#define BoostConv_RDY                       ((uint8) (0x01u << BoostConv_RDY_SHIFT))
#define BoostConv_START_SHIFT               (0x06u)
#define BoostConv_START                     ((uint8) (0x01u << BoostConv_START_SHIFT))
#define BoostConv_OV_SHIFT                  (0x04u)
#define BoostConv_OV                        ((uint8) (0x01u << BoostConv_OV_SHIFT))
#define BoostConv_VHI_SHIFT                 (0x03u)
#define BoostConv_VHI                       ((uint8) (0x01u << BoostConv_VHI_SHIFT))
#define BoostConv_VNOM_SHIFT                (0x02u)
#define BoostConv_VNOM                      ((uint8) (0x01u << BoostConv_VNOM_SHIFT))
#define BoostConv_VLO_SHIFT                 (0x01u)
#define BoostConv_VLO                       ((uint8) (0x01u << BoostConv_VLO_SHIFT))
#define BoostConv_UV_SHIFT                  (0x00u)
#define BoostConv_UV                        ((uint8) (0x01u << BoostConv_UV_SHIFT))

/* Boost.CR4 */
#define BoostConv_INT_ENABLE_SHIFT          (0x00u)
#define BoostConv_INT_ENABLE_MASK           ((uint8) (0x01u << BoostConv_INT_ENABLE_SHIFT))

#if (CY_PSOC3)
    #define BoostConv_EXTCLK_SRC_SHIFT      (0x01u)
    #define BoostConv_EXTCLK_SRC_MASK       ((uint8) (0x03u << BoostConv_EXTCLK_SRC_SHIFT))
#endif /* CY_PSOC3 */

/* Boost.SR2 */
#define BoostConv_INT_SHIFT                 (0x00u)
#define BoostConv_INT                       ((uint8) (0x01u << BoostConv_INT_SHIFT))

/* Timing requirements of Start depends on input voltage and can be in range 100us to 10ms (for 0.5V) */
#define BoostConv_STARTUP_TIMEOUT           (10000u) /* Initial startup timeout 10 ms  */

#endif /* CY_BOOST_BoostConv_H */


/* [] END OF FILE */
