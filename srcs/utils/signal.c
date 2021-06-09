/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:06:43 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 04:41:34 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT) /* ctrl + C */
	{
		g_data.exit_status = 130;
		if (g_data.buffer_list)
		{
			deque_clear(g_data.buffer_list, ft_free);
			g_data.buffer_list = deque_init();
			g_data.cursor = NULL;
			g_data.history_iterator = NULL;
		}
		if (g_data.pid == 0)
		{
			ft_putendl_fd("", 2);
			print_prompt();
		}
		else
			ft_putendl_fd("", 2);
	}
	if (signal == SIGQUIT) /* ctrl + \ */
	{
		if (g_data.pid != 0)
		{
			g_data.exit_status = 131;
			ft_putendl_fd("Quit", 2);
		}
	}
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
