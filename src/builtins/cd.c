#include "minishell.h"

void	ft_cd(t_mini *mini, char **path)
{
	char	*cur_path;

	(void)path;
	cur_path = get_env(mini, "HOME");
	printf ("%s\n", cur_path);
	// chdir()
}
