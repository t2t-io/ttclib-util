/**
 * Copyright (c) 2019-2020 T2T Inc. All rights reserved.
 */

/*=========================================================================
 *  FILE:
 *      ttclib/util/hexify.c
 *
 *
 *  DESCRIPTION:
 *      The helper functions to convert byte(s) to hex string(s) for data
 *      communication or debugging purposes.
 *
 *  REVISION HISTORY:
 *      2019/12/22, yagamy, initial version.
 *
 *
 *=========================================================================*/
#define MODULE_NAME "ttclib/util/hexify.c"


/*-------------------------------------------------------------------------*/
/* Include Headers                                                         */
/*-------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexify.h"


/*-------------------------------------------------------------------------*/
/* Include Headers                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Macros                                                                  */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Typedefs, Enums, and Structures                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Global Variables                                                        */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Global External Functions                                               */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Global External Variables                                               */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Local Function Prototypes                                               */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Local Constant Variables                                                */
/*-------------------------------------------------------------------------*/
static const char *LOWERCASE_CHARS = "0123456789abcdef";
static const char *UPPERCASE_CHARS = "0123456789ABCDEF";


/*-------------------------------------------------------------------------*/
/* Local Variables                                                         */
/*-------------------------------------------------------------------------*/
static char m_hex_buffer[3] = {0};


/*-------------------------------------------------------------------------*/
/* Global Functions                                                        */
/*-------------------------------------------------------------------------*/

/**
 * @brief Convert a byte (unsigned int8) to a hex string.
 * 
 * The function converts a given byte to a hex string with 2 characters.
 * Please note, the returned pointer of string buffer is not valid since
 * next time of calling the same function.
 * 
 * @param c         The given byte to be converted.
 * @param uppercase `true` to use uppercase characters (A ~ F). `false` to use 
 *                  lowercase characters.
 * @return char*    The pointer to the buffer with hex string. NULL indicates
 *                  the given parameters are invalid.
 */
char* ttlib_util_byte2hex(uint8_t c, bool uppercase)
{
    const char* hexes = uppercase ? UPPERCASE_CHARS : LOWERCASE_CHARS;
    uint8_t hsb = (uint8_t) ((c & 0xF0) >> 4);
    uint8_t lsb = c & 0x0F;

    m_hex_buffer[0] = hexes[hsb];
    m_hex_buffer[1] = hexes[lsb];
    m_hex_buffer[2] = 0;

    return m_hex_buffer;
}

/*-------------------------------------------------------------------------*/
/* Local Functions                                                         */
/*-------------------------------------------------------------------------*/
