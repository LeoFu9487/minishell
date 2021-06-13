/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:49:31 by xli               #+#    #+#             */
/*   Updated: 2021/06/13 16:11:15 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If no arg, exits the whole minishell(exit code 0).
**
**
**
*/

void	builtin_exit(char **args)
{
	if (args && !args[1])
		message_exit(g_data.exit_status, "exit\n", 2);
}

