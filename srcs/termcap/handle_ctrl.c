/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:45:34 by yfu               #+#    #+#             */
/*   Updated: 2021/06/10 21:17:37 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_a(void)
{}

void	handle_ctrl_b(void)
{}

void	handle_ctrl_d(void)
{
	if ((g_data.buffer_list == NULL || g_data.buffer_list->size == 0) && g_data.pid == 0)
	{
		message_exit(g_data.exit_status, "exit\n", 2);
	}
}

void	handle_ctrl_l(void)
{
	t_double_list	*iterator;

	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_putendl_fd("", 2);
	else
		ft_putstr_fd(tgetstr("cl", NULL), 2);
	print_prompt();
	iterator = g_data.buffer_list->head;
	while (iterator)
	{
		ft_putchar_fd(*((char *)iterator->content), 2);
		iterator = iterator->next;
	}
	iterator = g_data.buffer_list->tail;
	while (iterator && iterator != g_data.cursor)
	{
		ft_putchar_fd('\b', 2);
		iterator = iterator->last;
	}
}

void	handle_ctrl_v(void)
{}
