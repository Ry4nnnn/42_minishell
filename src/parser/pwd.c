#include "minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	ft_putendl_fd(cwd, 1);
	free(cwd);
}
