/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:19:25 by artvan-d          #+#    #+#             */
/*   Updated: 2023/04/12 21:34:46 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Includes/minishell.h"

extern int exit_code;

static void	ft_getchildpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		//error managment function
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt init_vars(t_prompt prompt, char *str, char **argv)
{
	return (prompt);
}

static t_prompt init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char			*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	exit_code = 0;
	ft_getchildpid(&prompt);
	//prompt = init_vars(prompt, str, argv);
	return (prompt);
}

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;

	prompt = init_prompt(argv, envp);
	return (0);
}
