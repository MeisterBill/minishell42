#include "../Includes/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exitcode = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
