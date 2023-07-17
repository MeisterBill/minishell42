#include "../Includes/minishell.h"

extern int	exit_code;

int	builtin(t_prompt *prompt, t_list *cmds, int *is_exit, int c_len)
{
	char **cmd_full;

	while (cmds)
	{
		cmd_full = ((t_data *)cmds->content)->full_cmd;
		c_len = 0;
		if (cmd_full)
			c_len = ft_strlen(*cmd_full);
		if (cmd_full && !ft_strncmp(*cmd_full, "exit", c_len) && c_len == 4)
			exit_code = ft_exit(cmds, is_exit);
		else if (!cmds->next && cmd_full && !ft_strncmp(*cmd_full, "cd", c_len) && c_len == 2)
			exit_code = ft_cd(prompt);
		else if (!cmds->next && cmd_full && !ft_strncmp(*cmd_full, "export", c_len) && c_len == 6)
			exit_code = ft_export(prompt);
		else if (!cmds->next && cmd_full && !ft_strncmp(*cmd_full, "unset", c_len) && c_len == 5)
			exit_code = ft_unset(prompt);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmds);
		}
		cmds = cmds->next;
	}
	return (exit_code);
}

int	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}

static void	change_error_cd(char **str[2])
{
	DIR	*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		exit_code = 1;
		ft_putstr_fd("noobshell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		exit_code = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		ft_print_errors(NODIR, str[0][1], 1);
	else if (str[0][1])
		ft_print_errors(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

int	ft_cd(t_prompt *prompt)
{
	char **str[2];
	char *tmp;

	exit_code = 0;
	str[0] = ((t_data *)prompt->cmds->content)->full_cmd;
	tmp = mini_getenv("HOME", prompt->envp, 4);
	if (!tmp)
		tmp = ft_strdup("");
	str[1] = ft_extend_matrix(NULL, tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	str[1] = ft_extend_matrix(str[1], tmp);
	free(tmp);
	change_error_cd(str);
	if (!exit_code)
		prompt->envp = mini_setenv("OLDPWD", str[1][1], prompt->envp, 6);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup("");
	str[1] = ft_extend_matrix(str[1], tmp);
	free(tmp);
	prompt->envp = mini_setenv("PWD", str[1][2], prompt->envp, 3);
	ft_free_matrix(&str[1]);
	return (exit_code);
}
