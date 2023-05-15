#include "../Includes/libft.h"

int	ft_nbrlen(long nb, int base)
{
	int len;

	len = 0;
	if (!base)
		base = 10;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		len++;
		nb /= base;
	}
	return (len);
}

static char	*ft_fill_str(char *str, int len, int nb, int nb_cpy)
{
	str[len] = '\0';
	while (len-- > 0)
	{
		if (len > 0 || nb_cpy >= 0)
			str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

static char *ft_allocate_str(char *str, int len, int nb, int nb_cpy)
{
	if (nb >= 0)
	{
		str = (char *)malloc(len + 1);
		if (str == NULL)
			return (NULL);
	}
	else if (nb < 0 && nb != -2147483648)
	{
		str = (char *)malloc(++len + 1);
		if (str == NULL)
			return (NULL);
		str[0] = '-';
		nb = -nb;
	}
	else
	{
		str = (char *)malloc(12);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	return (ft_fill_str(str, len, nb, nb_cpy));
}

/* Saves the given nb as a string (char array) */
char *ft_itoa(int nb)
{
	char *str;
	int len;
	int nb_cpy;

	nb_cpy = nb;
	len = ft_nbrlen(nb, 10);
	str = NULL;
	str = ft_allocate_str(str, len, nb, nb_cpy);
	if (str == NULL)
		return (NULL);
	return (str);
}
