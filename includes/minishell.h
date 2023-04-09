/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/04/09 17:31:09 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------LIBRARIES----------//
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include <dirent.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

//----------COLOURS----------//
/* Regular */
# define RESET		"\033[0m"
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

/* Bolded */
# define BBLACK		"\033[1;30m"
# define BRED		"\033[1;31m"
# define BGREEN		"\033[1;32m"
# define BYELLOW	"\033[1;33m"
# define BBLUE		"\033[1;34m"
# define BMAGEN		"\033[1;35m"
# define BCYAN		"\033[1;36m"
# define BWHITE		"\033[1;37m"

// Error Messages
# define CMD_NF "command not found\n"
# define NSFD "No such file or directory\n"
# define PERMISSION_DENIED "Permission denied\n"
# define UNEXPECTED_TOKEN "syntax error near unexpected token"
# define UNCLOSED_QUOTE "Unclosed quote"
# define NOHOME "HOME not set\n"
# define NOTDIR "Not a directory\n"
# define ISDIR "is a directory\n"
# define INVALID_IDENTIFIER "not a valid identifier\n"
# define TOOMANYARGS "too many arguments\n"
# define NONNUMERICARG "numeric argument required\n"

// Special characters
# define HARD_SPLITERS "(&|"
# define SOFT_SPLITERS " $'\""
# define IGNORE_CHARS "\\;"

// Redir Secret Code 😏
# define S_IN "\1"
# define S_HEREDOC "\1\1"
# define S_OUT "\3"
# define S_APPEND "\3\3"

// For pipe
# define READ 0
# define WRITE 1

# define SUCCESS 0
# define ERROR 1

//----------GLOBAL-VARIABLE----------//

int	g_errno;

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
	char	**cmd_argv;
	int		estatus;
	pid_t	pid;
	pid_t	h_pid;
	char	*infile;
	char	*outfile;
}	t_cmdblock;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_pipes
{
	int		pipe[2];
	int		do_pipe;
	int		prep_pipe;
	int		saved_stdout;
	int		saved_stdin;
	int		temp_read_fd;
	int		h_pipe[2];
	int		hd_estatus;
	int		is_redir_in;
}	t_pipes;

typedef struct s_mini
{
	t_list	*envp;
	char	**env;
	char	*exec_path;
	char	*prompt;
	char	*builtins[8];
	char	*redir[5];
	char	*input;
	t_list	*cmdblock_list;
	t_pipes	pipes;
	int		fd_in;
	int		fd_out;
}		t_mini;

//----------BUILTINS----------//
int		ms_cd(t_mini *mini, t_cmdblock *cmdblock);
int		ms_echo(t_mini *mini, char **input);
int		ms_env(t_mini *mini);
int		ms_exit(t_mini *mini, t_cmdblock *cmdblock);
int		ms_export(t_mini *mini, t_cmdblock *cmdblock);
void	ms_unset(t_mini *mini, char **cmd_argv);
void	ms_pwd(void);

//builtins.c
int		check_builtins(t_mini *mini, char *cmds);
int		exec_builtins(t_mini *mini, t_cmdblock *cmdblock);

//builtin_utils.c
int		valid_input(char *key);
t_env	*check_env_var(t_list *env, char *key);

// env_utils.c
char	*get_env(t_mini *mini, char *key);
void	add_env_var(t_mini *mini, char *key, char *value);

//----------LEXER----------//

t_list	*split_cmdblocks(char *input, int bracket);
char	*skip_spliter(char *input, int spliter_type);
int		get_spliter_type(char *input);
void	ft_strexpand(char **s, char *insert, int start, int n);
int		expand_input(t_mini *mini, char **pinput);
char	**tokenize_cmd(t_mini *mini, char *input);
char	*get_next_token(char *input, int i, int quote);
int		check_syntax(t_mini *mini, t_list *cmdblocks_list);
char	*trim_input(char *input);
int		wildcard(t_mini *mini, char **pinput, char **ptoken, int i);
int		name_pattern_match(char *wildcard, char *name, int pattern_len);
int		get_pattern_len(char *str);
void	sort_names_list(t_list **names);
int		detect_quote_token(char *input, int quote);
int		detect_normal_token(char *input);

//----------REDIR----------//
void	prepare_pipe(t_mini *mini);
void	do_pipe(t_mini *mini);
void	finish_pipe(t_mini *mini);
void	init_pipe(t_mini *mini);
void	handle_io(int fd, int std_file_no);
int		exec_redir(t_mini *mini, t_cmdblock *cmdblock);
void	done_redir(t_mini *mini, int heredoc);
int		redir_out(t_mini *mini, char *file, int type);
int		redir_in(t_mini *mini, t_cmdblock *cmdblock, char *file, int type);
void	heredoc(t_mini *mini, t_cmdblock *cmdblock);
int		ms_open(t_mini *mini, char *filename, int flags, int mode);
int		check_redir_type(t_mini *mini, t_cmdblock *cmdblock);
int		redir_error(t_mini *mini, t_cmdblock *cmdblock);
int		check_for_redir(t_mini *mini, char *str);
int		get_iofile(t_mini *mini, t_cmdblock *cmdblock, int i);
int		check_is_redir(char *str);

//----------EXECUTOR----------//

int		handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list);
int		handle_cmdblock(t_mini *mini, t_cmdblock *cmdblock);
int		executor(t_mini *mini, t_cmdblock *cmdblock);
int		exec_commands(t_mini *mini, t_cmdblock *cmdblock);
int		exec_program(t_mini *mini, t_cmdblock *cmdblock);
char	*env_to_str(void *arg);
char	*get_exec_path(t_mini *mini, char **cmds);
void	get_exec_argv(t_mini *mini, t_cmdblock *cmdblock);
int		get_exit_status(t_list *cmdblock_list);
void	prepare_handling(t_mini *mini, t_list *curr_node,
			t_cmdblock *cmdblock);
int		should_execute(t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock);
int		get_program_permission(t_mini *mini, t_cmdblock *cmdblock);
char	*try_cmd_path(char *path, char *cmd);

//----------MAIN_DIR----------//

//error.c
void	cmd_error(t_mini *mini, char **cmds, char *msg);
int		syntax_error(t_mini *mini, char *err_msg, char *token);
void	cmd_arg_error(t_mini *mini, char **cmds, char *msg);
void	identifier_error(t_mini *mini, char **cmds, int i, char *msg);

//free.c
void	clear_env_var(void *content);
void	free_cmdblock(void *arg);
void	ms_free(t_mini *mini);

//utils.c
void	wait_childs(t_list *cmdblocks);

//signal.c
void	signal_handler(int signo);
void	signal_handler_exec(int signo);
void	init_signal(void);

//prompt.c
void	init_prompt(t_mini *mini);

// init.c
void	ms_init(t_mini *mini, char **envp);
void	ms_loop_init(t_mini *mini);

#endif
