/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:41:45 by welim             #+#    #+#             */
/*   Updated: 2023/03/13 21:11:56 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_branch_name(void)
{
	char	*argv[] = {"git", "branch", NULL};
	pid_t	pid;
	int		pipefd[2];
	char	buf[1024];
	ssize_t	nread;
	char	*current_branch;
	char	*line;

	if ((access("../.git", F_OK) == -1) && (access(".git", F_OK) == -1)) //only works for cur and sub directory
		return (NULL);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// Child process
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (close(pipefd[0]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		if (execve("/usr/bin/git", argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		current_branch = NULL;
		if (close(pipefd[1]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		if ((nread = read(pipefd[0], buf, 1024 - 1)) == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		buf[nread] = '\0';
		line = strtok(buf, "\n");
		if (close(pipefd[0]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		while (line != NULL)
		{
			if (line[0] == '*' && line[1] == ' ')
			{
				current_branch = ft_strdup(line + 2);
				break;
			}
			line = strtok(NULL, "\n");
		}
		return (current_branch);
	}
	return (NULL);
}

//to strjoin the prompt tgt
static void	combine_prompt(t_mini *mini, char *user, char *dir)
{
	char	*prompt0;
	char	*prompt1;
	char	*cur_branch;

	cur_branch = get_branch_name();
	if (!cur_branch)
		cur_branch = ft_strdup("?");
	prompt0 = ft_strjoin(GREEN , user);
	prompt1 = ft_strjoin(prompt0, " @ ");
	free(prompt0);
	prompt0 = ft_strjoin(prompt1, dir);
	free(prompt1);
	prompt1 = ft_strjoin(prompt0, " (");
	free(prompt0);
	prompt0 = ft_strjoin(prompt1, cur_branch);
	free (cur_branch);
	free(prompt1);
	prompt1 = ft_strjoin(prompt0, ") ");
	free(prompt0);
	prompt0 = ft_strjoin(prompt1, " $ ");
	free(prompt1);
	prompt1 = ft_strjoin(prompt0, RESET);
	free (prompt0);
	mini->prompt = prompt1;
}

//this function is so fucking useless that i have to use one more function
//just to pass norm and displays a prompt that shows the current dir location
//and also to make my minishell looks cooler
void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*dir;
	char	*home;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	dir = get_env(mini, "PWD");
	home = get_env(mini, "HOME");
	if (home == NULL)
		dir = "🤷";
	else
	{
		if (dir != NULL && ft_strcmp(dir, home) == 0)
			dir = "~";
		else if (dir != NULL)
			dir = ft_strrchr(dir, '/');
		else
			dir = "🤷";
	}
	combine_prompt(mini, user, dir);
}
