/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:49:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/08 17:00:41 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the $? variable, expand to g_errno.
 * 
 * @param mini 
 * @param pinput input string ptr
 * @param i input string index ptr
 */
static int	expand_exit_status(t_mini *mini, char **pinput, int *i)
{
	char	*str_exit_status;

	(void)mini;
	str_exit_status = ft_itoa(g_errno);
	ft_strexpand(pinput, str_exit_status, *i, 2);
	*i += ft_strlen(str_exit_status) - 1;
	free(str_exit_status);
	return (1);
}

/**
 * @brief expand the $ variables
 * a variable is from $ until the first char that is
 * either ' ', '"' or special characters
 * 
 * @param mini 
 * @param pinput input string ptr
 * @param quote type of quote
 * @param i input string index ptr
 */
static int	expand_var(t_mini *mini, char **pinput, int quote, int *i)
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
	if (n == 1)
		return (0);
	temp_key = ft_strndup((*pinput + *i + 1), n - 1);
	env_var = get_env(mini, temp_key);
	free(temp_key);
	ft_strexpand(pinput, env_var, *i, n);
	*i += ft_strlen(env_var) - 1;
	return (1);
}

/**
 * @brief Expand wildcard if not in single quote
 * Special case:
 * If the * character is a part of the argument in the export command,
 * then check if the token is assigning * to an identifier, (e.g. A=*)
 * If yes then ignore the token.
 * 
 * @param mini 
 * @param pinput input string ptr
 */
static int	expand_wildcard(t_mini *mini, char **pinput)
{
	int		i;
	int		quote;
	char	*token;
	int		is_export;
	int		expanded;

	i = -1;
	is_export = 0;
	expanded = 0;
	while ((*pinput)[++i] != 0)
	{
		quote = (*pinput)[i];
		token = get_next_token(*pinput, i, quote);
		if (i == 0 && ft_strcmp(token, "export") == 0)
			is_export = 1;
		if (quote != '\'' && quote != '"' && ft_strchr(token, '*') != NULL)
			if (!(is_export && ft_strchr(token, '=')))
				expanded += wildcard(mini, pinput, &token, i);
		i += ft_strlen(token);
		free(token);
		if (i >= 0 && (*pinput)[i] == 0)
			return (expanded);
	}
	return (expanded);
}

/**
 * @brief Expand env_var if not in single quotes
 * 
 * @param mini 
 * @param pinput input string ptr
 */
static int	expand_variables(t_mini *mini, char **pinput)
{
	int		quote;
	int		i;
	int		expanded;

	quote = 0;
	i = -1;
	expanded = 0;
	while ((*pinput)[++i] != 0)
	{
		if (quote != '\'' && (*pinput)[i] == '$')
			expanded += expand_var(mini, pinput, quote, &i);
		else if (quote == 0 && ((*pinput)[i] == '<' || (*pinput)[i] == '>'))
		{
			(*pinput)[i] = 1 + ((*pinput)[i] == '>') * 2;
			expanded++;
		}
		else if (quote == 0 && ((*pinput)[i] == '\'' || (*pinput)[i] == '"'))
			quote = (*pinput)[i];
		else if (quote == (*pinput)[i])
			quote = 0;
		if (i >= 0 && (*pinput)[i] == 0)
			return (expanded);
	}
	return (expanded);
}

/**
 * @brief Expand the variables and wildcards in the input
 * 1. Expand variables if not in single quotes.
 * 2. Expand wildcards if not in single quotes or the case like export A=*.
 * 
 * @param mini 
 * @param pinput input string ptr
 */
int	expand_input(t_mini *mini, char **pinput)
{
	int		expanded;
	char	*temp;

	expanded = 0;
	expanded += expand_variables(mini, pinput);
	expanded += expand_wildcard(mini, pinput);
	if (((*pinput)[0] == '\'' && (*pinput)[ft_strlen(*pinput) - 1] == '\'')
		|| ((*pinput)[0] == '"' && (*pinput)[ft_strlen(*pinput) - 1] == '"'))
	{
		temp = *pinput;
		*pinput = ft_strndup(temp + 1, ft_strlen(temp) - 2);
		free(temp);
	}
	return (expanded);
}
