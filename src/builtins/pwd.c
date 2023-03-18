/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:23:16 by welim             #+#    #+#             */
/*   Updated: 2023/03/18 15:13:26 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builtin command pwd
 * 
 */
void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
}
