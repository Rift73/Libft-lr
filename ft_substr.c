#include "libft.h"
#include <stdlib.h>

/* Check start before subtracting it from an unsigned length. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	source_length;

	if (s == NULL)
		return (NULL);
	source_length = ft_strlen(s);
	if ((size_t)start >= source_length)
		return (ft_strdup(""));
	if (len > source_length - (size_t)start)
		len = source_length - (size_t)start;
	substring = malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	ft_memcpy(substring, s + start, len);
	substring[len] = '\0';
	return (substring);
}
