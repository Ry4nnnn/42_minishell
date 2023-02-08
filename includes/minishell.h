#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_mini
{
	t_env	*env;
	int		exit;
	int		fd;

}		t_mini;


int 	ft_pwd(void);
int		ft_env(t_env *env);
int		ft_echo(char **args);

#endif
