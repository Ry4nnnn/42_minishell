/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/03/05 18:17:03 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <linux/limits.h> // (for wsl)

# define SUCCESS 0
# define ERROR 1

//COLORS//
# define RESET		"\033[0m"
# define WHITE		"\033[0;37m"
# define GREEN		"\033[0;32m"
# define RED		"\033[0;31m"
# define UNDERLINE	"\033[4m"
# define HEADER		"\033[95m"
# define OKBLUE		"\033[94m"
# define OKCYAN		"\033[96m"
# define WARNING	"\033[93m"
# define BOLD		"\033[1m"

// Error Messages
# define CMD_NF "command not found\n"
# define NSFD "No such file or directory\n"

// int glob_errno;//not used

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_mini
{
	t_list	*envp;// call env
	char	*prompt;
	char	**builtins;
	char	**operators;
	char	*input;
	char	**cmds;
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
void	edit_env_var(t_mini *mini, char *key, char *value);

//unset.c
void	ft_unset(t_mini *mini, char **args);
void	rm_env_var(t_mini *ms, t_env *env);

//pwd.c
void 	ft_pwd(void);

//builtins.c
int		check_builtins(t_mini *mini, char *cmds);
int		exec_builtins(t_mini *mini, char **cmds);

//builtin_utils.c
int		valid_input(char *key);
t_env	*check_env_var(t_list *env, char *key);

//----------LEXER----------//

void	lexer(t_mini *mini);

//----------MAIN_DIR----------//

//error.c
void	ft_error(t_mini *mini, char **cmds, char *msg);

//free.c
void	free_Llist(t_mini *mini, t_list *env_list);
void	clear_env_var(void *content);
void	ft_free_cmds(t_mini *mini);
void	ft_free(t_mini *mini, int type);

//main.c
void	add_env_var(t_mini *mini, char *key, char *value);
int		init_env(t_mini *mini, char **ev);
char	*get_env(t_mini *mini, char *key);
void	init_prompt(t_mini *mini);
int		handle_commands(t_mini *mini, char **cmds);

//utils.c
int		valid_input(char *key);
void	get_key_value(char *arg, char **key, char **value);

//signal.c
void	signal_handler(int signo);
void	init_signal(void);

//prompt.c
void	init_prompt(t_mini *mini);

//execve.c
char	**ft_llto2darr(t_list *list);
char	*get_exec_path(t_mini *mini, char **cmds);
void	exec_non_builtins(t_mini *mini, char **cmds);
void	exec_program(t_mini *mini, char **cmds);

#endif
