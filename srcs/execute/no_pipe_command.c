/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 03:53:46 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe_command(t_deque *cmd) // cmd is a list of tokens
{
	int	status;
/*
** here is only for the convenience of testing
*/
	g_data.pid = fork();
	if (g_data.pid) // parent process
	{
		waitpid(g_data.pid, &status, 0);
		if (WIFEXITED(status))
			g_data.exit_status = WEXITSTATUS(status);
	}
	else
	{
		run_command(cmd);
	}
/*____________________________________________*/
	// didn't open any fork yet
	//don't open a fork if the command is exit	
}
