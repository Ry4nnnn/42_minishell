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

typedef struct s_arg
{
	int 	ac;
	char	**av;
}		t_arg;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

// typedef struct	s_envp
// {
// 	char	*key;
// 	char	*token;
// }	t_envp;

typedef struct s_mini
{
	t_env	*env;
	int		exit;
	int		fd;
	char	*prompt;

}		t_mini;


int 	ft_pwd(void);
int		ft_env(t_env *env);
int		ft_echo(char **args);
int		ft_export(char **args, t_env *env, t_env *secret);

#endif
