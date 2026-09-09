#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		bytes[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
