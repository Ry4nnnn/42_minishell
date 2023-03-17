/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:49:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/17 16:15:41 by wangxuerui       ###   ########.fr       */
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

/**
 * @brief expand the $ variables
 * a variable is from $ until the first char that is
 * either ' ', '"' or special characters
 * 
 * @param mini 
 * @param pinput 
 * @param quote 
 * @param i 
 */
void	expand_var(t_mini *mini, char **pinput, int quote, int *i)
{
	int		n;
	char	*temp_key;
	char	*env_var;

	n = 1;
	env_var = NULL;
	if ((*pinput + *i)[1] == '?')
		return (expand_exit_status(mini, pinput, i));
	while ((ft_isalnum((*pinput + *i)[n])
		|| (*pinput + *i)[n] == '_')
		&& (*pinput + *i)[n] != quote)
		n++;
	temp_key = ft_strndup((*pinput + *i + 1), n - 1);
	env_var = get_env(mini, temp_key);
	free(temp_key);
	ft_strexpand(pinput, env_var, *i, n);
	*i += ft_strlen(env_var) - 1;
}

void	expand_wildcard(t_mini *mini, char **pinput)
{
	int		i;
	int		quote;
	char	*token;
	int		is_export;

	i = -1;
	is_export = 0;
	while ((*pinput)[++i] != 0)
	{
		quote = (*pinput)[i];
		token = get_next_token(*pinput, i, quote);
		if (i == 0 && ft_strcmp(token, "export") == 0)
			is_export = 1;
		if (quote != '\'' && quote != '"' && ft_strchr(token, '*') != NULL)
		{
			if (!(is_export && ft_strnstr(token, "=*", ft_strlen(token))))
				wildcard(mini, pinput, &token, i);
		}
		i += ft_strlen(token);
		free(token);
		if ((*pinput)[i] == 0)
			return ;
	}
}

void	expand_input(t_mini *mini, char **pinput)
{
	int		quote;
	int		i;

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
	expand_wildcard(mini, pinput);
}
