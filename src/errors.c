#include "../Includes/minishell.h"

void	*ft_print_errors(int err_type, char *str, int exitcode)
{
	g_exitcode = exitcode;
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

void	free_content(void *contentt)
{
	t_data	*content;

	content = contentt;
	ft_free_matrix(&content->full_cmd);
	free(content->full_path);
	if (content->infile != STDIN_FILENO)
		close(content->infile);
	if (content->outfile != STDOUT_FILENO)
		close(content->outfile);
	free(content);
}

static int	ft_atoi2(const char *nptr, long *nbr)
{
	int	sign;

	sign = 1;
	*nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbr = 10 * *nbr + (*nptr - '0');
		nptr++;
	}
	if (*nptr && !ft_isspace(*nptr))
		return (-1);
	*nbr *= sign;
	return (0);
}

int	ft_exit(t_list *cmds, int *is_exit)
{
	t_data	*content;
	long	status[2];

	content = cmds->content;
	*is_exit = !cmds->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!content->full_cmd || !content->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(content->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("noobshell: exit: ", 2);
		ft_putstr_fd(content->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (content->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("noobshell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

int	ft_echo(t_list *cmds)
{
	int			newline;
	int			i[2];
	char		**matrix;
	t_data		*cnt;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	cnt = cmds->content;
	matrix = cnt->full_cmd;
	while (matrix && matrix[++i[0]])
	{
		if (!i[1] && !ft_strncmp(matrix[i[0]], "-n", 2) && \
		(ft_countchar(matrix[i[0]], 'n') == \
		(int)(ft_strlen(matrix[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(matrix[i[0]], 1);
			if (matrix[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}
