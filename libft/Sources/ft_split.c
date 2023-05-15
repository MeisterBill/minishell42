#include "../Includes/libft.h"

static int	ft_count_words(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **result, char const *str, char c)
{
	size_t	i;
	size_t	j;
	int			k;
	size_t	str_len;

	i = 0;
	k = 0;
	str_len = ft_strlen(str);
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		j = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (j >= str_len)
			result[k++] = "\0";
		else
			result[k++] = ft_substr(str, j, i - j);
	}
	return (result);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		nb_words;

	if (!str)
		return (NULL);
	nb_words = ft_count_words(str, c);
	result = malloc((nb_words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_fill_array(result, str, c);
	result[nb_words] = NULL;
	return (result);
}
