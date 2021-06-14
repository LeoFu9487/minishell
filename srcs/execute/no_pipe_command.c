/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 10:47:41 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_pipe_exit(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	builtin_exit(args);
	ft_free(args);
}

void	no_pipe_command(t_deque *cmd, t_iofd *iofd) // cmd is a list of tokens
{
	int		status;

	if (iofd->stdin_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (ft_strncmp(iofd->in_file, "", 1) == 0)
			ft_putstr_fd(": ", 2);
		perror(iofd->in_file);
		g_data.exit_status = 1;
		return ;
	}
	if (iofd->stdout_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (ft_strncmp(iofd->out_file, "", 1) == 0)
			ft_putstr_fd(": ", 2);
		perror(iofd->out_file);
		g_data.exit_status = 1;
		return ;
	}
	if (cmd->size > 0 && ft_strncmp(((t_token *)cmd->head->content)->str, "exit", 5) == 0)
	{
		no_pipe_exit(cmd);
		return ;
	}
	g_data.pid = fork();
	if (g_data.pid) // parent process
	{
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
