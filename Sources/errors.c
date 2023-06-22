#include "../Includes/minishell.h"

//extern int exit_code;

void	*ft_print_errors(int err_type, char *str, int exitcode)
{
	//exit_code = exitcode;
	exitcode = 0;
	if (err_type == QUOTE)
		ft_putstr_fd("noobshell: error while looking for matching quote\n", 2);
	else if (err_type == NODIR)
		ft_putstr_fd("noobshell: No such file or directory: ", 2);
	else if (err_type == NOPERM)
		ft_putstr_fd("noobshell: permission denied: ", 2);
	else if (err_type == NOCMD)
		ft_putstr_fd("noobshell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("noobshell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("noobshell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("noobshell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("noobshell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("noobshell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("noobshell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("noobshell: Not a directory: ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}
