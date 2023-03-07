/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:41:45 by welim             #+#    #+#             */
/*   Updated: 2023/03/06 20:28:04 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to strjoin the prompt tgt
static void	combine_prompt(t_mini *mini, char *user, char *dir)
{
	char	*prompt0;
	char	*prompt1;

	prompt0 = ft_strjoin(GREEN , user);
	prompt1 = ft_strjoin(prompt0, " @ ");
	free(prompt0);
	prompt0 = ft_strjoin(prompt1, dir);
	free(prompt1);
	prompt1 = ft_strjoin(prompt0, " $ ");
	free(prompt0);
	prompt0 = ft_strjoin(prompt1, RESET);
	free (prompt1);
	mini->prompt = prompt0;
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
