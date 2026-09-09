#include "libft.h"
#include <stdlib.h>

/* The caller owns this new allocation, not an alias of the input. */
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
