#include "../Includes/minishell.h"

static void	update_output(char ***matrix, int fd)
{
	char	**tmp_matrix;
	char	*tmp;
	char	*line;

	tmp_matrix = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		free(line);
		tmp_matrix = ft_extend_matrix(tmp_matrix, tmp);
		free(tmp);
	}
	ft_free_matrix(matrix);
	*matrix = tmp_matrix;
}

void	exec_custom(char ***output, char *full_path, char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		matrix = ft_split(cmd, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full_path, F_OK))
			execve(full_path, matrix, envp);
		exit(1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(output, fd[READ_END]);
	close(fd[READ_END]);
}
