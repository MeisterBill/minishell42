#include "../Includes/minishell.h"

static int	ft_count_words(const char *str, char *set, int i[2])
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i[0]] != '\0')
	{
		if (!ft_strchr(set, str[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(set, str[i[0]]) || quotes[0]) && str[i[0]] != '\0')
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

static char	**ft_fill_matrix(char **tokens, char const *output, char *set, int i[3])
{
	int	out_len;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	out_len = ft_strlen(output);
	while (output[i[0]])
	{
		while (ft_strchr(set, output[i[0]]) && output[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, output[i[0]]) || quotes[0] || quotes[1]) && output[i[0]])
		{
			quotes[0] = (quotes[0] + (!quotes[1] && output[i[0]] == '\'')) % 2;
			quotes[1] = (quotes[1] + (!quotes[0] && output[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= out_len)
			tokens[i[2]++] = "\0";
		else
			tokens[i[2]++] = ft_substr(output, i[1], i[0] - i[1]);
	}
	return (tokens);
}

char	**ft_tokenize(char const *output, char *set)
{
	char	**tokens;
	int		nb_words;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!output)
		return (NULL);
	nb_words = ft_count_words(output, set, counts);
	if (nb_words == -1)
		return (NULL);
	tokens = malloc((nb_words + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens = ft_fill_matrix(tokens, output, set, i);
	tokens[nb_words] = NULL;
	return (tokens);
}
