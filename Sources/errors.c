#include "../Includes/minishell.h"

//extern int exit_code;

void *ft_print_errors(int err_type, char *str, int exitcode)
{
	//exit_code = exitcode;
	exitcode = 0;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NODIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NOPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NOCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell:\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}
