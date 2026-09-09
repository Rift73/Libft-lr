#include "libft.h"

/* Unsigned bytes preserve ordering for values above 127. */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*left;
	const unsigned char	*right;
	size_t				i;

	left = (const unsigned char *)s1;
	right = (const unsigned char *)s2;
	i = 0;
	while (i < n && left[i] == right[i])
	{
		if (left[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	return ((int)left[i] - (int)right[i]);
}
