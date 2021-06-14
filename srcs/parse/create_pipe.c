/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 23:09:38 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 00:03:43 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipe_sub_1(t_deque *cmd_list, int size, t_iofd *iofd)
{
	t_double_list	*iterator[3];
	int				i;

	iterator[0] = cmd_list->head;
	i = -1;
	while (++i < size)
	{
		iterator[1] = ((t_deque *)iterator[0]->content)->head;
		while (iterator[1])
		{
			if (is_redir(((t_token *)iterator[1]->content)->lexer_flag))
			{
				set_redir(((t_token *)iterator[1]->content)->str, ((t_token *)iterator[1]->next->content)->str, &iofd[i]);
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
		if (pipe(pipefd[i]) < 0) message_exit(87, "pipe", 2);
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
		if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("", 2);
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
	create_pipe_sub_1(cmd_list, size, iofd);
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



	
	pid[size - 1] = fork();
	if (pid[size - 1] < 0)
		message_exit(87, "fork", 2);
	else if (pid[size - 1] > 0)
	{
		g_data.pid = pid[size - 1];
		deque_clear(cmd_list->tail->content, free_token);
		deque_pop_back(cmd_list, NULL);
	}
	else
	{
		dup2(pipefd[size - 2][0], STDIN_FILENO);
		dup2(g_data.stdout_fd, STDOUT_FILENO);
		if (iofd[size - 1].stdin_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			if (ft_strncmp(iofd[size - 1].in_file, "", 1) == 0)
				ft_putstr_fd(": ", 2);
			perror(iofd[size - 1].in_file);
			message_exit(1, "", -1);
		}
		else if (iofd[size - 1].stdin_fd != STDIN_FILENO)
		{
			dup2(iofd[size - 1].stdin_fd, STDIN_FILENO);
			close(iofd[size - 1].stdin_fd);
		}
		if (iofd[size - 1].stdout_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			if (ft_strncmp(iofd[size - 1].out_file, "", 1) == 0)
				ft_putstr_fd(": ", 2);
			perror(iofd[size - 1].out_file);
			message_exit(1, "", -1);
		}
		else if (iofd[size - 1].stdout_fd != STDOUT_FILENO)
		{
			dup2(iofd[size - 1].stdout_fd, STDOUT_FILENO);
			close(iofd[size - 1].stdout_fd);
		}
		for (int i = 0 ; i < size - 1 ; ++i)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		run_command(cmd_list->tail->content);
	}
	for (int i = size - 2; i > 0; --i)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			message_exit(87, "fork", 2);
		else if (pid[i] > 0)
		{
			deque_clear(cmd_list->tail->content, free_token);
			deque_pop_back(cmd_list, NULL);
		}
		else
		{
			dup2(pipefd[i - 1][0], STDIN_FILENO);
			dup2(pipefd[i][1], STDOUT_FILENO);
			if (iofd[i].stdin_fd < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				if (ft_strncmp(iofd[i].in_file, "", 1) == 0)
					ft_putstr_fd(": ", 2);
				perror(iofd[i].in_file);
				message_exit(1, "", -1);
			}
			else if (iofd[i].stdin_fd != STDIN_FILENO)
			{
				dup2(iofd[i].stdin_fd, STDIN_FILENO);
				close(iofd[i].stdin_fd);
			}
			if (iofd[i].stdout_fd < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				if (ft_strncmp(iofd[i].out_file, "", 1) == 0)
					ft_putstr_fd(": ", 2);
				perror(iofd[i].out_file);
				message_exit(1, "", -1);
			}
			else if (iofd[i].stdout_fd != STDOUT_FILENO)
			{
				dup2(iofd[i].stdout_fd, STDOUT_FILENO);
				close(iofd[i].stdout_fd);
			}
			for (int j = 0 ; j < size - 1 ; ++j)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
			}
			run_command(cmd_list->tail->content);
		}
	}
	pid[0] = fork();
	if (pid[0] < 0)
		message_exit(87, "fork", 2);
	else if (pid[0] > 0)
	{
		for (int i = 0 ; i < size - 1 ; ++i)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		deque_clear(cmd_list->tail->content, free_token);
		deque_pop_back(cmd_list, NULL);
	}
	else
	{
		dup2(g_data.stdin_fd, STDIN_FILENO);
		dup2(pipefd[0][1], STDOUT_FILENO);
		if (iofd[0].stdin_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			if (ft_strncmp(iofd[0].in_file, "", 1) == 0)
				ft_putstr_fd(": ", 2);
			perror(iofd[0].in_file);
			message_exit(1, "", -1);
		}
		else if (iofd[0].stdin_fd != STDIN_FILENO)
		{
			dup2(iofd[0].stdin_fd, STDIN_FILENO);
			close(iofd[0].stdin_fd);
		}
		if (iofd[0].stdout_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			if (ft_strncmp(iofd[0].out_file, "", 1) == 0)
				ft_putstr_fd(": ", 2);
			perror(iofd[0].out_file);
			message_exit(1, "", -1);
		}
		else if (iofd[0].stdout_fd != STDOUT_FILENO)
		{
			dup2(iofd[0].stdout_fd, STDOUT_FILENO);
			close(iofd[0].stdout_fd);
		}
		for (int i = 0 ; i < size - 1 ; ++i)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		run_command(cmd_list->tail->content);
	}
	
	create_pipe_sub_4(size, pid, pipefd, iofd);
}
