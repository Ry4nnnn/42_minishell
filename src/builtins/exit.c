#include "minishell.h"

// void	ft_free_cmds(t_mini *mini)
// {
// 	char **temp;

// 	temp = mini->cmds;
// 	while (temp && *temp)
// 	{
// 		free(*temp);
// 		temp++;
// 	}
// 	free (mini->cmds);
// }

void	ft_free_cmds(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->cmds[i])
	{
		printf ("check%s\n", mini->cmds[i]);
		i++;
	}
}

int	ft_exit(t_mini *mini)
{
	// free(mini->prompt);
	// ft_free_cmds(mini);
	ft_lstclear(&mini->envp, clear_env_var);
	ft_lstclear(&mini->envx, clear_env_var);
	rl_clear_history();
	system ("leaks minishell");
	printf("exit 🤍\n");
	return (0);
}