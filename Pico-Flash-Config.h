/* ============================================================================================================================================================= *\
   Pico-Flash-Config.h
   St-Louys Andre - April 2024
   astlouys@gmail.com
   Revision 23-APR-2024
   Langage: C++ with arm-none-eabi

   From an original version by Raspberry Pi (Trading) Ltd.

   NOTE:
   THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
   WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
   TIME. AS A RESULT, THE AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
   INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM
   THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
   INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCT.
\* ============================================================================================================================================================= */

#ifndef __PICO_FLASH_CONFIG_H
#define __PICO_FLASH_CONFIG_H

/* $PAGE */
/* $TITLE=Include files. */
/* ============================================================================================================================================================= *\
                                                                        Include files.
\* ============================================================================================================================================================= */
#include "hardware/flash.h"
#include "hardware/irq.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"





/* $PAGE */
/* $TITLE=Definitions */
/* ============================================================================================================================================================= *\
                                                                        Definitions.
\* ============================================================================================================================================================= */
#ifndef UINT
typedef unsigned char UCHAR;
typedef int8_t        INT8;
typedef unsigned int  UINT;   // processor-optimized.
typedef uint8_t       UINT8;
typedef uint16_t      UINT16;
typedef uint32_t      UINT32;
typedef uint64_t      UINT64;
#endif


/* Define if developer or release version. */
/// #define RELEASE_VERSION
#ifdef RELEASE_VERSION
#warning ===============> Firmware Pico-Flash_Config built as RELEASE VERSION.
#else  // RELEASE_VERSION
#warning ===============> Firmware Pico-Flash_Config built as DEVELOPER VERSION.
#endif  // RELEASE_VERSION


/* Polynom used for CRC16 calculation. Different authorities use different polynoms:
   0x8005, 0x1021, 0x1DCF, 0x755B, 0x5935, 0x3D65, 0x8BB7, 0x0589, 0xC867, 0xA02B, 0x2F15, 0x6815, 0xC599, 0x202D, 0x0805, 0x1CF5 */
#define CRC16_POLYNOM           0x1021

/* Offset in Pico's 2 MB flash where to save configuration data. Starting at 2 MB flash highest limit minus 4096 bytes (0x1000) - At the very end of flash. */
#define FLASH_CONFIG_OFFSET  0x1FF000

/* Offset in Pico's 2 MB where to save more date if needed. Starting at 2 MB flash highest limit minus 2 X 4096 bytes (0x2000).
   At the end of flash, just before the above defined configuration data. */
// #define FLASH_CONFIG2_OFFSET  0x1FE000

/* RAM base address. */
#define RAM_BASE_ADDRESS  0x20000000

#define FLAG_OFF  0x00
#define FLAG_ON   0x01





/* $PAGE */
/* $TITLE=Functions prototype. */
/* ============================================================================================================================================================= *\
                                                                     Functions prototype.
\* ============================================================================================================================================================= */
/* Display flash content through external monitor. */
void flash_display(UINT32 Offset, UINT32 Length);

/* Erase configuration data in Pico's flash memory. One sector of the flash (4096 bytes - 0x1000) must be erased at a time. */
static void flash_erase(UINT32 DataOffset);

/* Extract the CRC16 from the packet passed as an argument (last 16 bits of the packet). */
UINT16 flash_extract_crc(UINT8 *Data, UINT16 DataSize);

/* Read configuration data from flash memory. */
UINT8 flash_read_config(UINT32 DataOffset, UINT8 *Data, UINT16 DataSize);

/* Save current configuration data to flash. */
UINT8 flash_save_config(UINT32 DataOffset, UINT8 *Data,  UINT16 DataSize);

/* Write configuration data to Pico's flash memory. */
static UINT8 flash_write(UINT32 DataOffset, UINT8 *NewData, UINT16 NewDataSize);

/* Send a string to external monitor through Pico's UART or CDC USB. */
extern void uart_send(UINT LineNumber, const UCHAR *FunctionName, UCHAR *Format, ...);

/* Find the cyclic redundancy check of the specified data. */
UINT16 util_crc16(UINT8 *Data, UINT16 DataSize);

/* Display binary data whose pointer is sent in argument to an external monitor. */
void util_display_data(UCHAR *Data, UINT32 DataSize);

#endif  // __PICO_FLASH_CONFIG_H
