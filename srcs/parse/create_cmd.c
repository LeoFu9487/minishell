/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:23:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 23:50:50 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	recursive_pipe(t_deque *cmd_list, t_double_list *iterator, int fd)
{
	int	pipefd[2];
	int	status;

	if (iterator == cmd_list->head)
	{
		dup2(g_data.stdin_fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		run_command(iterator->content);
	}
	if (pipe(pipefd) < 0)
		message_exit(87, strerror(errno), 2);
	g_data.pid = fork();
	if (g_data.pid < 0)
		message_exit(87, strerror(errno), 2);
	if (g_data.pid > 0) // parent process
	{
		close(pipefd[1]);
		waitpid(g_data.pid, &status, 0);
		dup2(pipefd[0], STDIN_FILENO); // read(0, ...) will read from pipe
		close(pipefd[0]);
		dup2(fd, STDOUT_FILENO); // write(1, ...) will write to pipe
		close(fd);
		run_command(iterator->content);
		if (WIFEXITED(status))
			g_data.exit_status = WEXITSTATUS(status);
	}
	else // child process
	{
		close(pipefd[0]);
		recursive_pipe(cmd_list, iterator->last, pipefd[1]);
	}
}
*/
void	create_pipe(t_deque *cmd_list) // need to deque_clear every cmd (deep free), but don't free cmd_list (only pop_front to make it empty)
{
	int				status;
	int				**pipefd;
	pid_t			*pid;
	int				size;

	size = cmd_list->size;
	if (cmd_list->size == 1)
	{
		no_pipe_command(cmd_list->head->content);
		deque_clear(cmd_list->head->content, ft_free);
		deque_pop_front(cmd_list, NULL);
		return ;
	}
	pipefd = ft_malloc(size - 1, sizeof(int *));
	for (int i = 0 ; i < size - 1 ; ++i) pipefd[i] = ft_calloc(2, sizeof(int)); // write into 1 and read from 0
	for (int i = 0 ; i < size - 1 ; ++i) if (pipe(pipefd[i]) < 0) message_exit(87, "pipe", 2);
	pid = ft_malloc(size, sizeof(pid_t));
	pid[size - 1] = fork();
	if (pid[size - 1] < 0)
		message_exit(87, "fork", 2);
	else if (pid[size - 1] > 0)
	{
		g_data.pid = pid[size - 1];
		deque_clear(cmd_list->tail->content, ft_free);
		deque_pop_back(cmd_list, NULL);
	}
	else // child : run_command
	{
		dup2(pipefd[size - 2][0], STDIN_FILENO);
		dup2(g_data.stdout_fd, STDOUT_FILENO);
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
			deque_clear(cmd_list->tail->content, ft_free);
			deque_pop_back(cmd_list, NULL);
		}
		else
		{
			dup2(pipefd[i - 1][0], STDIN_FILENO);
			dup2(pipefd[i][1], STDOUT_FILENO);
			for (int j = 0 ; j < size - 1 ; ++j)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
			}
			run_command(cmd_list->tail->content);
		}
	}
	//need to deal with the last command
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
		deque_clear(cmd_list->tail->content, ft_free);
		deque_pop_back(cmd_list, NULL);
	}
	else
	{
		dup2(g_data.stdin_fd, STDIN_FILENO);
		dup2(pipefd[0][1], STDOUT_FILENO);
		for (int i = 0 ; i < size - 1 ; ++i)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		run_command(cmd_list->tail->content);
	}
	for (int i = 0 ; i < size - 1 ; ++i) waitpid(pid[i], NULL, 0);
	waitpid(pid[size - 1], &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	for (int i = 0 ; i < size - 1 ; ++i) ft_free(pipefd[i]);
	ft_free(pipefd);
	ft_free(pid);
}

void	create_cmd(t_deque *tokens) // seperate commands with pipes, call create_pipe when there is a semicolon or EOL
{
	t_deque	*cmd_list;
	t_deque	*cur_cmd;

	cmd_list = deque_init();
	cur_cmd = deque_init();
	while (tokens->size > 0)
	{
		if (ft_strncmp(tokens->head->content, "|", 2) == 0)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
		}
		else if (ft_strncmp(tokens->head->content, ";", 2) != 0)
			deque_push_back(cur_cmd, ft_strdup(tokens->head->content));
		if (ft_strncmp(tokens->head->content, ";", 2) == 0 || tokens->size == 1)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
			create_pipe(cmd_list); // after running this, cmd_list will be empty
		}
		deque_pop_front(tokens, ft_free);
	}
	deque_clear(cur_cmd, ft_free);
	deque_clear(cmd_list, NULL);
}
