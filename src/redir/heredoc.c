/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/03/22 22:29:02 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*    get_keyword(t_cmdblock *cmdblock)
{
    int i;

    i = 0;
    while(cmdblock->cmd_argv[i])
    {
        if (ft_strncmp(cmdblock->cmd_argv[i], "<<", 3) == 0)
            return (cmdblock->cmd_argv[i + 1]);
        i++;
    }
    return (NULL);
}


int    heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
    (void)mini;
    int     fd;
    char    *rl;
    char *keyword;

    while (true)
    {
        fd = open(".tmp", O_CREAT | O_APPEND | O_WRONLY, 0644);
        rl = readline("> ");
        keyword = get_keyword(cmdblock);
        if (ft_strcmp(keyword, rl) == 0)
            break ;
        write(fd, rl, ft_strlen(rl));
        write(fd, "\n", 1);
        close (fd);
        free (rl);
    }
    dup2 (fd, 0);
    unlink(".tmp");
    return (0);
}
