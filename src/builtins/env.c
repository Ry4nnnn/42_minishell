/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welim <welim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:06 by welim             #+#    #+#             */
/*   Updated: 2023/03/23 16:54:31 by welim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**temp;
	int		i;

	if (ft_strncmp(cmdblock->cmd_argv[1], "echo", 5) == 0)
	{
		i = ft_2darrlen((void **)cmdblock->cmd_argv);
		temp = malloc(sizeof(char *) * i);
		i = 1;
		while (cmdblock->cmd_argv[i])
		{
			temp[i - 1] = ft_strdup(cmdblock->cmd_argv[i]);
			i++;
		}
		ms_echo(mini, temp);
		ft_free2darr((void **)temp);
	}
	else if (ft_strncmp(cmdblock->cmd_argv[1], "pwd", 4) == 0)
		ms_pwd();
	else if (ft_strncmp(cmdblock->cmd_argv[1], "cd", 3) == 0)
		return (0);
	else
		return (exec_commands(mini, cmdblock));
	return (0);
}

/**
 * @brief Builtin command env
 * 
 * @param mini
 * @param cmdblock
 * @return int
 */
int	ms_env(t_mini *mini, t_cmdblock *cmdblock)
{
	t_list	*env_list;
	t_env	*env_node;

	if (cmdblock->cmd_argv[1] != NULL)
	{
		if (!(ft_strncmp(cmdblock->cmd_argv[1], "env", 4) == 0))
			return (handle_env(mini, cmdblock));
	}
	env_list = mini->envp;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->value != NULL)
			printf ("%s=%s\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
	return (0);
}
