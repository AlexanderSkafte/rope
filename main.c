#include "rope.h"
#include <string.h>

#define SIZEOF(A) printf("sizeof(A) = %zu\n", sizeof(A));

int main(void)
{
	rope r = rope_new("hello");
	rope_info(r);
	rope_append(r, " there");
	rope_info(r);
	rope_prepend(r, "welcome and ");
	rope_info(r);
}
