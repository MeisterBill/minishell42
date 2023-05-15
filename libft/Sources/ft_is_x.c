#include "../Includes/libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int ft_isalpha(int c)
{
	return ((c > 64 && c < 91) || (c > 96 && c < 123));
}

int ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

