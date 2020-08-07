/**
 * Copyright (c) 2019-2020 T2T Inc. All rights reserved.
 */

#ifndef __TTLIB_UTIL_HEXIFY_HEADER__
#define __TTLIB_UTIL_HEXIFY_HEADER__

#ifdef __cplusplus
extern "C"
{
#endif

/*-------------------------------------------------------------------------*/
/* Include Headers                                                         */
/*-------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/*-------------------------------------------------------------------------*/
/* Configurable Marcos                                                     */
/*-------------------------------------------------------------------------*/

#if 0
/**
 * The maximum size of line buffer for input.
 */
#ifndef MCS4U_CONST_MAX_INPUT_LINE_BUFFER_SIZE
#define MCS4U_CONST_MAX_INPUT_LINE_BUFFER_SIZE (256)
#endif

/**
 * The maximum size of line buffer for output.
 */
#ifndef MCS4U_CONST_MAX_OUTPUT_LINE_BUFFER_SIZE
#define MCS4U_CONST_MAX_OUTPUT_LINE_BUFFER_SIZE (256)
#endif


/**
 * The number of bytes to represent the PID (packet identity).
 */
#ifndef MCS4U_CONST_PACKET_ID_BYTES
#define MCS4U_CONST_PACKET_ID_BYTES (2)
#endif
#endif

/*-------------------------------------------------------------------------*/
/* Constant Marcos                                                         */
/*-------------------------------------------------------------------------*/

/**
 * The operation is done successfully.
 */
#define HEXIFY_RET_OKAY (0)


/*-------------------------------------------------------------------------*/
/* Types and Structures                                                    */
/*-------------------------------------------------------------------------*/

/**
 * @brief Callback function for hexify() to print out hexadecimal string every 16 bytes
 * 
 * @param   ctx         the context for the printout task
 * @param   ptr         the pointer to the data buffer to be hexified; treated as
 *                      unique task id for the call to hexify().
 * @param   times       the number of times of output the hexadecimal string for 16 bytes
 * @param   string      the hexadecimal string to be output, converted from 
 */
typedef void (* hexify_printout) (void *ctx, void *ptr, int times, char *string);


/*-------------------------------------------------------------------------*/
/* Global Function Prototypes                                              */
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
const char* ttlib_util_byte2hex(uint8_t c, bool lowercase, char tailing);


/**
 * @brief Dump memory buffer in hex.
 * 
 * @param ptr       the pointer of data buffer to be dumped
 * @param count     the number of bytes in the data buffer
 * @param printout  the callback function to print out the dump info every 16 bytes
 * @param ctx       the context to be passed when calling printout callback function
 * @return int      `0` is okay. Non-zero is error.
 */
int ttlib_util_hexify(void *ptr, size_t count, hexify_printout printout, void *ctx);


#ifdef __cplusplus
}
#endif

#endif /* __TTLIB_UTIL_HEXIFY_HEADER__ */
