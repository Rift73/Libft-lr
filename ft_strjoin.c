#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	first_length;
	size_t	second_length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	first_length = ft_strlen(s1);
	second_length = ft_strlen(s2);
	if (first_length > (size_t)-1 - second_length - 1)
		return (NULL);
	joined = malloc(first_length + second_length + 1);
	if (joined == NULL)
		return (NULL);
	ft_memcpy(joined, s1, first_length);
	ft_memcpy(joined + first_length, s2, second_length + 1);
	return (joined);
}
