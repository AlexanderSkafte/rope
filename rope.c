#include "rope.h"
#include <string.h>

#define PHI (1.6180339887498948482)
#define LAST(A) &(A)[strlen(A)]
#define CHECK(P) do { if ((P) == NULL) { \
			fprintf(stderr, "[!] Memory allocation failed.\n"); \
			return NULL; } } while (0);

typedef struct {
	size_t	len;	// 8 bytes ; length of the string
	size_t	cap;	// 8 bytes ; capacity of the string
	char	buf[];	// 0 bytes
} rope_t;

typedef enum {
	POS_FIRST,
	POS_LAST,
} position_t;

static inline rope_t* getrope(const char*);
static inline char* rope_insert(char* str, const char* more, position_t pos);

char* rope_new(const char* str)
{
	size_t	len;
	rope_t*	r;

	len	= str ? strlen(str) : 0;
	r	= calloc(1, sizeof(*r) + len + 1);
	CHECK(r);

	r->len = len;
	r->cap = len;

	if (len > 0)
		memcpy(r->buf, str, len);

	r->buf[len] = '\0';

	return r->buf;
}

void rope_free(const char* str)
{
	if (str != NULL)
		free(getrope(str));
}

char* rope_prepend(char* str, const char* more)
{
	return rope_insert(str, more, POS_FIRST);
}

char* rope_append(char* str, const char* more)
{
	return rope_insert(str, more, POS_LAST);
}

void rope_info(const char* str)
{
	printf("\"%s\": { len = %zu, cap = %zu }\n",
			str, ropelen(str), ropecap(str));
}

size_t ropelen(const char* str)
{
	return getrope(str)->len;
}

size_t ropecap(const char* str)
{
	return getrope(str)->cap;
}

/*------------------------------------------------------------------------------
 * 	Get a pointer to the beginning of the rope_t struct that `str` is
 * 	associated with.
 *----------------------------------------------------------------------------*/
static inline rope_t* getrope(const char* str)
{
	rope_t* r = (void*) (str - sizeof(*r));
	return r;
}

static inline char* rope_insert(char* str, const char* more, position_t pos)
{
	rope_t*	r;
	size_t	newlen;
	size_t	newcap;

	const char* where =	  pos == POS_FIRST	? "prepend"
				: pos == POS_LAST	? "append" : "???";

	if (str == NULL) {
		fprintf(stderr,
			"[!] rope_%s: (arg #1): No string to %s.\n",
			where, where);
		return NULL;
	}

	if (more == NULL) {
		return str;
	}

	r	= getrope(str);
	newlen	= r->len + strlen(more);
	newcap	= r->cap == 0
			? strlen(more)
			: r->cap;

	while (newcap < newlen) {
		newcap *= PHI;
	}

	if (newlen > r->cap) {
		r = realloc(r, sizeof(*r) + newcap + 1);
		if (r == NULL) {
			fprintf(stderr, "[!] rope_%s: Realloc failed.\n",
				where);
			return str;
		}
	}

	r->len = newlen;
	r->cap = newcap;

	if (pos == POS_FIRST)
	{
		/* Buffer to hold the original string */
		char buffer[strlen(r->buf) + 1];

		/* Copy the original string to the buffer */
		memcpy(buffer, r->buf, strlen(r->buf) + 1);

		/* Write the new string to the beginning of the original one */
		memcpy(r->buf, more, strlen(more));

		/* Write the original string to the end of the new string */
		memcpy(&r->buf[strlen(more)], buffer, strlen(buffer));

		/* 0-terminate the string */
		r->buf[strlen(r->buf)] = '\0';

	}
	else if (pos == POS_LAST)
	{
		memcpy(&r->buf[strlen(r->buf)], more, strlen(more));
		r->buf[strlen(r->buf)] = '\0';
	}
	else
	{
		fprintf(stderr, "[!] Implementation error in `rope_insert`.\n");
		exit(1);
	}

	return r->buf;
}





#define ROPE_XPEND(X)							       \
	rope_t*	r;							       \
	size_t	newlen;							       \
	size_t	newcap;							       \
									       \
	if (str == NULL) {						       \
		fprintf(stderr,						       \
			"[!] rope_#X: (arg #1): No string to #X.\n");	       \
		return NULL;						       \
	}								       \
									       \
	if (more == NULL) {						       \
		return str;						       \
	}								       \
									       \
	r	= getrope(str);						       \
	newlen	= r->len + strlen(more);				       \
	newcap	= r->cap == 0						       \
			? strlen(more)					       \
			: r->cap;					       \
									       \
	while (newcap < newlen) {					       \
		newcap *= PHI;						       \
	}								       \
									       \
	if (newlen > r->cap) {						       \
		r = realloc(r, sizeof(*r) + newcap + 1);		       \
		if (r == NULL) {					       \
			fprintf(stderr, "[!] rope_#X: Realloc failed.\n");     \
			return str;					       \
		}							       \
	}								       \
									       \
	r->len = newlen;						       \
	r->cap = newcap;

