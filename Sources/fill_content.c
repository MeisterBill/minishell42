#include "../Includes/minishell.h"

int	get_fd(int oldfd, char *path, int flags[2])
{
	int fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NODIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NOPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NOPERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_data	*get_outfile2(t_data *content, char **matrix, int *i)
{
	char	*nl;
	int		flags[2];
	int		test;

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (matrix[++(*i)])
		content->outfile = get_fd(content->outfile, matrix[*i], flags);
	if (!matrix[*i] || content->outfile == -1)
	{
		*i = -1;
		if (content->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			//exit_code = 2;
		}
		else
			//exit_code = 1;
			test = 1;
	}
	return (content);
}
