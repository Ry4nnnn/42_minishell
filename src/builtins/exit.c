#include "minishell.h"

int	ft_exit(t_mini *mini)
{
	printf("exit 🤍\n");
	free (mini->prompt);
	exit(0);
}