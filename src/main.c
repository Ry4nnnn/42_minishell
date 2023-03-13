/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:19 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 16:27:18 by welim            ###   ########.fr       */
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
	char	**builtins;

	builtins = ft_calloc(7 + 1, sizeof(char *));
	builtins[0] = "pwd";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "cd";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	mini->builtins = builtins;
}

void	init_redir(t_mini *mini)
{
	char	**redir;

	redir = ft_calloc(4 + 1, sizeof(char *));
	redir[0] = ">";
	redir[1] = ">>";
	redir[2] = "<";
	redir[3] = "<<";
	mini->redir = redir;
}

int		handle_commands(t_mini *mini, t_cmdblock *cmdblock)
{
	signal(SIGINT, SIG_IGN);
	if (check_builtins(mini, cmdblock->cmd_argv[0]) == 1)// it is a builtin!
	{
		return (exec_builtins(mini, cmdblock->cmd_argv));
	}
	else if (get_env(mini, "PATH") == NULL)
	{
		ft_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	else if (ft_strchr(cmdblock->cmd_argv[0], '/') != NULL)
	{
		if (access(cmdblock->cmd_argv[0], F_OK) == 0)
		{
			if (access(cmdblock->cmd_argv[0], X_OK) == 0)
				return (exec_program(mini, cmdblock));
			ft_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
			return (126);
		}
		ft_error(mini, cmdblock->cmd_argv, NSFD);
	}
	else // non builtins
	{
		// exec_redir(mini, cmdblock);
		return (exec_non_builtins(mini, cmdblock));
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
		if (cmdblock->spliter_type == OR && cmdblock->executed && cmdblock->exit_status == 0) // if executed and successed and is in OR logic
				return (0);
		else if (cmdblock->spliter_type == AND && cmdblock->executed) // if executed and in AND logic
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
	(void)prev_cmdblock;
	if (cmdblock->spliter_type == PIPE) // if the current cmdblock is piping, do the piping
		mini->pipes.do_pipe = 1;
	if (next_cmdblock != NULL && next_cmdblock->spliter_type == PIPE) // if the next cmdblock is piping, prepare the pipe here
		mini->pipes.prep_pipe = 1;
	if (cmdblock->in_bracket)
		return (handle_cmdblocks(mini, split_cmdblocks(cmdblock->input)));
	expand_input(mini, &cmdblock->input);
	// printf("expanded: %s\n", cmdblock->input);
	cmdblock->cmd_argv = tokenize_cmd(mini, cmdblock->input);
	cmdblock->exit_status = handle_commands(mini, cmdblock);
	ft_free2darr((void *)cmdblock->cmd_argv);
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
	temp = cmdblocks_list;
	while (temp != NULL)
	{
		waitpid(((t_cmdblock *)temp->content)->pid, &((t_cmdblock *)temp->content)->estatus, WUNTRACED);
		if (WIFEXITED(((t_cmdblock *)temp->content)->estatus))
		{
			// printf("%i exited normally\n", (int)((t_cmdblock *)temp->content)->pid);
			WEXITSTATUS(((t_cmdblock *)temp->content)->estatus);
		}
		if (WIFSIGNALED(((t_cmdblock *)temp->content)->estatus))
		{
			// printf("%i exited abnormally\n", (int)((t_cmdblock *)temp->content)->pid);
			WTERMSIG(((t_cmdblock *)temp->content)->estatus);
		}
		// printf("pid: %i, errno: %i\n", (int)((t_cmdblock *)temp->content)->pid, errno);
		temp = temp->next;
	}
	exit_status = get_exit_status(cmdblocks_list);
	// printf("exit_status: %i\n", exit_status);
	ft_lstclear(&cmdblocks_list, free_cmdblock);
	return (exit_status);
}

//expand then tokenize
//lexer, pipes, heredoc, redirection
int main(int ac, char **av, char **ev)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.envp = NULL;
	mini.exit_status = 0;
	init_env(&mini, ev);
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
			ft_exit(&mini);
		if (mini.input[0] == '\0')
		{
			ft_free(&mini, 4);
			continue ;
		}
		mini.cmdblock_list = split_cmdblocks(mini.input);
		g_errno = handle_cmdblocks(&mini, mini.cmdblock_list);
		// printf("g_errno: %i\n", g_errno);
		add_history(mini.input);
		ft_free(&mini, 4);
	}
	return(0);
}

