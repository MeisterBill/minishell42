#include "../Includes/minishell.h"

int ft_pwd(void)
{
	char *buffer;

	buffer = getcwd(NULL, 0);
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
