/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/03/01 17:38:27 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <termios.h>

# define SUCCESS 0
# define ERROR 1

//COLORS//
# define RESET "\033[0m"
# define WHITE "\033[0;37m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define UNDERLINE = "\033[4m"
# define HEADER = "\033[95m"
# define OKBLUE = "\033[94m"
# define OKCYAN = "\033[96m"
# define WARNING = "\033[93m"
# define BOLD = "\033[1m"

// int glob_errno;//not used

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_mini
{
	// int		exit;// not used
	char	*prompt;
	char	**builtins;
	char	**operators;
	t_list	*envp;// call env
	// t_list	*envx;// call export
	char *input;
	char **cmds;
	char oldpwd[1024];
}		t_mini;


//----------BUILTINS----------//
//cd.c
void	ft_cd(t_mini *mini);
void	update_pwd(t_mini *mini, char *key);
void	update_oldpwd(t_mini *mini, char *old_path);

//echo.c
int		ft_echo(char **input);
int		is_option(char *input);

//env.c
int		ft_env(t_mini *mini);

//exit.c
void	ft_exit(t_mini *mini);

//export.c
void	ft_export(t_mini *mini, char **key);
void	print_export_x(t_mini *mini);
t_env	*check_env_var(t_list *env, char *key);
void	edit_env_var(t_mini *mini, char *key, char *value);
void	edit_envx_var(t_mini *mini, char *keyx, char *valuex);

//unset.c
void	ft_unset(t_mini *mini, char **args);
void	del_env_var(t_mini *ms, t_env *env);
void	del_envx_var(t_mini *ms, t_env *env);

//pwd.c
void 	ft_pwd(void);

//error.c
void	ft_error(t_mini *mini, char **cmds);

//free.c
void	free_Llist(t_mini *mini, t_list *env_list);
void	clear_env_var(void *content);
void	ft_free_cmds(t_mini *mini);

//main.c
void	add_envp_var(t_mini *mini, char *key, char *value);
void	add_envx_var(t_mini *mini, char *key, char *value);
int		init_env(t_mini *mini, char **ev);
char	*get_env(t_mini *mini, char *key);
void	init_prompt(t_mini *mini);
int	handle_commands(t_mini *mini, char **cmds);
void	signal_handler(int num);
t_list	*ft_lststruct_dup(t_list *lst);

//utils.c
int		valid_input(char *key);
void	get_key_value(char *arg, char **key, char **value);
void	sort_env_x(t_mini *mini);

//lexer.c
void	lexer(t_mini *mini);

//signal.c
void	signal_handler(int signo);
void	init_signal(void);

#endif
