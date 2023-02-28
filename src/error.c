#include "minishell.h"

//print error for invalid input || non valid commands
void	ft_error(t_mini *mini, char **cmds)
{
	char *user;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf("\033[95m%s:\033[0m ", user);
	printf("%s: command not found\n", cmds[0]);
}
