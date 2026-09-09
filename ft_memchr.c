#include "libft.h"

/* Raw memory searches continue through zero bytes. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*bytes;
	unsigned char		target;
	size_t				i;

	bytes = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (bytes[i] == target)
			return ((void *)(bytes + i));
		i++;
	}
	return (NULL);
}
