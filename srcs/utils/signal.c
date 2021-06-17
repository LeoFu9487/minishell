/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:06:43 by yfu               #+#    #+#             */
/*   Updated: 2021/06/17 13:52:36 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_data.buffer_list)
		{
			deque_clear(g_data.buffer_list, ft_free);
			g_data.buffer_list = deque_init();
			g_data.cursor = NULL;
			g_data.history_iterator = NULL;
			g_data.exit_status = 1;
			ft_putendl_fd("", 2);
			print_prompt();
		}
		else if (g_data.pid == 0 && g_data.heredoc_process == 0)
		{
			g_data.exit_status = 1;
			ft_putendl_fd("", 2);
			print_prompt();
		}
		if (g_data.pid && g_data.heredoc_process)
			kill(g_data.pid, SIGUSR1);
		else if (g_data.pid)
		{
			ft_putendl_fd("", 2);
			g_data.exit_status = 130;
		}
	}
}

static void	update_term_size(int signal)
{
	if (tgetent(NULL, getenv("TERM")) != 1)
	{
		g_data.term_width = -1;
		g_data.term_height = -1;
	}
	else
	{
		g_data.term_height = tgetnum("li");
		g_data.term_width = tgetnum("co");
	}
	(void)signal;
}

static void	kill_process(int signal)
{
	message_exit(GET_KILLED, "", -1);
	(void)signal;
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGWINCH, update_term_size);
	signal(SIGUSR1, kill_process);
}
