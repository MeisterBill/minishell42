/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:26:45 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:26:47 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*handle_path(char *str, int i, int q[2], char *path_var)
{
	char	*path;
	char	*tmp;

	q[0] = 0;
	q[1] = 0;
	while (str && str[++i])
	{
		q[0] = (q[0] + (!q[1] && str[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && str[i] == '\"')) % 2;
		if (!q[0] && !q[1] && str[i] == '~' && (i == 0 || str[i - 1] != '$'))
		{
			tmp = ft_substr(str, 0, i);
			path = ft_strjoin(tmp, path_var);
			free(tmp);
			tmp = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, tmp);
			free(tmp);
			free(path);
			return (handle_path(str, i + ft_strlen(path_var) - 1, q, path_var));
		}
	}
	free(path_var);
	return (str);
}

static char	*replace_var_value(char *str, int i, t_prompt *prompt)
{
	char	*tmp;
	int		endchar_pos;
	char	*pre_and_var;
	char	*var_value;

	endchar_pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + \
	(ft_strchr("$?", str[i]) != 0);
	if (endchar_pos == -1)
		endchar_pos = ft_strlen(str) - 1;
	tmp = ft_substr(str, 0, i - 1);
	var_value = ft_getenv(&str[i], prompt->envp, \
	ft_strchars_i(&str[i], "\"\'$|>< "));
	if (!var_value && str[i] == '$')
		var_value = ft_itoa(prompt->pid);
	else if (!var_value && str[i] == '?')
		var_value = ft_itoa(g_exitcode);
	pre_and_var = ft_strjoin(tmp, var_value);
	free(tmp);
	tmp = ft_strjoin(pre_and_var, &str[i + endchar_pos]);
	free(var_value);
	free(pre_and_var);
	free(str);
	return (tmp);
}

char	*handle_vars(char *str, int i, int q[2], t_prompt *prompt)
{
	q[0] = 0;
	q[1] = 0;
	while (str && str[++i])
	{
		q[0] = (q[0] + (!q[1] && str[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && str[i] == '\"')) % 2;
		if (!q[0] && str[i] == '$' && str[i + 1] && \
		((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !q[1]) || \
		(ft_strchars_i(&str[i + 1], "/~%^{}:;\" ") && q[1])))
			return (handle_vars(replace_var_value(str, ++i, prompt), -1, \
			q, prompt));
	}
	return (str);
}
