#include "../Includes/minishell.h"

extern int exit_code;

static char *ft_getuser(t_prompt prompt)
{
	char **user;
	char *tmp;
	char *tmp2;

	user = NULL;
	tmp2 = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		tmp2 = ft_strjoin(NULL, RED);
	else if ((int)(user[0][0]) % 5 == 0)
		tmp2 = ft_strjoin(NULL, CYAN);
	else if ((int)(user[0][0]) % 5 == 1)
		tmp2 = ft_strjoin(NULL, GRAY);
	else if ((int)(user[0][0]) % 5 == 2)
		tmp2 = ft_strjoin(NULL, GREEN);
	else if ((int)(user[0][0]) % 5 == 3)
		tmp2 = ft_strjoin(NULL, MAGENTA);
	else
		tmp2 = ft_strjoin(NULL, YELLOW);
	tmp = ft_strjoin(tmp2, *user);
	free(tmp2);
	ft_free_matrix(&user);
	return (tmp);
}

char *ft_getprompt(t_prompt prompt)
{
	char	*tmp;

	tmp = ft_getuser(prompt);
}
