/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:49:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/17 00:09:04 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_exit_status(t_mini *mini, char **pinput, int *i)
{
	char	*str_exit_status;

	(void)mini;
	str_exit_status = ft_itoa(g_errno);
	ft_strexpand(pinput, str_exit_status, *i, 2);
	*i += ft_strlen(str_exit_status) - 1;
	free(str_exit_status);
}

void	expand_var(t_mini *mini, char **pinput, int quote, int *i)
{
	int		n;
	char	*temp_key;
	char	*env_var;

	n = 0;
	env_var = NULL;
	if ((*pinput + *i)[1] == '?')
		return (expand_exit_status(mini, pinput, i));
	while ((ft_isalnum((*pinput + *i)[++n]) || (*pinput + *i)[n] == '_') && (*pinput + *i)[n] != quote) // when the current char is not quote, '$' or space, continue finding the key
		;
	temp_key = ft_strndup((*pinput + *i + 1), n - 1);
	env_var = get_env(mini, temp_key);
	free(temp_key);
	ft_strexpand(pinput, env_var, *i, n);
	*i += ft_strlen(env_var) - 1;
}

void	expand_input(t_mini *mini, char **pinput)
{
	int	quote;
	int	i;
	char	*token;
	int		del_len;

	quote = 0;
	i = -1;
	while ((*pinput)[++i] != 0)
	{
		if (quote != '\'' && (*pinput)[i] == '$')
			expand_var(mini, pinput, quote, &i);
		else if (quote == 0 && ((*pinput)[i] == '\'' || (*pinput)[i] == '"'))
			quote = (*pinput)[i];
		else if (quote == (*pinput)[i])
			quote = 0;
		if ((*pinput)[i] == 0)
			break ;
	}
	i = -1;
	while ((*pinput)[++i] != 0)
	{
		quote = (*pinput)[i];
		token = get_next_token(*pinput, i, quote);
		del_len = ft_strlen(token);
		if (quote != '\'' && ft_strchr(token, '*') != NULL)
		{
			expand_wildcard(mini, &token);
			ft_strexpand(pinput, token, i, del_len);
		}
		i += ft_strlen(token);
		free(token);
		if ((*pinput)[i] == 0)
			break ;	
	}
}