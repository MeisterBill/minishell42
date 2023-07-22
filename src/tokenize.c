/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:26:27 by artvan-d          #+#    #+#             */
/*   Updated: 2023/07/22 18:26:29 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	ft_count_words(const char *str, char *set, int i[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (str[i[0]] != '\0')
	{
		if (!ft_strchr(set, str[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(set, str[i[0]]) || q[0]) && str[i[0]] != '\0')
			{
				if (!q[1] && (str[i[0]] == '\"' || str[i[0]] == '\''))
					q[1] = str[i[0]];
				q[0] = (q[0] + (str[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_matrix(char **tok, char const *out, char *set, int i[3])
{
	int	out_len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	out_len = ft_strlen(out);
	while (out[i[0]])
	{
		while (ft_strchr(set, out[i[0]]) && out[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, out[i[0]]) || q[0] || q[1]) && out[i[0]])
		{
			q[0] = (q[0] + (!q[1] && out[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && out[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= out_len)
			tok[i[2]++] = "\0";
		else
			tok[i[2]++] = ft_substr(out, i[1], i[0] - i[1]);
	}
	return (tok);
}

char	**ft_tokenize(char const *out, char *set)
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
	if (!out)
		return (NULL);
	nb_words = ft_count_words(out, set, counts);
	if (nb_words == -1)
		return (NULL);
	tokens = malloc((nb_words + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens = ft_fill_matrix(tokens, out, set, i);
	tokens[nb_words] = NULL;
	return (tokens);
}
