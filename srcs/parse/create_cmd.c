/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:23:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/12 23:37:51 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
change set_redir
change no_pipe_command
change run_command
while running, if fd < 0, error else dup2
First, run set_redir for every command
Second, check from 0 to size - 1  if there is fd < 0, if so, print the error message
Third, still run the command, but check if there is fd < 0, exit directly
*/

t_iofd	*init_iofd(int size)
{
	t_iofd	*iofd;
	int		cnt;

	iofd = ft_malloc(size, sizeof(t_iofd));
	cnt = -1;
	while (++cnt < size)
	{
		iofd[cnt].in_file = ft_strdup("STDIN");
		iofd[cnt].out_file = ft_strdup("STDOUT");
		iofd[cnt].stdin_fd = STDIN_FILENO;
		iofd[cnt].stdout_fd = STDOUT_FILENO;
	}
	return (iofd);
}

void	ft_free_iofd(t_iofd *iofd, int size)
{
	while (--size >= 0)
	{
		ft_free(iofd[size].in_file);
		ft_free(iofd[size].out_file);
	}
	ft_free(iofd);
}

void	create_pipe(t_deque *cmd_list) // need to deque_clear every cmd (deep free), but don't free cmd_list (only pop_front to make it empty)
{
	int				status;
	int				**pipefd;
	pid_t			*pid;
	int				size;
	t_iofd			*iofd; // iofd needs to be initialize ?
	t_double_list	*iterator[3];

	size = cmd_list->size;
	iofd = init_iofd(size);
	iterator[0] = cmd_list->head;
	for (int i = 0 ; i < size ; ++i) // set redir for every cmd
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
	if (cmd_list->size == 1)
	{
		no_pipe_command(cmd_list->head->content, &iofd[0]);
		ft_free_iofd(iofd, size);
		deque_clear(cmd_list->head->content, free_token);
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
		deque_clear(cmd_list->tail->content, free_token);
		deque_pop_back(cmd_list, NULL);
	}
	else // child : run_command
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
	for (int i = 0 ; i < size - 1 ; ++i) waitpid(pid[i], NULL, 0);
	waitpid(pid[size - 1], &status, 0);
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
	for (int i = 0 ; i < size - 1 ; ++i) ft_free(pipefd[i]);
	ft_free(pipefd);
	ft_free(pid);
	ft_free_iofd(iofd, size);
}

void	create_cmd(t_deque *tokens) // seperate commands with pipes, call create_pipe when there is a semicolon or EOL
{
	t_deque	*cmd_list;
	t_deque	*cur_cmd;

	cmd_list = deque_init();
	cur_cmd = deque_init();
	while (tokens->size > 0)
	{
		if (((t_token *)tokens->head->content)->lexer_flag == _pipe)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
		}
		else if (((t_token *)tokens->head->content)->lexer_flag != _semicolon)
			deque_push_back(cur_cmd, tokens->head->content);
		if (((t_token *)tokens->head->content)->lexer_flag == _semicolon || tokens->size == 1)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
			create_pipe(cmd_list); // after running this, cmd_list will be empty
		}
		deque_pop_front(tokens, NULL);
	}
	deque_clear(cur_cmd, free_token);
	deque_clear(cmd_list, NULL);
}
