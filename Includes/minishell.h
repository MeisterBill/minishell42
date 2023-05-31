#ifndef MINISHELL_H

#define MINISHELL_H

#include "../libft/Includes/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/ioctl.h>

#define READ_END 0
#define WRITE_END 1

/* Implementation of linked list */
typedef struct s_list
{
	void					*content;
	struct s_list	*next;
} t_list;

/* Vector with x and y coordinates */
typedef struct s_vector
{
	int	x;
	int	y;
} t_vector;

/* Data structure useful for prompt stuff + stocking copy of env */
typedef struct s_prompt
{
	t_list	*cmds;
	char		**envp;
	pid_t		pid;
} t_prompt;

/* General data structure containing most of needed data for command stuff */
typedef struct s_data
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
} t_data;

/* Easier error managment */
enum e_mini_error
{
	QUOTE = 1,
	NODIR = 2,
	NOPERM = 3,
	NOCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

/* Prints a custom error message to standard error */
void	*ft_print_errors(int err_type, char *str, int exitcode);

/* Retrieves a string containing the value of an env var */
char	*ft_getenv(char *var, char **envp, int n);
/* Sets a new environment variable or changes the value of an existing one */
char	**ft_setenv(char *var, char *value, char **envp, int n);

#endif
