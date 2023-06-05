#include "../Includes/minishell.h"

static char *ft_getuser(t_prompt prompt)
{
	char **user;
	char *tmp;

	user = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	tmp = ft_strjoin(NULL, *user);
	ft_free_matrix(&user);
	return (tmp);
}

int ft_getprompt(t_prompt prompt)
{
	char	*tmp;

	tmp = ft_getuser(prompt);
	return (0);
}
