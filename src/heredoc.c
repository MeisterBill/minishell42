/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:25:45 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:25:47 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*tmp;

	while (g_exitcode != 130 && (!str[0] || \
	ft_strncmp(str[0], limit, len) || ft_strlen(limit) != len))
	{
		tmp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(tmp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		tmp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(tmp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_exitcode = 0;
	if (pipe(fd) == -1)
	{
		ft_print_errors(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_exitcode == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
