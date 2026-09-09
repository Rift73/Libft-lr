#include "libft.h"

/* Look for dst inside the unread source range, using pointer equality. */
static int	ft_needs_backward_copy(const unsigned char *dst,
		const unsigned char *src, size_t len)
{
	size_t	i;

	i = 1;
	while (i < len)
	{
		if (dst == src + i)
			return (1);
		i++;
	}
	return (0);
}

static void	ft_copy_backward(unsigned char *dst,
		const unsigned char *src, size_t len)
{
	while (len > 0)
	{
		len--;
		dst[len] = src[len];
	}
}

/*
** Moving five bytes of "abcdef" one place right must give "aabcde".
** A forward copy overwrites 'b' before reading it; copying backward avoids
** this. When moving left or copying separate regions, forward copying works.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*destination;
	const unsigned char	*source;
	size_t				i;

	if (dst == src || len == 0)
		return (dst);
	destination = (unsigned char *)dst;
	source = (const unsigned char *)src;
	i = 0;
	if (ft_needs_backward_copy(destination, source, len))
		ft_copy_backward(destination, source, len);
	else
	{
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dst);
}
