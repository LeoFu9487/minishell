/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:15:05 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 01:24:43 by yfu              ###   ########lyon.fr   */
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
	g_data.color = NOCOLOR;
	g_data.prompt_color = NOCOLOR;
	g_data.history = deque_init();
	g_data.heredoc_process = 0;
	deque_push_back(g_data.history, "You have no history before this.");
	g_data.clip_board = NULL;
	g_data.pwd = ft_getcwd(NULL, 0);
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
