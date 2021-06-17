/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 23:09:38 by yfu               #+#    #+#             */
/*   Updated: 2021/06/17 13:53:40 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipe_sub_1(t_deque *cmd_list, int size, t_iofd *iofd, int i)
{
	t_double_list	*iterator[3];

	iterator[0] = cmd_list->head;
	i = -1;
	while (++i < size)
	{
		iterator[1] = ((t_deque *)iterator[0]->content)->head;
		while (iterator[1])
		{
			if (is_redir(((t_token *)iterator[1]->content)->lexer_flag))
			{
				set_redir(((t_token *)iterator[1]->content)->str,
					((t_token *)iterator[1]->next->content)->str, &iofd[i]);
				iterator[2] = iterator[1];
				iterator[1] = iterator[1]->next;
				deque_pop_one(iterator[0]->content, iterator[2], free_token);
				iterator[2] = iterator[1];
				iterator[1] = iterator[1]->next;
				deque_pop_one(iterator[0]->content, iterator[2], free_token);
			}
			else
				iterator[1] = iterator[1]->next;
		}
		iterator[0] = iterator[0]->next;
	}
}

static void	create_pipe_sub_2(int **pipefd, int size)
{
	int	i;

	i = -1;
	while (++i < size - 1)
	{
		pipefd[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipefd[i]) < 0)
			message_exit(87, "pipe", 2);
	}
}

static void	create_pipe_sub_3(t_deque *cmd_list, int **pipefd, pid_t *pid,
t_iofd *iofd)
{
	int	size;
	int	i;

	size = cmd_list->size;
	i = size;
	while (--i >= 0)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			message_exit(87, "fork", 2);
		else if (pid[i] > 0)
		{
			if (i == size - 1)
				g_data.pid = pid[i];
			if (i == 0)
				close_pipefd(size, pipefd);
			deque_clear(cmd_list->tail->content, free_token);
			deque_pop_back(cmd_list, NULL);
		}
		else
			create_pipe_child(cmd_list, size, pipefd, iofd);
	}
}

static void	create_pipe_sub_4(int size, pid_t *pid, int **pipefd, t_iofd *iofd)
{
	int	status;
	int	i;

	i = -1;
	while (++i < size - 1)
		waitpid(pid[i], NULL, 0);
	waitpid(pid[size - 1], &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT || WTERMSIG(status) == SIGINT)
			g_data.exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
		//if (WTERMSIG(status) == SIGINT)
		//	ft_putendl_fd("", 2);
	}
	i = -1;
	while (++i < size - 1)
		ft_free(pipefd[i]);
	ft_free(pipefd);
	ft_free(pid);
	ft_free_iofd(iofd, size);
}

void	create_pipe(t_deque *cmd_list)
{
	int				**pipefd;
	pid_t			*pid;
	int				size;
	t_iofd			*iofd;

	size = cmd_list->size;
	iofd = init_iofd(size);
	create_pipe_sub_1(cmd_list, size, iofd, -1);
	if (cmd_list->size == 1)
	{
		no_pipe_command(cmd_list->head->content, &iofd[0]);
		ft_free_iofd(iofd, size);
		deque_clear(cmd_list->head->content, free_token);
		deque_pop_front(cmd_list, NULL);
		return ;
	}
	pipefd = ft_malloc(size - 1, sizeof(int *));
	pid = ft_malloc(size, sizeof(pid_t));
	create_pipe_sub_2(pipefd, size);
	create_pipe_sub_3(cmd_list, pipefd, pid, iofd);
	create_pipe_sub_4(size, pid, pipefd, iofd);
}
