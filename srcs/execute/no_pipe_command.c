/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 20:17:17 by yfu              ###   ########lyon.fr   */
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
		if (is_redir(cmd->head->content))
		{
			set_redir(cmd->head->content, cmd->head->next->content);
			deque_pop_front(cmd, NULL);
		}
		else
			args[cnt++] = cmd->head->content;
		deque_pop_front(cmd, NULL);
	}
	//builtin_exit(args);
	ft_free(args);
}

void	no_pipe_command(t_deque *cmd) // cmd is a list of tokens
{
	int		status;

	if (ft_strncmp(cmd->head->content, "exit", 5) == 0)
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
		run_command(cmd);
	}
}
