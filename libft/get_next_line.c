#include "libft.h"

char	*ft_readfile_and_pushtostash(int fd, char *stash)
{
	int		read_bytes;
	char	*buffer;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_checkbackn_and_pushtoline(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

char	*ft_push_cutstash_to_nextstash(char *stash)
{
	int		i;
	int		j;
	char	*next_stach;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	next_stach = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!next_stach)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		next_stach[j++] = stash[i++];
	next_stach[j] = '\0';
	free(stash);
	return (next_stach);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	stash = ft_readfile_and_pushtostash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_checkbackn_and_pushtoline(stash);
	stash = ft_push_cutstash_to_nextstash(stash);
	return (line);
}
