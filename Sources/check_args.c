#include "../Includes/minishell.h"

static char	**split_vars_path(char **matrix, t_prompt *prompt)
{

	return (matrix);
}

static void	*ft_parsing(char **matrix, t_prompt *prompt)
{
	split_vars_path(matrix, prompt);
	prompt->cmds = fill_list();
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
	//printf("%s\n", matrix[2]);
	free(output);
	if (!matrix)
		ft_print_errors(QUOTE, NULL, 1);
	if (!matrix)
		return ("");
	prompt = ft_parsing(matrix, prompt);
	return (prompt);
}
