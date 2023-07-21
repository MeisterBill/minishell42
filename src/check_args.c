#include "../Includes/minishell.h"

static char	**split_all(char **matrix, t_prompt *prompt)
{
		int		i;
		int		quotes[2];
		char	**tmp_matrix;

		i = -1;
		while (matrix && matrix[++i])
		{
			matrix[i] = handle_vars(matrix[i], -1, quotes, prompt);
			matrix[i] = handle_path(matrix[i], -1, quotes, ft_getenv("HOME", prompt->envp, 4));
			tmp_matrix = handle_pipe_redir(matrix[i], "<|>");
			ft_replace_in_matrix(&matrix, tmp_matrix, i);
			i += ft_matrixlen(tmp_matrix) - 1;
			ft_free_matrix(&tmp_matrix);
		}
		return (matrix);
}

static void	*ft_parsing(char **matrix, t_prompt *prompt)
{
	int	i;
	int	is_exit;

	matrix = split_all(matrix, prompt);
	prompt->cmds = fill_list(matrix, -1);
	if (!prompt->cmds)
			return (prompt);
	i = ft_listsize(prompt->cmds);
	g_exitcode = builtin(prompt, prompt->cmds, &is_exit, 0);
	while (i-- > 0)
			waitpid(-1, &g_exitcode, 0);
	if (!is_exit && g_exitcode == 13)
			g_exitcode = 0;
	if (g_exitcode > 255)
			g_exitcode = g_exitcode / 255;
	if (matrix && is_exit)
	{
			ft_listclear(&prompt->cmds, free_content);
			return (NULL);
	}
	return (prompt);
}

void	*checkargs_exec(char *output, t_prompt *prompt)
{
	char		**matrix;
	t_data	*cnt;

	if (!output)
	{
		printf("exit\n");
		return (NULL);
	}
	if (output[0] != '\0')
		add_history(output);
	matrix = ft_tokenize(output, " ");
	free(output);
	if (!matrix)
		ft_print_errors(QUOTE, NULL, 1);
	if (!matrix)
		return ("");
	prompt = ft_parsing(matrix, prompt);
	if (prompt && prompt->cmds)
		cnt = prompt->cmds->content;
	if (prompt && prompt->cmds && cnt && cnt->full_cmd && ft_listsize(prompt->cmds) == 1)
		prompt->envp = ft_setenv("_", cnt->full_cmd[ft_matrixlen(cnt->full_cmd) - 1], \
			prompt->envp, 1);
	if (prompt && prompt->cmds)
		ft_listclear(&prompt->cmds, free_content);
	return (prompt);
}
