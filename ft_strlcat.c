#include "libft.h"

/* dstsize is the whole buffer capacity, not just its remaining space. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	destination_length;
	size_t	source_length;
	size_t	i;

	destination_length = 0;
	while (destination_length < dstsize
		&& dst[destination_length] != '\0')
		destination_length++;
	source_length = ft_strlen(src);
	if (destination_length == dstsize)
		return (dstsize + source_length);
	i = 0;
	while (src[i] != '\0' && destination_length + i + 1 < dstsize)
	{
		dst[destination_length + i] = src[i];
		i++;
	}
	dst[destination_length + i] = '\0';
	return (destination_length + source_length);
}
