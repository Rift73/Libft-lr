#include "libft.h"
#include <stdlib.h>

/*
** The caller owns a separate allocation. Index length holds the terminator,
** so the <= loop copies it along with all the visible characters.
*/
char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	size_t	length;
	size_t	i;

	length = ft_strlen(s1);
	duplicate = malloc(length + 1);
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (i <= length)
	{
		duplicate[i] = s1[i];
		i++;
	}
	return (duplicate);
}
