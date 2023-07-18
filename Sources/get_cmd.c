#include "../Includes/minishell.h"

extern int exit_code;

static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char *tmp;
	int i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*cmd_checks(t_prompt *prompt, t_list *cmds, char ***s, char *path)
{
	t_data	*cnt;
	DIR			*dir;

	dir = NULL;
	cnt = cmds->content;
	if (cnt && cnt->full_cmd)
		dir = opendir(*cnt->full_cmd);
	if (cnt && cnt->full_cmd && ft_strchr(*cnt->full_cmd, '/') && !dir)
	{
		*s = ft_split(*cnt->full_cmd, '/');
		cnt->full_path = ft_strdup(*cnt->full_cmd);
		free(cnt->full_cmd[0]);
		cnt->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
	}
	else if (!is_builtin(cnt) && cnt && cnt->full_cmd && !dir)
	{
		path = ft_getenv("PATH", prompt->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		cnt->full_path = find_command(*s, *cnt->full_cmd, cnt->full_path);
		if (!cnt->full_path || !cnt->full_cmd[0] || !cnt->full_cmd[0][0])
			ft_print_errors(NOCMD, *cnt->full_cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_prompt *prompt, t_list *cmds, char **s, char *path)
{
	t_data	*cnt;
	DIR			*dir;

	cnt = cmds->content;
	dir = cmd_checks(prompt, cmds, &s, path);
	if (!is_builtin(cnt) && cnt && cnt->full_cmd && dir)
		ft_print_errors(IS_DIR, *cnt->full_cmd, 126);
	else if (!is_builtin(cnt) && cnt && cnt->full_path && \
					 access(cnt->full_path, F_OK) == -1)
		ft_print_errors(NODIR, cnt->full_path, 127);
	else if (!is_builtin(cnt) && cnt && cnt->full_path && \
					 access(cnt->full_path, X_OK) == -1)
		ft_print_errors(NOPERM, cnt->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmds)
{
	int	fd[2];

	get_cmd(prompt, cmds, NULL, NULL);
	return (NULL);
}
