#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last_match;
	unsigned char	target;

	last_match = NULL;
	target = (unsigned char)c;
	while (1)
	{
		if ((unsigned char)*s == target)
			last_match = s;
		if (*s == '\0')
			break ;
		s++;
	}
	return ((char *)last_match);
}
