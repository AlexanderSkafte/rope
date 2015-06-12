#include "rope.h"
#include <string.h>

#define PHI (1.6180339887498948482)
#define LAST(A) &(A)[strlen(A)]
#define CHECK(P) do { if ((P) == NULL) { \
			fprintf(stderr, "[!] Memory allocation failed.\n"); \
			return NULL; } } while (0);

static inline rope_t* getrope(const char*);

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

char* rope_extend(char* str, const char* more)
{
	rope_t*	r;
	size_t	oldlen;		// TODO: Redundant, remote
	size_t	oldcap;
	size_t	newlen;
	size_t	newcap;

	if (str == NULL) {
		fprintf(stderr,
			"[!] rope_extend: (arg 1): no string to extend.\n");
		return str;
	}

	if (more == NULL) { return str; }

	r	= getrope(str);
	oldlen	= r->len;
	oldcap	= r->cap;
	newlen	= oldlen + strlen(more);
	newcap	= oldcap;

	while (newcap < newlen) {
		newcap *= PHI;
	}

	if (newlen > oldcap) {
		// TODO: Do this more safely.
		r = realloc(r, sizeof(*r) + newcap + 1);
	}

	r->len = newlen;
	r->cap = newcap;
	memcpy(&r->buf[strlen(r->buf)], more, strlen(more));

	return r->buf;
}

void rope_print(const char* str)
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

void check_null(const char* str)
{
	rope_t* r = getrope(str);
	printf("Checking so that the string is null terminated:\n");
	for (int i = 0; r->buf[i] != '\0'; ++i) {
		printf("%c", r->buf[i]);
	}
	printf("<\n");
}





#if 0
bool rope_extend(rope** r, const char* str)
{
	rope*	tmp	= *r;		// if realloc fails
	char*	buf	= (*r)->buf;
	size_t	old_len	= (*r)->len;
	size_t	new_len	= old_len + strlen(str);
	char*	last;

	*r = realloc(*r, sizeof(r) + new_len + 1);

	if (*r == NULL) {
		printf(">>>realloc FAILED<<<\n");
		*r = tmp;
		return false;
	}

	(*r)->len = new_len;
	last = &buf[strlen(buf)];	// Pointer to 0-byte of r->buf
	strcpy(last, str);

	return true;
}
#endif

