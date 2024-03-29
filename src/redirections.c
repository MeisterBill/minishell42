/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:26:13 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:26:15 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_fd(int oldfd, char *file, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!file)
		return (-1);
	if (access(file, F_OK) == -1 && !flags[0])
		ft_print_errors(NODIR, file, 127);
	else if (!flags[0] && access(file, R_OK) == -1)
		ft_print_errors(NOPERM, file, 126);
	else if (flags[0] && access(file, W_OK) == -1 && access(file, F_OK) == 0)
		ft_print_errors(NOPERM, file, 126);
	if (flags[0] && flags[1])
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(file, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_data	*get_out_append(t_data *content, char **matrix, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "noobshell: syntax error near unexpected token `newline'";
	(*i)++;
	if (matrix[++(*i)])
		content->outfile = get_fd(content->outfile, matrix[*i], flags);
	if (!matrix[*i] || content->outfile == -1)
	{
		*i = -1;
		if (content->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_exitcode = 2;
		}
		else
			g_exitcode = 1;
	}
	return (content);
}

t_data	*get_outfile(t_data *content, char **matrix, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "noobshell: syntax error near unexpected token `newline'";
	(*i)++;
	if (matrix[*i])
		content->outfile = get_fd(content->outfile, matrix[*i], flags);
	if (!matrix[*i] || content->outfile == -1)
	{
		*i = -1;
		if (content->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_exitcode = 2;
		}
		else
			g_exitcode = 1;
	}
	return (content);
}

t_data	*get_in_heredoc(t_data *content, char **matrix, int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "noobshell: warning: here-document delimited by end-of-file";
	nl = "noobshell: syntax error near unexpected token `newline'";
	(*i)++;
	if (matrix[++(*i)])
	{
		aux[0] = matrix[*i];
		content->infile = get_here_doc(str, aux);
	}
	if (!matrix[*i] || content->infile == -1)
	{
		*i = -1;
		if (content->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_exitcode = 2;
		}
	}
	return (content);
}

t_data	*get_infile(t_data *content, char **matrix, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "noobshell: syntax error near unexpected token `newline'";
	(*i)++;
	if (matrix[*i])
		content->infile = get_fd(content->infile, matrix[*i], flags);
	if (!matrix[*i] || content->infile == -1)
	{
		*i = -1;
		if (content->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_exitcode = 2;
		}
		else
			g_exitcode = 1;
	}
	return (content);
}
