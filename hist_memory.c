#include "shell.h"

/**
 * bfree - This frees a pointer and NULLs the address
 * @ptr: The  address of the pointer to free
 *
 * Returns: 1 when freed,else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


