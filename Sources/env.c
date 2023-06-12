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
