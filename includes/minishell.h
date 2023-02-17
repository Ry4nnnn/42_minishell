#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

# define SUCCESS 0
# define ERROR 1

int glob_errno;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_mini
{
	int		exit;
	char	*prompt;
	char	**builtins;
	char	**operators;
	t_list	*envp;
}		t_mini;

int 	ft_pwd(void);
int		ft_env(t_mini *mini);
int		ft_exit(t_mini *mini);
void	ft_unset(t_mini *mini, char **args);
void		ft_export(t_mini *mini, char **key);
// int		ft_echo(char *input);

#endif
