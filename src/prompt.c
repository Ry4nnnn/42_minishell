/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:41:45 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 23:41:58 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute the git branch --show-current command in a child process,
 * and store the input result in a pipe.
 * 
 * @param buf pipe fds used to store branch name
 */
static void	exec_git_cmd(int *buf)
{
	pid_t	getter;
	char	*cmd_argv[4];

	getter = fork();
	cmd_argv[0] = "git";
	cmd_argv[1] = "branch";
	cmd_argv[2] = "--show-current";
	cmd_argv[3] = NULL;
	if (getter == 0)
	{
		dup2(buf[WRITE], STDOUT_FILENO);
		dup2(buf[WRITE], STDERR_FILENO);
		close(buf[READ]);
		if (execve("/usr/bin/git", cmd_argv, NULL) != 0)
			exit(EXIT_FAILURE);
	}
	waitpid(getter, NULL, 0);
}

/**
 * @brief Get the current branch name, if not in a git repo then return 🍆.
 * 
 * @return char* branch name
 */
static char	*get_branch_name(void)
{
	char	*branch;
	int		buf[2];

	pipe(buf);
	exec_git_cmd(buf);
	close(buf[WRITE]);
	branch = get_next_line(buf[READ]);
	close(buf[READ]);
	if (branch == NULL)
		return (ft_strdup("🍆"));
	if (ft_strnstr(branch, "not a git repository", ft_strlen(branch)))
	{
		free(branch);
		return (ft_strdup("🍆"));
	}
	branch[ft_strlen(branch) - 1] = 0;
	return (branch);
}

/**
 * @brief to combine the prompts into a single line
 * 
 * @param user user name
 * @param dir current directory path
**/
static void	combine_prompt(t_mini *mini, char *user, char *dir)
{
	char	*temp;
	char	*prompt;
	char	*cur_branch;

	cur_branch = get_branch_name();
	if (!cur_branch)
		cur_branch = ft_strdup("🍆");
	temp = " "BGREEN"❒ ";
	prompt = ft_strjoin(temp, user);
	temp = " ↩ "BCYAN;
	prompt = ft_strjoin_free(prompt, temp);
	prompt = ft_strjoin_free(prompt, dir);
	free(dir);
	temp = " ✘"BBLUE" ("BMAGEN;
	prompt = ft_strjoin_free(prompt, temp);
	prompt = ft_strjoin_free(prompt, cur_branch);
	free(cur_branch);
	temp = BBLUE")\n"BBLUE" ↪ "RESET;
	prompt = ft_strjoin_free(prompt, temp);
	mini->prompt = prompt;
}

/**
 * @brief Get the relative path of the current working directory
 * 
 * @param home home path
 * @param pwd current working directory
 * @return char* relative path
 */
static char	*get_relative_path(char *home, char *pwd)
{
	char	*path;

	path = ft_strnstr(pwd, home, ft_strlen(home)) + ft_strlen(home);
	path = ft_strjoin("~", path);
	free(pwd);
	return (path);
}

//this function is so fucking useless that i have to use one more function
//just to pass norm and displays a prompt that shows the current dir location
//and also to make my minishell looks cooler
void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*pwd;
	char	*home;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	pwd = getcwd(NULL, 0);
	home = get_env(mini, "HOME");
	if (ft_strnstr(pwd, home, ft_strlen(home)))
		pwd = get_relative_path(home, pwd);
	combine_prompt(mini, user, pwd);
}
