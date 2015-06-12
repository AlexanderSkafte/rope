#ifndef ROPE_H
#define ROPE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* rope;

typedef struct {
	size_t	len;	// 8 bytes ; length of the string
	size_t	cap;	// 8 bytes ; capacity of the string
	char	buf[];	// 0 bytes
} rope_t;

/*------------------------------------------------------------------------------
 *	Create a new rope from `str` and return a pointer to the newly created
 *	string. The returned string is always 0-terminated.
 *----------------------------------------------------------------------------*/
char*	rope_new	(const char* str);

/*------------------------------------------------------------------------------
 *	Append `more` to `str`. The result is null terminated.
 *	`str` is not safe to use after this function has been called.
 *	You should always assign `str` to the return value of the function:
 *
 *		r = rope_extend(r, "Appended text");
 *----------------------------------------------------------------------------*/
char*	rope_extend	(char* str, const char* more);

/*------------------------------------------------------------------------------
 *	Print the rope in the following format:
 *		"example": { len = 7, cap = <the capacity> }
 *----------------------------------------------------------------------------*/
void	rope_print	(const char* str);

/*------------------------------------------------------------------------------
 *	Return the length of `str`, excluding the terminating 0-byte.
 *----------------------------------------------------------------------------*/
size_t	ropelen		(const char* str);

/*------------------------------------------------------------------------------
 *	Return the capacity of `str`.
 *----------------------------------------------------------------------------*/
size_t	ropecap		(const char* str);

//int	rope_free(rope_t* r);
void	check_null(const char* str);

#endif

