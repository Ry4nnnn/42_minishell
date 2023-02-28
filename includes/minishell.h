/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:22:38 by welim             #+#    #+#             */
/*   Updated: 2023/02/28 17:22:43 by welim            ###   ########.fr       */
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
	t_list	*envx;// call export
	char *input;
	char **cmds;
	char oldpwd[1024];
}		t_mini;


//BUILTINS//
void 	ft_pwd(void);
int		ft_env(t_mini *mini);
void	ft_exit(t_mini *mini);
void	ft_unset(t_mini *mini, char **args);
void	ft_export(t_mini *mini, char **key);
void	ft_cd(t_mini *mini);
int		ft_echo(char **input);

void	clear_env_var(void *content);
void	ft_free_cmds(t_mini *mini);
char	*get_env(t_mini *mini, char *key);
void	add_envp_var(t_mini *mini, char *key, char *value);
void	add_envx_var(t_mini *mini, char *key, char *value);
int		valid_input(char *key);
t_env	*check_env_var(t_list *envp, char *key);

void	free_Llist(t_mini *mini, t_list *env_list);
t_list	*ft_lststruct_dup(t_list *lst);
void	sort_env_x(t_mini *mini);

void	lexer(t_mini *mini);

#endif
