#include "libft.h"

/* Writes n zeroes to the string s */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/* Reserves count blocks of size bits of memory */
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(sizeof(void) * count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

int	ft_countchar(char *str, char c)
{
	int count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
