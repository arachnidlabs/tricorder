/*******************************************************************************
* File Name: Freebooter.h
* Version 1.0
*
*  Description:
*   Provides an API for the Bootloader. The API includes functions for starting
*   boot loading operations, validating the application and jumping to the
*   application.
*
********************************************************************************
* Portions of this code are copyright (c) 2013 Nick Johnson.
* Portions of this code are copyright (c) 2013 Cypress Semiconductor Corporation.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#if !defined(CY_BOOTLOADER_Freebooter_H)
#define CY_BOOTLOADER_Freebooter_H

#include "device.h"
#include <string.h>


/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Freebooter_v1_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5X) */

/* Map existing call to the instance specific one */
#define CyBtldr_Start   Freebooter_Start

#define Freebooter_DUAL_APP_BOOTLOADER        (0)
#define Freebooter_BOOTLOADER_APP_VERSION     (0)
#define Freebooter_FAST_APP_VALIDATION        (0)
#define Freebooter_PACKET_CHECKSUM_CRC        (0)
#define Freebooter_WAIT_FOR_COMMAND           (1)
#define Freebooter_WAIT_FOR_COMMAND_TIME      (200)
#define Freebooter_BOOTLOADABLE_APP_VALID     (1)

#define Freebooter_CMD_GET_FLASH_SIZE_AVAIL   (1)
#define Freebooter_CMD_ERASE_ROW_AVAIL        (1)
#define Freebooter_CMD_VERIFY_ROW_AVAIL       (1)
#define Freebooter_CMD_SYNC_BOOTLOADER_AVAIL  (1)
#define Freebooter_CMD_SEND_DATA_AVAIL        (0)

#if(0u != Freebooter_DUAL_APP_BOOTLOADER)
    #define Freebooter_CMD_GET_APP_STATUS_AVAIL   (1)
#endif  /* (0u != Freebooter_DUAL_APP_BOOTLOADER) */


/* Bootloader command responces */
#define Freebooter_ERR_KEY       (0x01u)  /* The provided key does not match the expected value          */
#define Freebooter_ERR_VERIFY    (0x02u)  /* The verification of flash failed                            */
#define Freebooter_ERR_LENGTH    (0x03u)  /* The amount of data available is outside the expected range  */
#define Freebooter_ERR_DATA      (0x04u)  /* The data is not of the proper form                          */
#define Freebooter_ERR_CMD       (0x05u)  /* The command is not recognized                               */
#define Freebooter_ERR_DEVICE    (0x06u)  /* The expected device does not match the detected device      */
#define Freebooter_ERR_VERSION   (0x07u)  /* The bootloader version detected is not supported            */
#define Freebooter_ERR_CHECKSUM  (0x08u)  /* The checksum does not match the expected value              */
#define Freebooter_ERR_ARRAY     (0x09u)  /* The flash array is not valid                                */
#define Freebooter_ERR_ROW       (0x0Au)  /* The flash row is not valid                                  */
#define Freebooter_ERR_PROTECT   (0x0Bu)  /* The flash row is protected and can not be programmed        */
#define Freebooter_ERR_APP       (0x0Cu)  /* The application is not valid and cannot be set as active    */
#define Freebooter_ERR_ACTIVE    (0x0Du)  /* The application is currently marked as active               */
#define Freebooter_ERR_UNK       (0x0Fu)  /* An unknown error occurred                                   */


/*******************************************************************************
* A common code for the Bootloader and Bootloadable
*******************************************************************************/

/* Mask used to indicate starting application */
#define Freebooter_START_APP                      0x80

 /* Mask used to indicate starting bootloader */
#define Freebooter_START_BTLDR                    0x40


#ifndef CYDEV_FLASH_BASE
    #define CYDEV_FLASH_BASE                            CYDEV_FLS_BASE
    #define CYDEV_FLASH_SIZE                            CYDEV_FLS_SIZE
#endif /* CYDEV_FLASH_BASE */


#define Freebooter_META_DATA_SIZE                 64
#define Freebooter_META_APP_CHECKSUM_OFFSET       0


