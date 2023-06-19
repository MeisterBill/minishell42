#include "../Includes/minishell.h"

static char **ft_trim_quotes(char **matrix)
{
	char	**tmp_matrix;
	char	*tmp;
	int		j;

	j = -1;
	tmp_matrix = ft_dup_matrix(matrix);
	while (tmp_matrix && tmp_matrix[++j])
	{
		tmp = trim_quotes(tmp_matrix[j], 0, 0);
		free(tmp_matrix[j]);
		tmp_matrix[j] = tmp;
	}
	return (tmp_matrix);
}

static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->full_cmd = NULL;
	data->full_path = NULL;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	return (data);
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
		if (i == 0 || (matrix[i][0] == '|' && matrix[i + 1] && matrix[i + 1][0]))
		{
			i += matrix[i][0] == '|';
			ft_listadd_back(&cmds[0], ft_listnew(init_data()));
			cmds[1] = ft_listlast(cmds[0]);
		}
		tmp[0] = matrix;
	}
	return (cmds[0]);
}
