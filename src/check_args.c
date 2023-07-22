/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:53 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 19:11:34 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		matrix[i] = handle_path(matrix[i], -1, quotes, \
		ft_getenv("HOME", prompt->envp, 4));
		tmp_matrix = handle_pipe_redir(matrix[i], "<|>");
		ft_replace_in_matrix(&matrix, tmp_matrix, i);
		i += ft_matrixlen(tmp_matrix) - 1;
		ft_free_matrix(&tmp_matrix);
	}
	return (matrix);
}

static void	*ft_parsing(char **matrix, t_prompt *prompt)
{
	int	l[2];
	int	is_exit;

	is_exit = 0;
	matrix = split_all(matrix, prompt);
	prompt->cmds = fill_list(matrix, -1);
	if (!prompt->cmds)
		return (prompt);
	l[1] = ft_listsize(prompt->cmds);
	g_exitcode = builtin(prompt, prompt->cmds, &is_exit, l);
	while (l[1]-- > 0)
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

void	*checkargs_exec(char *output, t_prompt *p)
{
	char	**matrix;
	t_data	*c;

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
	p = ft_parsing(matrix, p);
	if (p && p->cmds)
		c = p->cmds->content;
	if (p && p->cmds && c && c->full_cmd && ft_listsize(p->cmds) == 1)
		p->envp = ft_setenv("_", c->full_cmd[ft_matrixlen(c->full_cmd) - 1], \
		p->envp, 1);
	if (p && p->cmds)
		ft_listclear(&p->cmds, free_content);
	return (p);
}