#if(CY_PSOC3)

    #define Freebooter_APP_ADDRESS                uint16
    #define Freebooter_GET_CODE_DATA(idx)         *((uint8  CYCODE *) idx)
    #define Freebooter_GET_CODE_WORD(idx)         *((uint32 CYCODE *) idx)

    /* Offset by 2 from 32 bit start because only need 16 bits */
    #define Freebooter_META_APP_ADDR_OFFSET           3       /* 2 bytes */
    #define Freebooter_META_APP_BL_LAST_ROW_OFFSET    7       /* 4 bytes */
    #define Freebooter_META_APP_BYTE_LEN_OFFSET       11      /* 4 bytes */
    #define Freebooter_META_APP_RUN_TYPE_OFFSET       15      /* 1 byte  */

#else

    #define Freebooter_APP_ADDRESS                uint32
    #define Freebooter_GET_CODE_DATA(idx)         *((uint8  *)(CYDEV_FLASH_BASE + (idx)))
    #define Freebooter_GET_CODE_WORD(idx)         *((uint32 *)(CYDEV_FLASH_BASE + (idx)))

    #define Freebooter_META_APP_ADDR_OFFSET           1   /* 4 bytes */
    #define Freebooter_META_APP_BL_LAST_ROW_OFFSET    5   /* 4 bytes */
    #define Freebooter_META_APP_BYTE_LEN_OFFSET       9   /* 4 bytes */
    #define Freebooter_META_APP_RUN_TYPE_OFFSET       13  /* 1 byte  */

#endif /* (CY_PSOC3) */

#define Freebooter_META_APP_ACTIVE_OFFSET             16  /* 1 byte  */
#define Freebooter_META_APP_VERIFIED_OFFSET           17  /* 1 byte  */

#define Freebooter_META_APP_BL_BUILD_VER_OFFSET       18  /* 2 bytes */
#define Freebooter_META_APP_ID_OFFSET                 20  /* 2 bytes */
#define Freebooter_META_APP_VER_OFFSET                22  /* 2 bytes */
#define Freebooter_META_APP_CUST_ID_OFFSET            24  /* 4 bytes */


#if ((CYDEV_DEBUGGING_XRES) && (CY_PSOC3_ES2 || CY_PSOC5_ES1))
    #define WORKAROUND_OPT_XRES                                 1
#endif


#if(CY_PSOC4)

    extern uint8 appRunType;

    #define Freebooter_SOFTWARE_RESET CY_SET_REG32(CYREG_CM0_AIRCR, 0x05FA0004)

    #define Freebooter_GET_RUN_TYPE   (((CY_GET_REG32(CYREG_RES_CAUSE) & 0x10) > 0) \
                                            ? (CY_GET_REG8(CYDEV_SRAM_BASE + (4 * (CYINT_IRQ_BASE + NUM_INTERRUPTS)))) \
                                            : 0)

    #define Freebooter_SET_RUN_TYPE(x)         CY_SET_REG8(CYDEV_SRAM_BASE + (4 * (CYINT_IRQ_BASE + NUM_INTERRUPTS)), (x))

#else

    #define Freebooter_SOFTWARE_RESET CY_SET_REG8(CYREG_RESET_CR2, 0x01)

    #define Freebooter_GET_RUN_TYPE   (CY_GET_REG8(CYREG_RESET_SR0) & \
                                            (Freebooter_START_BTLDR | Freebooter_START_APP))

    #if defined(WORKAROUND_OPT_XRES)
        #define Freebooter_SET_RUN_TYPE(x)     Freebooter_SetFlashByte(Freebooter_MD_APP_RUN_ADDR(Freebooter_activeApp), (x))
    #else
        #define Freebooter_SET_RUN_TYPE(x)     CY_SET_REG8(CYREG_RESET_SR0, (x))
    #endif  /* defined(WORKAROUND_OPT_XRES) */

#endif  /* (CY_PSOC4) */


