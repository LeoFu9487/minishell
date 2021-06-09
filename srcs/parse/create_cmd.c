/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:23:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 02:54:20 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recursive_pipe(t_deque *cmd_list, t_double_list *iterator, int fd)
{
	int	pipefd[2];

	if (iterator == cmd_list->head)
		run_command(iterator->content);
	if (pipe(pipefd) < 0)
		message_exit(87, strerror(errno), 2);
	g_data.pid = fork();
	if (g_data.pid < 0)
		message_exit(87, strerror(errno), 2);
	if (g_data.pid > 0) // parent process
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO); // read(0, ...) will read from pipe
		close(pipefd[0]);
		dup2(fd, STDOUT_FILENO); // write(1, ...) will write to pipe
		close(fd);
		run_command(iterator->content);
		waitpid(g_data.pid, NULL, 0); // need to get and change the exit code here
	}
	else // child process
	{
		close(pipefd[0]);
		recursive_pipe(cmd_list, iterator->last, pipefd[1]);
	}
}

void	create_pipe(t_deque *cmd_list) // need to deque_clear every cmd (deep free), but don't free cmd_list (only pop_front to make it empty)
{
	if (cmd_list->size == 1)
	{
		no_pipe_command(cmd_list->head->content);
		deque_clear(cmd_list->head->content, ft_free);
		deque_pop_front(cmd_list, NULL);
		return ;
	}
	g_data.pid = fork(); // if cmd_list->size == 1 and exit then don't do this
	if (g_data.pid < 0)
		message_exit(87, strerror(errno), 2);
	if (g_data.pid > 0) // parent process
	{
		waitpid(g_data.pid, NULL, 0); // need to get and change the exit code here
		while (cmd_list->size > 0)
		{
			deque_clear(cmd_list->head->content, ft_free);
			deque_pop_front(cmd_list, NULL);
		}
	}
	else // child process
	{
		recursive_pipe(cmd_list, cmd_list->tail, g_data.stdout_fd);
	}
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
