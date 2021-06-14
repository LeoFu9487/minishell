/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:07:49 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 20:59:55 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_delete_sub(int cnt[2])
{
	t_double_list	*iterator;

	iterator = g_data.cursor;
	cnt[0] = 0;
	while (iterator && iterator != g_data.buffer_list->tail)
	{
		++cnt[0];
		iterator = iterator->next;
	}
	cnt[1] = -1;
	while (++cnt[1] < cnt[0])
		ft_putchar_fd(' ', 2);
	while (cnt[0]-- > 0)
		ft_putchar_fd('\b', 2);
	iterator = g_data.cursor->next;
	--(g_data.buffer_list->size);
	g_data.cursor->next = iterator->next;
	if (iterator->next)
		iterator->next->last = g_data.cursor;
	ft_free(iterator->content);
	ft_free(iterator);
	g_data.cursor = g_data.cursor->next;
	print_the_rest_of_buffer();
	g_data.cursor = g_data.cursor->last;
	ft_putchar_fd('\b', 2);
}

void	handle_delete(void)
{
	int	cnt[2];

	if (g_data.cursor == g_data.buffer_list->tail)
		return ;
	if (g_data.cursor == NULL)
	{
		cnt[0] = -1;
		while (++cnt[0] < g_data.buffer_list->size)
			ft_putchar_fd(' ', 2);
		cnt[0] = -1;
		while (++cnt[0] < g_data.buffer_list->size)
			ft_putchar_fd('\b', 2);
		deque_pop_front(g_data.buffer_list, ft_free);
		g_data.cursor = NULL;
		print_the_rest_of_buffer();
		g_data.cursor = NULL;
		return ;
	}
	if (g_data.cursor->next == g_data.buffer_list->tail)
	{
		ft_putstr_fd(" \b", 2);
		deque_pop_back(g_data.buffer_list, ft_free);
		return ;
	}
	handle_delete_sub(cnt);
}
