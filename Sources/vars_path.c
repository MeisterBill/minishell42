#include "../Includes/minishell.h"

char *handle_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1])
		{
			
		}
	}
	return (str);
}
