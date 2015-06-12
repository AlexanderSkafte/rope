#ifndef ROPE_H
#define ROPE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------------
 *	A "rope" is simply a char pointer. The caller does not need to know this
 *	though.
 *----------------------------------------------------------------------------*/
typedef char* rope;

/*------------------------------------------------------------------------------
 *	Create a new rope from `str` and return a pointer to the newly created
 *	string. The returned string is always 0-terminated.
 *----------------------------------------------------------------------------*/
char* rope_new (const char* str);

/*------------------------------------------------------------------------------
 *	Free the rope unless `str` is equal to NULL; then nothing is done.
 *----------------------------------------------------------------------------*/
void rope_free (const char* str);

/*------------------------------------------------------------------------------
 *	Append `more` to `str`. The result is null terminated.
 *	`str` is not safe to use after this function has been called.
 *	You should always assign `str` to the return value of the function:
 *
 *		r = rope_extend(r, "Appended text");
 *----------------------------------------------------------------------------*/
char* rope_extend (char*	str,
		   const char*	more);

/*------------------------------------------------------------------------------
 *	Print the rope in the following format:
 *		"example": { len = 7, cap = <the capacity> }
 *----------------------------------------------------------------------------*/
char* rope_info (const char* str);

/*------------------------------------------------------------------------------
 *	Return the length of `str`, excluding the terminating 0-byte.
 *----------------------------------------------------------------------------*/
size_t ropelen (const char* str);

/*------------------------------------------------------------------------------
 *	Return the capacity of `str`.
 *----------------------------------------------------------------------------*/
size_t ropecap (const char* str);

#endif

