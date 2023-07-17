#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

# define READ_END 0
# define WRITE_END 1

/* Implementation of linked list, content will become a t_data struct */
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

/* Data structure for prompt + env + command linked list */
typedef struct s_prompt
{
	t_list	*cmds;
	char		**envp;
	pid_t		pid;
} t_prompt;

/* General data structure containing data for execution */
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

/* ERRORS */
/* Prints a custom error message to standard error */
void	*ft_print_errors(int err_type, char *str, int exitcode);
/* Frees all elements in linked list nodes */
void	free_content(void *contentt);

/* ENV + PROMPT */
/* Retrieves a string containing the value of an env var */
char	*ft_getenv(char *var, char **envp, int n);
/* Sets a new environment variable or changes the value of an existing one */
char	**ft_setenv(char *var, char *value, char **envp, int n);
/* Returns a string with user and current directory used as prompt for readline */
char	*ft_getprompt(t_prompt prompt);

/* Executes a custom command and saves output to string ending in \n */
void	exec_custom(char ***output, char *full_path, char *cmd, char **envp);

/* Parsing and execution of program */
void	*checkargs_exec(char *output, t_prompt *prompt);

/* Splits command and args into a matrix of tokens, taking quotes into account */
char	**ft_tokenize(char const *str, char *set);

/* Replaces env variables in a string if not in simple quotes */
char	*handle_vars(char *str, int i, int quotes[2], t_prompt *prompt);

/* Replaces "~" to home directory in a string if not in quotes */
char		*handle_path(char *str, int i, int quotes[2], char *path_var);

/* Copy of ft_split but handles pipe and redirections as separators and takes quotes into account */
char		**handle_pipe_redir(char const *str, char *set);

/* Replaces the matrix with all commands and args into a linked list with this same information */
t_list	*fill_list(char **matrix, int i);

/* Trims all needed quotes from the original input */
char		*trim_quotes(char const *str, int single, int doubleq);

/* LINKED LISTS */
/* Retrieves last element of the list */
t_list	*ft_listlast(t_list *list);
/* Adds new element at the end of the linked list */
void		ft_listadd_back(t_list **list, t_list *new_elem);
/* Creates new list element allocating with malloc */
t_list	*ft_listnew(void *content);
/* Returns number of elements of linked list */
int			ft_listsize(t_list *list);

/* REDIRECTIONS / APPEND */
/* Opens a file descriptor with the needed open flags */
int			get_fd(int oldfd, char *path, int flags[2]);
/* Tries to open proper file as outfile (>> case) */
t_data *get_out_append(t_data *content, char **matrix, int *i);
/* Tries to open proper file as outfile (> case) */
t_data	*get_outfile(t_data *content, char **matrix, int *i);
/* Tries to open proper file as infile (< case) */
t_data	*get_infile(t_data *content, char **matrix, int *i);
/* Tries to open read heredoc as infile (<< case) */
t_data	*get_in_heredoc(t_data *content, char **matrix, int *i);

/* SIGNALS */
/* Function to handle SIGINT signals for main process */
void		handle_sigint(int sig);

/* HEREDOC */
/* Retrieves a string from standard input, expanding vars when needed */
int			get_here_doc(char *str[2], char *aux[2]);

/* BUILTINS */
/* Handles all builtin functions */
int 		builtin(t_prompt *prompt, t_list *cmds, int *is_exit, int c_len);
/* Implementation of the exit builtin */
int			ft_exit(t_list *cmds, int *is_exit);
/* Implementation of the cd builtin */
int			ft_cd(t_prompt *prompt);
/* Implementation of the export builtin */
int ft_export(t_prompt *prompt);

#endif
