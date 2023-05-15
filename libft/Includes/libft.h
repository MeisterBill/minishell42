#ifndef LIBFT_H

# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

/* Reads a string, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
int	ft_atoi(const char *str);
int	ft_isspace(char c);

/* Saves the given number as a string (char array) */
char	*ft_itoa(int nb);
int		ft_nbrlen(long nb, int base);

/* Reserves count blocks of size bits of memory */
void	*ft_calloc(size_t count, size_t size);
/* Writes n zeroes to the string s */
void	ft_bzero(void *s, size_t n);

int	ft_isdigit(int c);

/* Assigns a character n times to a part of the memory*/
void	*ft_memset(void *s, int c, size_t n);

/* Prints a character to the given file descriptor */
int ft_putchar_fd(char c, int fd);
/* Prints a string followed by a new line \n to a given file descriptor */
int	ft_putendl_fd(char *str, int fd);
/* Prints string to the given file descriptor */
int	ft_putstr_fd(char *str, int fd);

/* Splits a string according to a given separator character (c) */
char	**ft_split(char const *s, char c);

/* Looks for a specific character inside a given string,
 * returning pointer to it*/
char	*ft_strchr(const char *str, int c);

/* Copies size - 1 bytes from a source string to a destination string */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* Saves enough space and duplicates a string */
char	*ft_strdup(const char *str);

/* Concatenates two strings allocating enough space first */
char	*ft_strjoin(char const *s1, char const *s2);



#endif
