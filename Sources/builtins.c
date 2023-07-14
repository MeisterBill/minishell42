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
