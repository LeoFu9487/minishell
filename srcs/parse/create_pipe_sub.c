/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 02:34:39 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 20:13:07 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipefd(int size, int **pipefd)
{
	int	i;

	i = -1;
	while (++i < size - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
}

static void	create_pipe_child_sub(int i, t_iofd *iofd)
{
	if (iofd[i].stdin_fd < 0 || iofd[i].stdout_fd < 0)
	{
		print_fd_error(&iofd[i]);
		message_exit(1, "", -1);
	}
	if (iofd[i].stdin_fd != STDIN_FILENO)
	{
		dup2(iofd[i].stdin_fd, STDIN_FILENO);
		close(iofd[i].stdin_fd);
	}
	if (iofd[i].stdout_fd != STDOUT_FILENO)
	{
		dup2(iofd[i].stdout_fd, STDOUT_FILENO);
		close(iofd[i].stdout_fd);
	}
}

void	create_pipe_child(t_deque *cmd_list, int size, int **pipefd,
t_iofd *iofd)
{
	int	i;

	i = cmd_list->size - 1;
	if (i == 0)
		dup2(g_data.stdin_fd, STDIN_FILENO);
	else
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	if (i == size - 1)
		dup2(g_data.stdin_fd, STDOUT_FILENO);
	else
		dup2(pipefd[i][1], STDOUT_FILENO);
	create_pipe_child_sub(i, iofd);
	close_pipefd(size, pipefd);
	run_command(cmd_list->tail->content);
}
