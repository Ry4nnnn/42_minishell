/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/17 18:32:16 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//take in ev from main func and add it into a linked list
int		init_env(t_mini *mini, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key = ft_strndup(*ev, (ft_strlen(*ev) - ft_strlen(value)));
		value = ft_strdup(value + 1);
		add_env_var(mini, key, value);
		ev++;
	}
	return (0);
}

// to initialize all the builtins
// dont have to NULL the last one (calloc alrdy did it)
void init_builtins(t_mini *mini)
{
	mini->builtins[0] = "pwd";
	mini->builtins[1] = "env";
	mini->builtins[2] = "echo";
	mini->builtins[3] = "cd";
	mini->builtins[4] = "unset";
	mini->builtins[5] = "export";
	mini->builtins[6] = "exit";
	mini->builtins[7] = NULL;
}

void	init_redir(t_mini *mini)
{
	mini->redir[0] = ">";
	mini->redir[1] = ">>";
	mini->redir[2] = "<";
	mini->redir[3] = "<<";
	mini->redir[4] = NULL;
}

int		handle_commands(t_mini *mini, t_cmdblock *cmdblock)
{
	cmdblock->redir_argv = NULL;
	signal(SIGINT, SIG_IGN);
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	if (check_builtins(mini, cmdblock->cmd_argv[0]) == 1)// it is a builtin!
	{
		// printf ("> test\n");
		return (exec_builtins(mini, cmdblock));// redir
	}
	else if (ft_strchr(cmdblock->cmd_argv[0], '/') != NULL)// program
	{
		return (exec_program(mini, cmdblock));
	}
	else if (get_env(mini, "PATH") == NULL)// error for empty path
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	else // non builtins
	{
		printf ("> test\n"); // here
		return (exec_non_builtins(mini, cmdblock));// execve //redir
	}
	return (0);
}

void	free_cmdblock(void *arg)
{
	t_cmdblock	*cmdblock;

	if (arg == NULL)
		return ;
	cmdblock = (t_cmdblock *)arg;
	free(cmdblock->input);
	free(cmdblock);
}

int	get_exit_status(t_list *cmdblock_list)
{
	t_cmdblock	*cmdblock;
	int		exit_status;

	exit_status = 0;
	while (cmdblock_list != NULL)
	{
		cmdblock = (t_cmdblock *)cmdblock_list->content;
		if (cmdblock->spliter_type == OR && cmdblock->exit_status == 0) // if executed and successed and is in OR logic
				return (0);
		else if (cmdblock->spliter_type == AND) // if executed and in AND logic
		{
			if ((cmdblock->exit_status == 0 && exit_status == 0) || (cmdblock->exit_status != 0)) // if (success and previous are all success) or (not success)
				exit_status = cmdblock->exit_status;
		}
		else
			exit_status = cmdblock->exit_status;
		cmdblock_list = cmdblock_list->next;
	}
	return (exit_status);
}

int	handle_cmdblock(t_mini *mini, t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock, t_cmdblock *next_cmdblock)
{
	cmdblock->need_wait = 0;
	if (prev_cmdblock != NULL)
	{
		if (cmdblock->spliter_type == AND && prev_cmdblock->exit_status != 0)
			return (0);
		else if (cmdblock->spliter_type == OR && prev_cmdblock->exit_status == 0)
			return (0);
	}
	if (cmdblock->spliter_type == PIPE) // if the current cmdblock is piping, do the piping
		mini->pipes.do_pipe = 1;
	if (next_cmdblock != NULL && next_cmdblock->spliter_type == PIPE) // if the next cmdblock is piping, prepare the pipe here
		mini->pipes.prep_pipe = 1;
	if (cmdblock->in_bracket)
		return (handle_cmdblocks(mini, split_cmdblocks(cmdblock->input, 1)));
	expand_input(mini, &cmdblock->input);
	// printf("expanded: %s\n", cmdblock->input);
	cmdblock->cmd_argv = tokenize_cmd(mini, cmdblock->input);
	cmdblock->exit_status = handle_commands(mini, cmdblock);
	ft_free2darr((void **)cmdblock->redir_argv);
	ft_free2darr((void **)cmdblock->cmd_argv);
	return (cmdblock->exit_status);
}

int	handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list)
{
	t_list	*temp;
	t_cmdblock	*prev_cmdblock;
	t_cmdblock	*cmdblock;
	t_cmdblock	*next_cmdblock;
	int		exit_status;

	temp = cmdblocks_list;
	prev_cmdblock = NULL;
	if (check_syntax(mini, cmdblocks_list) == 0)
	{
		ft_lstclear(&cmdblocks_list, free_cmdblock);
		return (258);
	}
	while (temp != NULL)
	{
		cmdblock = (t_cmdblock *)temp->content;
		if (temp->next == NULL)
			next_cmdblock = NULL;
		else
			next_cmdblock = (t_cmdblock *)temp->next->content;
		cmdblock->exit_status = handle_cmdblock(mini, prev_cmdblock, cmdblock, next_cmdblock);
		prev_cmdblock = cmdblock;
		temp = temp->next;
	}
	wait_childs(cmdblocks_list);
	exit_status = get_exit_status(cmdblocks_list);
	ft_lstclear(&cmdblocks_list, free_cmdblock);
	return (exit_status);
}

//expand then tokenize
//lexer, pipes, heredoc, redirection
int main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.envp = NULL;
	mini.exit_status = 0;
	init_env(&mini, envp);
	init_builtins(&mini);
	init_redir(&mini);
	g_errno = 0;
	while (1)
	{
		init_signal();
		init_prompt(&mini);
		init_pipe(&mini);
		mini.input = readline(mini.prompt);
		if (mini.input == NULL)
			ms_exit(&mini);
		mini.input = trim_input(mini.input);
		if (mini.input[0] == '\0')
		{
			ft_free(&mini, 4);
			continue ;
		}
		mini.cmdblock_list = split_cmdblocks(mini.input, 0);
		g_errno = handle_cmdblocks(&mini, mini.cmdblock_list);
		add_history(mini.input);
		ft_free(&mini, 4);
	}
	return(0);
}

