#include "../Includes/minishell.h"

static int ft_count_cmds(const char *str, char *delim, int i[2])
{
	int quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i[0]] != '\0')
	{
		if (!ft_strchr(delim, str[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(delim, str[i[0]]) || quotes[0]) && str[i[0]] != '\0')
			{
				if (!quotes[1] && (str[i[0]] == '\"' || str[i[0]] == '\''))
					quotes[1] = str[i[0]];
				quotes[0] = (quotes[0] + (str[i[0]] == quotes[1])) % 2;
				quotes[1] *= quotes[0] != 0;
				i[0]++;
			}
			if (quotes[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char **ft_fill_matrix(char **commands, char const *str, char *delim, int i[3])
{
	int s_len;
	int quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	s_len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(delim, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(delim, str[i[0]]) || quotes[0] || quotes[1]) && str[i[0]])
		{
			quotes[0] = (quotes[0] + (!quotes[1] && str[i[0]] == '\'')) % 2;
			quotes[1] = (quotes[1] + (!quotes[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			commands[i[2]++] = "\0";
		else
			commands[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (commands);
}

char **ft_tokenize(char const *str, char *delim)
{
	char **commands;
	int nb_cmd;
	int i[3];
	int counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!str)
		return (NULL);
	nb_cmd = ft_count_cmds(str, delim, counts);
	if (nb_cmd == -1)
		return (NULL);
	commands = malloc((nb_cmd + 1) * sizeof(char *));
	if (commands == NULL)
		return (NULL);
	commands = ft_fill_matrix(commands, str, delim, i);
	commands[nb_cmd] = NULL;
	return (commands);
}
