/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:49:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/07 14:28:09 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	expand_var(t_mini *mini, char **input_addr, int quote, int *i)
{
	int		n;
	char	*temp_key;
	char	*env_var;

	n = 0;
	env_var = NULL;
	while ((*input_addr + *i)[++n] != quote && (*input_addr + *i)[n] != '$' && (*input_addr + *i)[n] != ' ') // when the current char is not quote, '$' or space, continue finding the key
		;
	temp_key = ft_strndup((*input_addr + *i + 1), n - 1);
	env_var = get_env(mini, temp_key);
	free(temp_key);
	ft_strexpand(input_addr, env_var, *i, n);
	*i += ft_strlen(env_var) - 1;
}

void	expand_input(t_mini *mini, char **input_addr)
{
	int	quote;
	int	i;

	quote = 0;
	i = -1;
	while ((*input_addr)[++i] != 0)
	{
		if (quote != '\'' && (*input_addr)[i] == '$')
			expand_var(mini, input_addr, quote, &i);
		else if (quote == 0 && ((*input_addr)[i] == '\'' || (*input_addr)[i] == '"'))
			quote = (*input_addr)[i];
		else if (quote == (*input_addr)[i])
			quote = 0;
	}
}