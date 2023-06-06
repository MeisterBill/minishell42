#include "../Includes/minishell.h"

void *checkargs_exec(char *output, t_prompt *prompt)
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
	printf("%s\n", matrix[2]);
	return (prompt);
}
