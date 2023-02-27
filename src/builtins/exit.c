#include "minishell.h"

void	ft_exit(t_mini *mini)
{
	rl_clear_history();
	system("leaks minishell");
	printf("exit 🤍\n");
	exit(1);
}
