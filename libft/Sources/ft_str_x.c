#include "../Includes/libft.h"

char	*ft_strchr(const char *str, int n)
{
	unsigned char	n_unsigned;

	n_unsigned = (unsigned char)n;
	if (n_unsigned == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == n_unsigned)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int ft_strchr_index(const char *str, int n)
{
	unsigned char n_unsigned;
	int i;

	i = 0;
	if (!str)
		return (-1);
	n_unsigned = (unsigned char)n;
	while (str[i] != '\0')
	{
		if (str[i] == n_unsigned)
			return (i);
		i++;
	}
	if (n_unsigned == '\0')
		return (i);
	return (-1);
}

char	*ft_strdup(const char *str)
{
	char *res;
	size_t size;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, size + 1);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int len_s1;
	int len_s2;
	char *res;
	int i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *)malloc(len_s1 + len_s2 + 1);
	if (res == NULL)
		return (NULL);
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			res[i] = s1[i];
		if (i < len_s2)
			res[i + len_s1] = s2[i];
		i++;
	}
	res[len_s1 + len_s2] = '\0';
	return (res);
}

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int i;
	size_t size_src;

	i = 0;
	if (src == NULL)
		return (0);
	size_src = ft_strlen(src);
	if ((int)size < 0)
		size = size_src + 1;
	if (size >= 2 && size_src != 0)
	{
		while (i < size - 1)
		{
			if (i < size_src)
				dst[i] = src[i];
			else if (i == size_src)
				dst[i] = '\0';
			i++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	return (size_src);
}
