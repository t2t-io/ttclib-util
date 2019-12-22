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
 * @param uppercase `true` to use uppercase characters (A ~ F). `false` to use 
 *                  lowercase characters.
 * @return char*    The pointer to the buffer with hex string. NULL indicates
 *                  the given parameters are invalid.
 */
char* ttlib_util_byte2hex(uint8_t c, bool uppercase);

#ifdef __cplusplus
}
#endif

#endif /* __TTLIB_UTIL_HEXIFY_HEADER__ */
