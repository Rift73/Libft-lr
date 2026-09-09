#include "libft.h"

/* Unsigned bytes preserve ordering for values above 127. */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*left;
	const unsigned char	*right;
	size_t				i;

	left = (const unsigned char *)s1;
	right = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (left[i] != right[i])
			return ((int)left[i] - (int)right[i]);
		i++;
	}
	return (0);
}
