/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:07:16 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 21:03:06 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_backspace_sub_sub(t_double_list *target, int cnt[2])
{
	if (g_data.cursor == NULL)
		target = g_data.buffer_list->head;
	else
		target = g_data.cursor->next;
	while (target)
	{
		ft_putchar_fd(*((char *)target->content), 2);
		target = target->next;
	}
	while (--cnt[0] > 0)
		ft_putchar_fd('\b', 2);
}

static void	handle_backspace_sub(t_double_list *target, int cnt[2])
{
	if (g_data.cursor == g_data.buffer_list->head)
	{
		g_data.cursor = NULL;
		deque_pop_front(g_data.buffer_list, ft_free);
	}
	else if (g_data.cursor == g_data.buffer_list->tail)
	{
		g_data.cursor = g_data.cursor->last;
		deque_pop_back(g_data.buffer_list, ft_free);
	}
	else
	{
		target = g_data.cursor;
		g_data.cursor = g_data.cursor->last;
		--(g_data.buffer_list->size);
		g_data.cursor->next = target->next;
		target->next->last = g_data.cursor;
		ft_free(target->content);
		ft_free(target);
	}
	handle_backspace_sub_sub(target, cnt);
}

void	handle_backspace(void)
{
	t_double_list	*target;
	int				cnt[2];

	if (g_data.cursor == NULL)
		return ;
	cnt[0] = 0;
	target = g_data.cursor;
	while (target)
	{
		++cnt[0];
		ft_putchar_fd(' ', 2);
		target = target->next;
	}
	cnt[1] = -1;
	while (++cnt[1] < cnt[0])
		ft_putchar_fd('\b', 2);
	ft_putstr_fd("\b \b", 2);
	handle_backspace_sub(target, cnt);
}
