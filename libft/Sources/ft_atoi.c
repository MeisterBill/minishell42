#include "../Includes/libft.h"

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
}

/* Reads a string, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
int	ft_atoi(const char *str)
{
	long long unsigned	nb;
	int									sign;
	long long unsigned	max;

  sign = 1;
	max = 9223372036854775807;
	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = 10 * nb + (*str - '0');
		if (nb > max && sign == 1)
			return (-1);
		if (nb > max + 1 && sign == -1)
			return (0);
		str++;
	}
	return (sign * nb);
}
