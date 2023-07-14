#include "../Includes/minishell.h"

extern int	exit_code;

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
	i = ft_lstsize(prompt->cmds);
	exit_code = builtin(prompt, prompt->cmds, &is_exit, 0);
	return (prompt);
}

void	*checkargs_exec(char *output, t_prompt *prompt)
{
	char		**matrix;
	//t_data	*data;

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
	return (prompt);
}
