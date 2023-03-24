/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:39:01 by welim             #+#    #+#             */
/*   Updated: 2023/03/24 21:01:03 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_keyword(t_cmdblock *cmdblock)
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
    // int     fd;
    char    *rl;
    // char *keyword;

    pipe(mini->pipes.pipe);
    // fd = open(".tmp", O_CREAT | O_APPEND | O_WRONLY, 0644);
    // write(2, "ONLY ONCE\n", 10);
    // write(2, cmdblock->cmd_argv[0], ft_strlen(cmdblock->cmd_argv[0]));
    // write(2, "\n", 1);
    // write(2, "keyword is ", 12);
    // write(2, get_keyword(cmdblock), ft_strlen(get_keyword(cmdblock)));
    // write(2, "\n", 1);
    // signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
    while (true)
    {
        rl = readline("> ");
        // keyword = get_keyword(cmdblock);
        // write(2, "rl: ", 3);
        // write(2, rl, ft_strlen(rl));
        // write(2, "\n", 1);
        write(2, "file_name: ", 12);
        write(2, cmdblock->file_name, ft_strlen(cmdblock->file_name));
        write(2, "\n", 1);
        if (ft_strcmp(cmdblock->file_name, rl) == 0)
        {
            free (rl); // free limiter
            unlink(".tmp");
            return (mini->pipes.pipe[READ]);
            // // write(2, "BREAKED\n", 12);
            // return(0) ;
        }
        write(mini->pipes.pipe[WRITE], rl, ft_strlen(rl));
        write(mini->pipes.pipe[WRITE], "\n", 1);
        free (rl);
    }
    free (rl); // free limiter
    unlink(".tmp");
    return (mini->pipes.pipe[READ]);
}

// char	*tempfile_gen(int i)
// {
// 	char	*s;
// 	char	*ret;

// 	s = ft_itoa(i);
// 	ret = ft_strjoin("temp", s);
// 	free(s);
// 	return (ret);
// }

// void    heredoc_routine(char *s, char *file)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	while (1)
// 	{
// 		str = readline("heredoc > ");
//         // write(2, "[\"", 2);
//         // write(2, str, ft_strlen(str));
//         // write(2, "\" = \"", 5);
//         // write(2, s, ft_strlen(s));
//         // write(2, "\"]", 2);
//         // write(2, "\n", 1);
//         // sleep(1);
// 		if (!ft_strcmp(str, s))
// 			break ;
// 		// if (ft_strchr(str, '$'))
// 		// 	str = env_extract(str, 1);
// 		ft_putstr_fd((ft_strjoin_free(str, ft_strdup("\n"))), fd);
// 	}
// 	close(fd);
//     // exit(0);
// }

// int	heredoc(t_mini *mini, t_cmdblock *cmdblock, int i)
// {
// 	int		fd;
//     // int     pid;
//     // int     status;
// 	char	*file;

//     (void)mini;
// 	file = tempfile_gen(i);
// 	// pid = fork();
// 	// signal(SIGINT, ctrl_c);
// 	// signal(SIGQUIT, SIG_IGN);
// 	// if (pid == 0)
// 	heredoc_routine(cmdblock->file_name, file);
//     // printf("%zu\n", ft_strlen(cmdblock->file_name));
//     // write(2, cmdblock->file_name, ft_strlen(cmdblock->file_name));
//     // write(2, "\n", 1);
// 	// waitpid(pid, &status, 0);
//     write(2, "ABOUT TO OPEN AGAIN\n", 21);
// 	fd = open(file, O_RDONLY, 0644);
// 	unlink(file);
// 	free(file);
// 	return (fd);
// }
