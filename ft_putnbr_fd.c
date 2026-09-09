#include "libft.h"
#include <unistd.h>

static void	ft_put_positive(long long number, int fd)
{
	char	digit;

	if (number >= 10)
		ft_put_positive(number / 10, fd);
	digit = (char)('0' + number % 10);
	write(fd, &digit, 1);
}

/* Widen before negating so INT_MIN has a representable positive magnitude. */
void	ft_putnbr_fd(int n, int fd)
{
	long long	number;

	number = (long long)n;
	if (number < 0)
	{
		write(fd, "-", 1);
		number = -number;
	}
	ft_put_positive(number, fd);
}
