#include "../Includes/libft.h"

int	ft_matrixlen(char **matrix)
{
	int i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char ***matrix)
{
	int i;

	i = 0;
	while (matrix && matrix[0] && matrix[0][i])
	{
		free(matrix[0][i]);
		i++;
	}
	if (matrix)
	{
		free(matrix[0]);
		*matrix = NULL;
	}
}

char	**ft_dup_matrix(char **matrix)
{
	char **res;
	int nb_rows;
	int i;

	i = 0;
	nb_rows = ft_matrixlen(matrix);
	res = malloc(sizeof(char *) * (nb_rows + 1));
	if (!res)
		return (NULL);
	while (matrix[i])
	{
		res[i] = ft_strdup(matrix[i]);
		if (!res[i])
		{
			ft_free_matrix(&res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
