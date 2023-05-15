#include "../Includes/libft.h"

/* Assigns a character n times to a part of the memory*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char		*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (s);
}
