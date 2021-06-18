/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 20:16:05 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fd_error(t_iofd *iofd)
{
	if (iofd->stdin_fd < 0 || iofd->stdout_fd < 0)
	{
		print_fd_error(iofd);
		g_data.exit_status = 1;
		return (1);
	}
	return (0);
}

static void	no_pipe_command_parent_process(void)
{
	int	status;

	waitpid(g_data.pid, &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_data.exit_status = 131;
			ft_putendl_fd("Quit", 2);
		}
		if (WTERMSIG(status) == SIGINT)
		{
			g_data.exit_status = 130;
			ft_putendl_fd("", 2);
		}
	}
}

void	no_pipe_command(t_deque *cmd, t_iofd *iofd)
{
	if (fd_error(iofd))
		return ;
	if (no_pipe_builtin(cmd))
		return ;
	g_data.pid = fork();
	if (g_data.pid)
		no_pipe_command_parent_process();
	else
	{
		if (iofd->stdin_fd != STDIN_FILENO)
		{
			dup2(iofd->stdin_fd, STDIN_FILENO);
			close(iofd->stdin_fd);
		}
		if (iofd->stdout_fd != STDOUT_FILENO)
		{
			dup2(iofd->stdout_fd, STDOUT_FILENO);
			close(iofd->stdout_fd);
		}
		run_command(cmd);
	}
}
