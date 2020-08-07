/**
 * Copyright (c) 2019-2020 T2T Inc. All rights reserved.
 */

/*=========================================================================
 *  FILE:
 *      tt_util_hexify.c
 *
 *
 *  DESCRIPTION:
 *      The helper functions to convert byte(s) to hex string(s) for data
 *      communication or debugging purposes.
 *
 *  REVISION HISTORY:
 *      2019/12/22, yagamy, initial version.
 *      2020/08/07, yagamy, rename to tt_util_hexify.c
 *
 *
 *=========================================================================*/
#define MODULE_NAME "tt_util_hexify.c"


/*-------------------------------------------------------------------------*/
/* Include Headers                                                         */
/*-------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tt_util_hexify.h"


/*-------------------------------------------------------------------------*/
/* Include Headers                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/* Macros                                                                  */
/*-------------------------------------------------------------------------*/
#define MAX_HEX_DUMP_EXTRA_BYTES                (24)
#define MAX_HEX_DUMP_LINE_BUFFER_SIZE           (8 + 2 + 3 * 16 + 2 + 1 + 16 + 1 + MAX_HEX_DUMP_EXTRA_BYTES)

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

/* line buffer for hex string to be printed out.
 */
static char m_hex_dump_line[MAX_HEX_DUMP_LINE_BUFFER_SIZE] = {0};

/* ascii string buffer for further display.
 */
static char m_hex_dump_ascii_bytes[16 + 1] = {0};

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


/**
 * @brief Dump memory buffer in hex.
 * 
 * @param ptr       the pointer of data buffer to be dumped
 * @param count     the number of bytes in the data buffer
 * @param printout  the callback function to print out the dump info every 16 bytes
 * @param ctx       the context to be passed when calling printout callback function
 * @return int      `0` is okay. Non-zero is error.
 */
int ttlib_util_hexify(void *ptr, size_t count, hexify_printout printout, void *ctx)
{
    uint8_t *data = (uint8_t *)ptr;
    uint8_t c;
    int h_offset = 0;
    int a_offset = 0;
    int counter = 0;

    if (!printout) return -1;

    printout(ctx, ptr, -1, NULL);

    while (h_offset < count) {
        int address = ((int) ptr) + h_offset;
        memset(m_hex_dump_line, 0, sizeof(m_hex_dump_line));
        sprintf(m_hex_dump_line, "%X  ", address);
        for (int i = 0; i < 8; i++) {
            if (h_offset >= count) {
                strcat(m_hex_dump_line, "   ");
                m_hex_dump_ascii_bytes[a_offset++] = ' ';
            }
            else {
                c = data[h_offset++];
                strcat(m_hex_dump_line, ttlib_util_byte2hex(c, false, ' '));
                m_hex_dump_ascii_bytes[a_offset++] = ((c >= 0x20) && (c <= 0x7F)) ? c : '.';
            }
        }

        strcat(m_hex_dump_line, " ");
        m_hex_dump_ascii_bytes[a_offset++] = ' ';
        m_hex_dump_ascii_bytes[a_offset++] = ' ';

        for (int i = 0; i < 8; i++) {
            if (h_offset >= count) {
                strcat(m_hex_dump_line, "   ");
                m_hex_dump_ascii_bytes[a_offset++] = ' ';
            }
            else {
                c = data[h_offset++];
                strcat(m_hex_dump_line, ttlib_util_byte2hex(c, false, ' '));
                m_hex_dump_ascii_bytes[a_offset++] = ((c >= 0x20) && (c <= 0x7F)) ? c : '.';
            }
        }
        strcat(m_hex_dump_line, " |");
        strcat(m_hex_dump_line, m_hex_dump_ascii_bytes);
        strcat(m_hex_dump_line, "|");
        printout(ctx, ptr, counter++, m_hex_dump_line);
        a_offset = 0;
    }

    printout(ctx, ptr, -2, NULL);
    return 0;
}


/*-------------------------------------------------------------------------*/
/* Local Functions                                                         */
/*-------------------------------------------------------------------------*/
