#include "../Includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(sizeof(void) * count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
