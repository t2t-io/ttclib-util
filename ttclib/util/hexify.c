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

/* internal string buffer for single byte in hex format, e.g. 0x1F. Only 3 
 * bytes of the buffer is used in typical use cases, but declaring 4 bytes 
 * is because of 2 reasons:
 *      1. better performance (single uint32_t assignment better than memcpy)
 *      2. memory alignment
 */
static char m_hex_buffer[4] = {0};  

/* external string buffer for single byte in hex format, as return value
 * of `ttlib_util_byte2hex`.
 */
static char m_hex_output[4] = {0};  


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
 * @param lowercase `true` to use lowercase characters (A ~ F). `false` to use 
 *                  uppercase characters.
 * @param tailing   The tailing character of hex string. Typically, it shall be
 *                  '\0' (0x00).
 * @return char*    The pointer to the buffer with hex string. NULL indicates
 *                  the given parameters are invalid.
 */
const char* ttlib_util_byte2hex(uint8_t c, bool lowercase, char tailing)
{
    const char* hexes = lowercase ? LOWERCASE_CHARS : UPPERCASE_CHARS;
    int hsb = (c & 0xF0) >> 4;
    int lsb = (c & 0x0F) >> 0;

    m_hex_buffer[0] = hexes[hsb];
    m_hex_buffer[1] = hexes[lsb];
    m_hex_buffer[2] = tailing;
    m_hex_buffer[3] = 0;

    * ((uint32_t *) m_hex_output) = * ((uint32_t *) m_hex_buffer);
    return m_hex_output;
}

/*-------------------------------------------------------------------------*/
/* Local Functions                                                         */
/*-------------------------------------------------------------------------*/
