/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:27:30 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:27:31 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char ***matrix)
{
	int	i;

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
	char	**res;
	int		nb_rows;
	int		i;

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

char	**ft_extend_matrix(char **ex_matrix, char *to_add)
{
	char	**new_matrix;
	int		len;
	int		i;

	i = -1;
	new_matrix = NULL;
	if (!to_add)
		return (ex_matrix);
	len = ft_matrixlen(ex_matrix);
	new_matrix = malloc(sizeof(char *) * (len + 2));
	new_matrix[len + 1] = NULL;
	if (!new_matrix)
		return (ex_matrix);
	while (++i < len)
	{
		new_matrix[i] = ft_strdup(ex_matrix[i]);
		if (!new_matrix[i])
		{
			ft_free_matrix(&ex_matrix);
			ft_free_matrix(&new_matrix);
		}
	}
	new_matrix[i] = ft_strdup(to_add);
	ft_free_matrix(&ex_matrix);
	return (new_matrix);
}

char	**ft_replace_in_matrix(char ***original, char **to_add, int n)
{
	char	**new_matrix;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!original || !*original || n < 0 || n >= ft_matrixlen(*original))
		return (NULL);
	new_matrix = ft_calloc(ft_matrixlen(*original) + ft_matrixlen(to_add), \
	sizeof(char *));
	while (new_matrix && original[0][++i[0]])
	{
		if (i[0] != n)
			new_matrix[++i[2]] = ft_strdup(original[0][i[0]]);
		else
		{
			while (to_add && to_add[++i[1]])
				new_matrix[++i[2]] = ft_strdup(to_add[i[1]]);
		}
	}
	ft_free_matrix(original);
	*original = new_matrix;
	return (*original);
}
