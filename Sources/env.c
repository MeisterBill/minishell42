#include "../Includes/minishell.h"

char	*ft_getenv(char *var, char **envp, int n)
{
	int i;
	int len;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		len = n;
		if (len < ft_strchr_i(envp[i], '='))
			len = ft_strchr_i(envp[i], 61);
		if (!ft_strncmp(envp[i], var, len))
			return (ft_substr(envp[i], len + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}
