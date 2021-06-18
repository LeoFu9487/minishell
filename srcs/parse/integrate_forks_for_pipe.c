/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate_forks_for_pipe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 22:19:41 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 22:20:52 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	integrate_forks_for_pipe(int size, pid_t *pid)
{
	int	i;
	int	sigint;
	int	status;

	i = -1;
	sigint = 0;
	while (++i < size - 1)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			sigint = 1;
	}
	waitpid(pid[size - 1], &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGINT)
			g_data.exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
		if (WTERMSIG(status) == SIGINT)
			sigint = 1;
	}
	return (sigint);
}
