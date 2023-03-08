/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:49:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/08 20:59:59 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_exit_status(t_mini *mini, char **input_addr, int *i)
{
	char	*str_exit_status;

	str_exit_status = ft_itoa(mini->exit_status);
	ft_strexpand(input_addr, str_exit_status, *i, 2);
	*i += ft_strlen(str_exit_status) - 1;
	free(str_exit_status);
}

void	expand_var(t_mini *mini, char **input_addr, int quote, int *i)
{
	int		n;
	char	*temp_key;
	char	*env_var;

	n = 0;
	env_var = NULL;
	if ((*input_addr + *i)[1] == '?')
		return (expand_exit_status(mini, input_addr, i));
	while ((ft_isalnum((*input_addr + *i)[++n]) || (*input_addr + *i)[n] == '_') && (*input_addr + *i)[n] != quote) // when the current char is not quote, '$' or space, continue finding the key
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
		if ((*input_addr)[i] == 0)
			return ;
	}
}