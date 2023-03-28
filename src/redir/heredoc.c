/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/03/28 15:09:41 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
    char *rl;

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
