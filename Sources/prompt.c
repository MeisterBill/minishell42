#include "../Includes/minishell.h"

static char *ft_gethome(t_prompt prompt)
{
	char *pwd;
	char *home;
	char *result;
	char *tmp;

			pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = ft_getenv("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin(" ~", &pwd[ft_strlen(home)]);
		free(tmp);
	}
	free(home);
	result = ft_strjoin(pwd, " ");
	free(pwd);
	return result;
}

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

char	*ft_getprompt(t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_getuser(prompt);
	tmp2 = ft_strjoin(tmp, "@noobshell");
	free(tmp);
	tmp3 = ft_gethome(prompt);
	tmp = ft_strjoin(tmp2, tmp3);
	free(tmp3);
	free(tmp2);
	tmp2 = ft_strjoin(tmp,"$ ");
	free(tmp);
	return (tmp2);
}
