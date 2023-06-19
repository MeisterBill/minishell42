#include "../Includes/minishell.h"

static char **ft_trim_quotes(char **args)
{
	char	**tmp_matrix;
	char	*tmp;
	int		j;

	j = -1;
	tmp_matrix = ft_dup_matrix(args);
	while (tmp_matrix && tmp_matrix[++j])
	{
		tmp = trim_quotes(tmp_matrix[j], 0, 0);
		free(tmp_matrix[j]);
		tmp_matrix[j] = tmp;
	}
	return (tmp_matrix);
}

t_list	*fill_list(char **matrix, int i)
{
	t_list	*cmds[2];
	char		**tmp[2];

	cmds[0] = NULL;
	tmp[1] = ft_trim_quotes(matrix);
	while (matrix[++i])
	{
		cmds[1] = ft_listlast(cmds[0]);
	}
	return (cmds[0]);
}
