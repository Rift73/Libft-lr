#include "libft.h"
#include <stdlib.h>

/* Check multiplication before allocating; zero-size results stay freeable. */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	total;

	if (nmemb == 0 || size == 0)
		total = 1;
	else
	{
		if (nmemb > (size_t)(-1) / size)
			return (NULL);
		total = nmemb * size;
	}
	memory = malloc(total);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, total);
	return (memory);
}
