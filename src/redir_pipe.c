#include "../Includes/minishell.h"

static int	ft_count_words(char *str, char *set, int nwords)
{
	int quotes[2];
	int i;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[i] != '\0')
	{
		nwords++;
		if (!ft_strchr(set, str[i]))
		{
			while ((!ft_strchr(set, str[i]) || quotes[0] || quotes[1]) && str[i] != '\0')
			{
				quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
				quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
				i++;
			}
			if (quotes[0] || quotes[1])
				return (-1);
		}
		else
			i++;
	}
	return (nwords);
}

static char	**ft_fill_matrix(char **tmp_matrix, char *str, char *set, int i[3])
{
	int quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, str[i[0]]))
		{
			while ((!ft_strchr(set, str[i[0]]) || quotes[0] || quotes[1]) && str[i[0]])
			{
				quotes[0] = (quotes[0] + (!quotes[1] && str[i[0]] == '\'')) % 2;
				quotes[1] = (quotes[1] + (!quotes[0] && str[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		tmp_matrix[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (tmp_matrix);
}

char	**handle_pipe_redir(char const *str, char *set)
{
	char	**tmp_matrix;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!str)
		return (NULL);
	nwords = ft_count_words((char *)str, set, 0);
	if (nwords == -1)
		return (NULL);
	tmp_matrix = malloc((nwords + 1) * sizeof(char *));
	if (tmp_matrix == NULL)
		return (NULL);
	tmp_matrix = ft_fill_matrix(tmp_matrix, (char *)str, set, i);
	tmp_matrix[nwords] = NULL;
	return (tmp_matrix);
}
