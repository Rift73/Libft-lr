#include "libft.h"

static int	ft_right_overlap(const unsigned char *dst,
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

/* Copy backward only when writing forward would destroy unread source bytes. */
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
	if (ft_right_overlap(destination, source, len))
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
