#include "../Includes/minishell.h"

char	*ft_getenv(char *var, char **envp, int n)
{
	int	i;
	int	real_len;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		real_len = n;
		if (real_len < ft_strchr_index(envp[i], '='))
			real_len = ft_strchr_index(envp[i], 61);
		if (!ft_strncmp(envp[i], var, real_len))
			return (ft_substr(envp[i], real_len + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**ft_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*var_tmp[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	var_tmp[0] = ft_strjoin(var, "=");
	var_tmp[1] = ft_strjoin(var_tmp[0], value);
	free(var_tmp[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_index(envp[i[0]], '='))
			i[1] = ft_strchr_index(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			var_tmp[0] = envp[i[0]];
			envp[i[0]] = var_tmp[1];
			free(var_tmp[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, var_tmp[1]);
	free(var_tmp[1]);
	return (envp);
}

static int	var_in_envp(char *str, char **envp, int i[2])
{
	int	pos;

	i[1] = 0;
	pos = ft_strchr_index(str, '=');
	if (pos == -1)
		return (-1);
	while (envp[i[1]])
	{
		if (!ft_strncmp(envp[i[1]], str, pos + 1))
			return (1);
		i[1]++;
	}
	return (0);
}

int	ft_export(t_prompt *prompt)
{
	int		i[2];
	int		pos;
	char	**mtx;

	mtx = ((t_data *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(mtx) >= 2)
	{
		i[0] = 1;
		while (mtx[i[0]])
		{
			pos = var_in_envp(mtx[i[0]], prompt->envp, i);
			if (pos == 1)
			{
				free(prompt->envp[i[1]]);
				prompt->envp[i[1]] = ft_strdup(mtx[i[0]]);
			}
			else if (!pos)
				prompt->envp = ft_extend_matrix(prompt->envp, mtx[i[0]]);
			i[0]++;
		}
	}
	return (0);
}

int	ft_unset(t_prompt *prompt)
{
	char	**mtx;
	char	*tmp;
	int		i[2];

	i[0] = 0;
	mtx = ((t_data *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(mtx) >= 2)
	{
		while (mtx[++i[0]])
		{
			if (mtx[i[0]][ft_strlen(mtx[i[0]]) - 1] != '=')
			{
				tmp = ft_strjoin(mtx[i[0]], "=");
				free(mtx[i[0]]);
				mtx[i[0]] = tmp;
			}
			if (var_in_envp(mtx[i[0]], prompt->envp, i))
				ft_replace_in_matrix(&prompt->envp, NULL, i[1]);
		}
	}
	return (0);
}
