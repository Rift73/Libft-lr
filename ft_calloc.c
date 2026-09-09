#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

/*
** SIZE_MAX is the largest byte count size_t can represent. Divide first to
** check whether multiplication would wrap. A zero-size request uses one
** allocated byte so the returned pointer can still be freed.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	total;

	if (nmemb == 0 || size == 0)
		total = 1;
	else
	{
		if (nmemb > SIZE_MAX / size)
			return (NULL);
		total = nmemb * size;
	}
	memory = malloc(total);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, total);
	return (memory);
}