#define Freebooter_SetFlashRunType(runType)        Freebooter_SetFlashByte(Freebooter_MD_APP_RUN_ADDR(0), (runType))


void Freebooter_SetFlashByte(uint32 address, uint8 value) ;


/*******************************************************************************
* Metadata addresses and pointer defines
*******************************************************************************/

#define Freebooter_META_BASE(x)                 (CYDEV_FLASH_BASE + (CYDEV_FLASH_SIZE - ((x) * CYDEV_FLS_ROW_SIZE) - Freebooter_META_DATA_SIZE))
#define Freebooter_META_ARRAY                   (Freebooter_FLASH_NUMBER_SECTORS - 1)

#define Freebooter_META_APP_ENTRY_POINT_ADDR(x) (Freebooter_META_BASE(x) + Freebooter_META_APP_ADDR_OFFSET)
#define Freebooter_META_APP_BYTE_LEN(x)         (Freebooter_META_BASE(x) + Freebooter_META_APP_BYTE_LEN_OFFSET)
#define Freebooter_META_APP_RUN_ADDR(x)         (Freebooter_META_BASE(x) + Freebooter_META_APP_RUN_TYPE_OFFSET)
#define Freebooter_META_APP_ACTIVE_ADDR(x)      (Freebooter_META_BASE(x) + Freebooter_META_APP_ACTIVE_OFFSET)
#define Freebooter_META_APP_VERIFIED_ADDR(x)    (Freebooter_META_BASE(x) + Freebooter_META_APP_VERIFIED_OFFSET)
#define Freebooter_META_APP_BLDBL_VER_ADDR(x)   (Freebooter_META_BASE(x) + Freebooter_META_APP_BL_BUILD_VER_OFFSET)
#define Freebooter_META_APP_VER_ADDR(x)         (Freebooter_META_BASE(x) + Freebooter_META_APP_VER_OFFSET)
#define Freebooter_META_APP_ID_ADDR(x)          (Freebooter_META_BASE(x) + Freebooter_META_APP_ID_OFFSET)
#define Freebooter_META_APP_CUST_ID_ADDR(x)     (Freebooter_META_BASE(x) + Freebooter_META_APP_CUST_ID_OFFSET)
#define Freebooter_META_LAST_BLDR_ROW_ADDR(x)   (Freebooter_META_BASE(x) + Freebooter_META_APP_BL_LAST_ROW_OFFSET)
#define Freebooter_META_CHECKSUM_ADDR(x)        (Freebooter_META_BASE(x) + Freebooter_META_APP_CHECKSUM_OFFSET)


#if(0u == Freebooter_DUAL_APP_BOOTLOADER)

    #define Freebooter_MD_BASE                    Freebooter_META_BASE(0)
    #define Freebooter_MD_ROW                     ((FLASH_NUMBER_ROWS / Freebooter_FLASH_NUMBER_SECTORS) - 1)
    #define Freebooter_MD_CHECKSUM_ADDR           Freebooter_META_CHECKSUM_ADDR(0)
    #define Freebooter_MD_LAST_BLDR_ROW_ADDR      Freebooter_META_LAST_BLDR_ROW_ADDR(0)
    #define Freebooter_MD_APP_BYTE_LEN            Freebooter_META_APP_BYTE_LEN(0)
    #define Freebooter_MD_APP_VERIFIED_ADDR       Freebooter_META_APP_VERIFIED_ADDR(0)
    #define Freebooter_MD_APP_ENTRY_POINT_ADDR    Freebooter_META_APP_ENTRY_POINT_ADDR(0)
    #define Freebooter_MD_APP_RUN_ADDR            Freebooter_META_APP_RUN_ADDR(0)

