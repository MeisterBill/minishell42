#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

int	ft_putendl_fd(char *str, int fd)
{
	if (str != NULL)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen(str) + 1);
	}
	return (0);
}

int	ft_putstr_fd(char *str, int fd)
{
	if (str != NULL)
		return ((int)write(fd, str, ft_strlen(str)));
	return (0);
}

int	ft_putmatrix_fd(char **matrix, int nl, int fd)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (matrix && matrix[i])
	{
		if (nl)
			count += ft_putendl_fd(matrix[i], fd);
		else
			count += ft_putstr_fd(matrix[i], fd);
		i++;
	}
	return (count);
}
