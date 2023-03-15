/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/03/15 19:11:18 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

# define SUCCESS 0
# define ERROR 1

//----------COLOURS----------//
/* Regular */
# define RESET		"\033[0m"
#define BLACK		"\033[0;30m"
#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define MAGENTA		"\033[0;35m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"

/* Bolded */
#define BBLACK		"\033[1;30m"
#define BRED		"\033[1;31m"
#define BGREEN		"\033[1;32m"
#define BYELLOW		"\033[1;33m"
#define BBLUE		"\033[1;34m"
#define BMAGEN		"\033[1;35m"
#define BCYAN		"\033[1;36m"
#define BWHITE		"\033[1;37m"


// Error Messages
# define CMD_NF "command not found\n"
# define NSFD "No such file or directory\n"
# define PERMISSION_DENIED "Permission denied\n"
# define UNEXPECTED_TOKEN "syntax error near unexpected token"
# define UNCLOSED_QUOTE "Unclosed quote"

// Special characters
# define HARD_SPLITERS "(&|"
# define SOFT_SPLITERS " $'\""
# define IGNORE_CHARS "\\;"

// For pipe
# define READ 0
# define WRITE 1


//----------GLOBAL-VARIABLE----------//

int g_errno;

//----------STRUCTS----------//

enum e_spliters {
	BEGINNING,
	PIPE,
	AND,
	OR,
	INVALID
};

enum e_redir {
	NON_REDIR,
	OUT,
	APPEND,
	IN,
	HEREDOC
};

typedef struct s_cmdblock {
	char	*input;
	int		spliter_type;
	int		exit_status;
	int		need_wait;
	int		in_bracket;
	int		was_in_bracket;
	char	**cmd_argv;
	int		estatus;
	pid_t	pid;
	char	*file_name;
	char	**redir_argv;
}	t_cmdblock;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_pipes
{
	int	pipe[2];
	int	do_pipe;
	int	prep_pipe;
	int	saved_stdout;
	int	saved_stdin;
	int	temp_read_fd;
}	t_pipes;

typedef struct s_mini
{
	t_list	*envp;// call env
	char	*prompt;
	char	**builtins;
	char	**redir;
	char	*input;
	t_list	*cmdblock_list;
	t_pipes	pipes;	
	int		exit_status;
}		t_mini;

//----------BUILTINS----------//
//cd.c
void	ms_cd(t_mini *mini, t_cmdblock *cmdblock);
void	update_pwd(t_mini *mini, char *key);
void	update_oldpwd(t_mini *mini, char *old_path);

//echo.c
int		ms_echo(char **input);
int		is_option(char *input);

//env.c
int		ms_env(t_mini *mini);

//exit.c
void	ms_exit(t_mini *mini);

//export.c
// void	ms_export(t_mini *mini, char **key);
void	ms_export(t_mini *mini, char **input, t_cmdblock *cmdblock);
void	edit_env_var(t_mini *mini, char *key, char *value);

//unset.c
void	ms_unset(t_mini *mini, char **args);
void	rm_env_var(t_mini *ms, t_env *env);

//pwd.c
void 	ms_pwd(void);

//builtins.c
int		check_builtins(t_mini *mini, char *cmds);
int		exec_builtins(t_mini *mini, t_cmdblock *cmdblock);

//builtin_utils.c
int		valid_input(char *key);
t_env	*check_env_var(t_list *env, char *key);

//----------LEXER----------//

t_list	*split_cmdblocks(char *input, int bracket);
int	ft_incharset(char *charset, char c);
int	handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list);
int	handle_cmdblock(t_mini *mini, t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock, t_cmdblock *next_cmdblock);
void	ft_strexpand(char **s, char *insert, int start, int n);
void	expand_input(t_mini *mini, char **input_addr);
void	ft_strremove(char **s, int start, int n);
char	**tokenize_cmd(t_mini *mini, char *input);
int		check_syntax(t_list *cmdblocks_list);
char	*trim_input(char *input);

//----------SPLITERS----------//
void	prepare_pipe(t_mini *mini);
void	do_pipe(t_mini *mini);
void	finish_pipe(t_mini *mini);
void	init_pipe(t_mini *mini);
void	wait_childs(t_list *cmdblocks);

//----------MAIN_DIR----------//

//error.c
void	ft_error(t_mini *mini, char **cmds, char *msg);
void	syntax_error(char *err_msg, char *token);

//free.c
void	free_Llist(t_mini *mini, t_list *env_list);
void	clear_env_var(void *content);
void	ft_free(t_mini *mini, int type);

//main.c
void	add_env_var(t_mini *mini, char *key, char *value);
int		init_env(t_mini *mini, char **ev);
char	*get_env(t_mini *mini, char *key);
void	init_prompt(t_mini *mini);
int		handle_commands(t_mini *mini, t_cmdblock *cmdblock);

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
int		exec_non_builtins(t_mini *mini, t_cmdblock *cmdblock);
int		exec_program(t_mini *mini, t_cmdblock *cmdblock);

// redir.c
int	check_redir_type(t_mini *mini, t_cmdblock *cmdblock);
void	handle_io(int fd, int std_file_no);
void	redir_out(t_mini *mini, t_cmdblock *cmdblock);
void	redir_in(t_cmdblock *cmdblock);
void	call_redir(t_mini *mini, t_cmdblock *cmdblock);

#endif
