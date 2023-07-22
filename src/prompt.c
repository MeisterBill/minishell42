/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:01:05 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:01:13 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*ft_gethome(t_prompt prompt)
{
	char	*pwd;
	char	*home;
	char	*result;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = ft_getenv("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin(" ~", &pwd[ft_strlen(home)]);
		free(tmp);
	}
	free(home);
	result = ft_strjoin(pwd, " ");
	free(pwd);
	return (result);
}

char	*ft_getprompt(t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(NULL, "@noobshell");
	tmp2 = ft_gethome(prompt);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (tmp2);
}