#else

    #define Freebooter_MD_ROW(x)                  ((FLASH_NUMBER_ROWS / Freebooter_FLASH_NUMBER_SECTORS) - 1 - (x))
    #define Freebooter_MD_CHECKSUM_ADDR           Freebooter_META_CHECKSUM_ADDR(appId)
    #define Freebooter_MD_LAST_BLDR_ROW_ADDR      Freebooter_META_LAST_BLDR_ROW_ADDR(appId)
    #define Freebooter_MD_APP_BYTE_LEN            Freebooter_META_APP_BYTE_LEN(appId)
    #define Freebooter_MD_APP_VERIFIED_ADDR       Freebooter_META_APP_VERIFIED_ADDR(appId)
    #define Freebooter_MD_APP_ENTRY_POINT_ADDR    Freebooter_META_APP_ENTRY_POINT_ADDR(Freebooter_activeApp)
    #define Freebooter_MD_APP_RUN_ADDR            Freebooter_META_APP_RUN_ADDR(Freebooter_activeApp)

#endif  /* (0u == Freebooter_DUAL_APP_BOOTLOADER) */

/* Pointers to the Bootloader metadata items */
#define Freebooter_P_APP_ACTIVE(x)             ((uint8 CYCODE *)        Freebooter_META_APP_ACTIVE_ADDR(x))

#define Freebooter_MD_PTR_CHECKSUM                 ((uint8  CYCODE *)       Freebooter_MD_CHECKSUM_ADDR)
#define Freebooter_MD_PTR_APP_ENTRY_POINT          ((Freebooter_APP_ADDRESS CYCODE *) Freebooter_MD_APP_ENTRY_POINT_ADDR)
#define Freebooter_MD_PTR_LAST_BLDR_ROW            ((uint16 CYCODE *)       Freebooter_MD_LAST_BLDR_ROW_ADDR)
#define Freebooter_MD_PTR_APP_BYTE_LEN             ((Freebooter_APP_ADDRESS CYCODE *) Freebooter_MD_APP_BYTE_LEN)
#define Freebooter_MD_PTR_APP_RUN_ADDR             ((uint8  CYCODE *)        Freebooter_MD_APP_RUN_ADDR)
#define Freebooter_MD_PTR_APP_VERIFIED             ((uint8  CYCODE *)        Freebooter_MD_APP_VERIFIED_ADDR)
#define Freebooter_MD_PTR_APP_BLD_BL_VER           ((uint16 CYCODE *)       Freebooter_MD_APP_BLDBL_VER_ADDR)
#define Freebooter_MD_PTR_APP_VER                  ((uint16 CYCODE *)       Freebooter_MD_APP_VER_ADDR)
#define Freebooter_MD_PTR_APP_ID                   ((uint16 CYCODE *)       Freebooter_MD_APP_ID_ADDR)
#define Freebooter_MD_PTR_APP_CUST_ID              ((uint32 CYCODE *)       Freebooter_MD_APP_CUST_ID_ADDR)

typedef uint8 (*Freebooter_command_handler)(uint8, uint8[], uint16, uint16*);

/*******************************************************************************
* External References
*******************************************************************************/
extern void LaunchApp(uint32 addr);
extern void Freebooter_Start(void) CYSMALL ;
extern void Freebooter_LaunchApplication(void) CYSMALL ;
extern void Freebooter_SetCustomCommandHandler(Freebooter_command_handler);
extern void Freebooter_HostLink(uint8 TimeOut) ;

#if(1u == Freebooter_DUAL_APP_BOOTLOADER)

    extern cystatus Freebooter_ValidateApp(uint8 appId) CYSMALL ;
    #define Freebooter_ValidateApplication()   Freebooter_ValidateApp(0)

#else

    extern cystatus Freebooter_ValidateApplication(void) CYSMALL ;
    #define Freebooter_ValidateApp(x) Freebooter_ValidateApplication()

#endif  /* (1u == Freebooter_DUAL_APP_BOOTLOADER) */


/* If using custom interface as the IO Component, user must provide these functions */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == Freebooter_Custom_Interface)

    extern void CyBtldrCommStart(void);
    extern void CyBtldrCommStop (void);
    extern void CyBtldrCommReset(void);
    extern cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut);
    extern cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut);

#endif  /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == Freebooter_Custom_Interface) */

#endif /* CY_BOOTLOADER_Freebooter_H */


/* [] END OF FILE */
