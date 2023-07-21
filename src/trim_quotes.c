#include "../Includes/minishell.h"

static int	malloc_len(char const *str)
{
	int	count;
	int	i;
	int	doubleq;
	int	single;

	i = 0;
	count = 0;
	doubleq = 0;
	single = 0;
	while (str && str[i])
	{
		single = (single + (!doubleq && str[i] == '\'')) % 2;
		doubleq = (doubleq + (!single && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !single) || (str[i] == '\'' && !doubleq))
			count++;
		i++;
	}
	if (single || doubleq)
		return (-1);
	return (count);
}

char	*trim_quotes(char const *str, int single, int doubleq)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(str);
	if (!str || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!trimmed)
		return (NULL);
	while (str[i[0]])
	{
		single = (single + (!doubleq && str[i[0]] == '\'')) % 2;
		doubleq = (doubleq + (!single && str[i[0]] == '\"')) % 2;
		if ((str[i[0]] != '\"' || single) && (str[i[0]] != '\'' || \
		doubleq) && ++i[1] >= 0)
			trimmed[i[1]] = str[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}
