#include "libft.h"
#include <stdlib.h>

/* Zero needs one digit; each division by ten removes one decimal place. */
static size_t	ft_digit_count(long long number)
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

/* Remainders give the last digit first, so fill from right to left. */
static void	ft_fill_digits(char *text, long long number, size_t length)
{
	while (number >= 10)
	{
		length--;
		text[length] = (char)('0' + number % 10);
		number /= 10;
	}
	text[length - 1] = (char)('0' + number);
}

/*
** Widen before negation so the positive magnitude of INT_MIN fits on our
** 32-bit-int targets. Reserve digits, an optional sign, and a terminator.
** Filling the digits leaves the first position free when a sign is needed.
*/
char	*ft_itoa(int n)
{
	char		*text;
	long long	number;
	size_t		length;

	number = (long long)n;
	if (number < 0)
		number = -number;
	length = ft_digit_count(number);
	if (n < 0)
		length++;
	text = malloc(length + 1);
	if (text == NULL)
		return (NULL);
	text[length] = '\0';
	ft_fill_digits(text, number, length);
	if (n < 0)
		text[0] = '-';
	return (text);
}
