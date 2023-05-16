#ifndef LIBFT_H

# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

/* ATOI */
/* Reads a string, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
int			ft_atoi(const char *str);
int			ft_isspace(char c);

/* CALLOC */
/* Reserves count blocks of size bits of memory */
void		*ft_calloc(size_t count, size_t size);
/* Writes n zeroes to the string s */
void		ft_bzero(void *s, size_t n);

/* ITOA */
/* Saves the given number as a string (char array) */
char		*ft_itoa(int nb);
int			ft_nbrlen(long nb, int base);
int			ft_isdigit(int c);

/* MEM_X */
/* Assigns a character n times to a part of the memory*/
void		*ft_memset(void *s, int c, size_t n);

/* PUT_FD */
/* Prints a character to the given file descriptor */
int			ft_putchar_fd(char c, int fd);
/* Prints a string followed by a new line \n to a given file descriptor */
int			ft_putendl_fd(char *str, int fd);
/* Prints string to the given file descriptor */
int			ft_putstr_fd(char *str, int fd);

/* SPLIT */
/* Splits a string according to a given separator character (c) */
char		**ft_split(char const *s, char c);

/* STR_X */
size_t	ft_strlen(const char *str);
/* Looks for a specific character inside a given string,
 * returning pointer to it*/
char		*ft_strchr(const char *str, int c);
/* Copies size - 1 bytes from a source string to a destination string */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/* Saves enough space and duplicates a string */
char		*ft_strdup(const char *str);
/* Concatenates two strings allocating enough space first */
char		*ft_strjoin(char const *s1, char const *s2);
/* Compares two strings untill reaching the n-th character */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
/* Tries to find a substring (to_find) in a second string (str)
 * before the len-th char is reached */
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
/* Removes all first occurrences of characters (to_trim) from the start
 * and from the end of a str */
char		*ft_strtrim(char const *str, char const *to_trim);
/* Copies the next len characters from the start-th char of a str */
char		*ft_substr(char const *str, unsigned int start, size_t len);

#endif
