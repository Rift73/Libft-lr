#include "libft.h"

/* Return the full source length, even when the copy is truncated. */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	source_length;
	size_t	i;

	source_length = ft_strlen(src);
	if (dstsize == 0)
		return (source_length);
	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (source_length);
}
