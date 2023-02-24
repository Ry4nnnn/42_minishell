#include "minishell.h"

void	ft_exit(t_mini *mini)
{
	// ft_lstclear(&mini->envp, clear_env_var);
	// ft_lstclear(&mini->envx, clear_env_var);
	rl_clear_history();
	system ("leaks minishell");
	printf("exit 🤍\n");
	exit(1);
	// return (0);
}