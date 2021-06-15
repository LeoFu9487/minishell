/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:15:05 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 23:15:11 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(char **env)
{
	g_data.stdin_fd = dup(STDIN_FILENO);
	g_data.stdout_fd = dup(STDOUT_FILENO);
	g_data.exit_status = 0;
	g_data.buffer_list = NULL;
	g_data.pid = 0;
	g_data.history = deque_init();
	deque_push_back(g_data.history, "You have no history before this.");
	g_data.clip_board = NULL;
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
	init_env(env);
}
