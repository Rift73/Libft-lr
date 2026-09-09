#include "libft.h"
#include <stdlib.h>

/* The callback receives a value; its return goes into a new allocation. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapped;
	size_t	length;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	length = ft_strlen(s);
	mapped = malloc(length + 1);
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		mapped[i] = f((unsigned int)i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
