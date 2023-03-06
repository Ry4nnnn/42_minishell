/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/03/06 14:02:10 by codespace        ###   ########.fr       */
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
# include <stdbool.h>
// # include <linux/limits.h> // (for wsl)

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

// Special characters
# define HARD_SPLITERS "(&|"
# define SOFT_SPLITERS " $'\""
# define IGNORE_CHARS "\\;"

// int glob_errno;//not used

enum e_spliters {
	BEGINNING,
	PIPE,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	AND,
	OR,
	INVALID
};

enum e_quotes {
	SINGLE,
	DOUBLE
};

typedef struct s_cmdblock {
	char	*input;
	int		spliter_type;
	int		exit_status;
	int		executed;
	int		in_bracket;
}	t_cmdblock;

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
	t_list	*cmdblock_list;
	int		exit_status;
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

t_list	*split_cmdblocks(char *input);
int	ft_incharset(char *charset, char c);
int	handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list);
int	handle_cmdblock(t_mini *mini, t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock, t_cmdblock *next_cmdblock);
char	*ft_strexpand(char *s, char *insert, int start, int n);

//----------MAIN_DIR----------//

//error.c
void	ft_error(t_mini *mini, char **cmds, char *msg);

//free.c
void	free_Llist(t_mini *mini, t_list *env_list);
void	clear_env_var(void *content);
void	ft_free_cmds(t_mini *mini);

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
char	*get_exec_path(t_mini *mini, char **cmds);
void	exec_non_builtins(t_mini *mini, char **cmds);
void	exec_program(t_mini *mini, char **cmds);

#endif
