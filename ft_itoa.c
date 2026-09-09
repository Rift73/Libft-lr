#include "libft.h"
#include <stdlib.h>

static size_t	ft_digit_count(unsigned int number)
{
	size_t	count;

	count = 1;
	while (number >= 10)
	{
		number /= 10;
		count++;
	}
	return (count);
}

/* Unsigned subtraction gets INT_MIN's magnitude without signed overflow. */
char	*ft_itoa(int n)
{
	char			*text;
	unsigned int	number;
	size_t			length;

	number = (unsigned int)n;
	if (n < 0)
		number = 0 - number;
	length = ft_digit_count(number) + (n < 0);
	text = malloc(length + 1);
	if (text == NULL)
		return (NULL);
	text[length] = '\0';
	if (n < 0)
		text[0] = '-';
	while (length > (size_t)(n < 0))
	{
		length--;
		text[length] = (char)('0' + number % 10);
		number /= 10;
	}
	return (text);
}
