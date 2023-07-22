/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:25:18 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:25:21 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	child_exec(t_prompt *prompt, t_data *cnt, int l, t_list *cmds)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(cnt) && cnt->full_cmd)
		execve(cnt->full_path, cnt->full_cmd, prompt->envp);
	else if (cnt->full_cmd && !ft_strncmp(*cnt->full_cmd, "pwd", l) \
		&& l == 3)
		g_exitcode = ft_pwd();
	else if (is_builtin(cnt) && cnt->full_cmd && \
		!ft_strncmp(*cnt->full_cmd, "echo", l) && l == 4)
		g_exitcode = ft_echo(cmds);
	else if (is_builtin(cnt) && cnt->full_cmd && \
		!ft_strncmp(*cnt->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_exitcode = 0;
	}
}

static void	*child_redir(t_list *cmds, int fd[2])
{
	t_data	*content;

	content = cmds->content;
	if (content->infile != STDIN_FILENO)
	{
		if (dup2(content->infile, STDIN_FILENO) == -1)
			return (ft_print_errors(DUPERR, NULL, 1));
		close(content->infile);
	}
	if (content->outfile != STDOUT_FILENO)
	{
		if (dup2(content->outfile, STDOUT_FILENO) == -1)
			return (ft_print_errors(DUPERR, NULL, 1));
		close(content->outfile);
	}
	else if (cmds->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ft_print_errors(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_prompt *prompt, t_list *cmds, int fd[2])
{
	t_data	*cnt;
	int		l;

	cnt = cmds->content;
	l = 0;
	if (cnt->full_cmd)
		l = ft_strlen(*cnt->full_cmd);
	child_redir(cmds, fd);
	close(fd[READ_END]);
	child_exec(prompt, cnt, l, cmds);
	ft_listclear(&prompt->cmds, free_content);
	exit(g_exitcode);
}

void	exec_fork(t_prompt *prompt, t_list *cmds, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		ft_print_errors(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmds, fd);
}

void	*check_to_fork(t_prompt *prompt, t_list *cmds, int fd[2])
{
	t_data	*cnt;
	DIR		*dir;

	cnt = cmds->content;
	dir = NULL;
	if (cnt->full_cmd)
		dir = opendir(*cnt->full_cmd);
	if (cnt->infile == -1 || cnt->outfile == -1)
		return (NULL);
	if ((cnt->full_path && access(cnt->full_path, X_OK) == 0) \
	|| is_builtin(cnt))
		exec_fork(prompt, cmds, fd);
	else if (!is_builtin(cnt) && ((cnt->full_path && \
		!access(cnt->full_path, F_OK)) || dir))
		g_exitcode = 126;
	else if (!is_builtin(cnt) && cnt->full_cmd)
		g_exitcode = 127;
	if (dir)
		closedir(dir);
	return ("");
}
