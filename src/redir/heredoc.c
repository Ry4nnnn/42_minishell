/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/03/27 12:36:29 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
    char *rl;
    
    cmdblock->pid = fork();
	if (cmdblock->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        finish_pipe(mini);
        pipe(mini->pipes.pipe);
        rl = readline("> ");
        while (rl && ft_strncmp(rl, cmdblock->file_name, ft_strlen(cmdblock->file_name) + 1))
        {
            write(mini->pipes.pipe[WRITE], rl, ft_strlen(rl));
            write(mini->pipes.pipe[WRITE], "\n", 1);
            free(rl);
            rl = readline("> ");
        }
        free(rl);
        close(mini->pipes.pipe[WRITE]);
        return (mini->pipes.pipe[READ]);
    }
    if (mini->pipes.prep_pipe == 0 || cmdblock->was_in_bracket)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}
