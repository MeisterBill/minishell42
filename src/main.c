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

int	g_exitcode = 0;

static void	ft_getshellpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_print_errors(FORKERR, NULL, 1);
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

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
	char	*nb_shlvl;

	str = getcwd(NULL, 0);
	prompt.envp = ft_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = ft_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		nb_shlvl = ft_strdup("1");
	else
		nb_shlvl = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = ft_setenv("SHLVL", nb_shlvl, prompt.envp, 5);
	free(nb_shlvl);
	str = ft_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = ft_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = ft_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = ft_setenv("_", argv[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char			*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_exitcode = 0;
	ft_getshellpid(&prompt);
	prompt = init_vars(prompt, str, argv);
	return (prompt);
}

int	main(int ac, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;
	char		*output;

	prompt = init_prompt(argv, envp);
	while (argv && ac)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = ft_getprompt(prompt);
		if (str)
			output = readline(str);
		else
			output = readline("guest@noobshell $ ");
		free(str);
		if (!checkargs_exec(output, &prompt))
			break ;
	}
	exit(g_exitcode);
}
