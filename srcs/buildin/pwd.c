/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:45:14 by xli               #+#    #+#             */
/*   Updated: 2021/06/18 10:55:30 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char **args)
{
	if (args && args[1] && args[1][0] == '-')
		message_exit(1, "pwd: does not take options\n", 2);
	ft_putstr_fd(g_data.pwd, 1);
	message_exit(0, "\n", 1);
}
