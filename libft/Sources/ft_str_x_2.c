#include "../Includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	if (to_find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (to_find[j] != '\0' && j + i < len)
			{
				if (str[i + j] == to_find[j] && to_find[j + 1] == '\0')
					return ((char *)&str[i]);
				else if (str[i + j] != to_find[j])
					break;
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_strtrim(char const *str, char const *to_trim)
{
	int len;
	int i;
	int j;

	if (!str)
		return (0);
	len = ft_strlen(str);
	i = 0;
	j = len - 1;
	while (i <= len / 2 && ft_strchr(to_trim, str[i]) != NULL)
		i++;
	while (j >= len / 2 && ft_strchr(to_trim, str[j]) != NULL)
		j--;
	if (i > j)
		return (ft_strdup(""));
	len = j - i;
	return (ft_substr(str, i, len + 1));
}

char *ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t str_len;
	char *res;
	size_t i;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	i = 0;
	if (len > str_len)
		len = str_len;
	if (start >= str_len)
	{
		res = (char *)malloc(1);
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i++ < start)
		str++;
	ft_strlcpy(res, str, len + 1);
	return (res);
}
