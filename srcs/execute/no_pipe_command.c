/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 01:07:22 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe_command(t_deque *cmd) // cmd is a list of tokens
{
/*
** here is only for the convenience of testing
*/
	g_data.pid = fork();
	if (g_data.pid) // parent process
	{
		waitpid(g_data.pid, NULL, 0);
	}
	else
	{
		run_command(cmd);
	}
/*____________________________________________*/
	// didn't open any fork yet
	//don't open a fork if the command is exit	
}
