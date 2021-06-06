/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:59:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 20:51:46 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_home(void)
{
	while (g_data.cursor)
	{
		ft_putchar_fd('\b', 2);
		g_data.cursor = g_data.cursor->last;
	}
}

void	handle_end(void)
{
	if (g_data.cursor == g_data.buffer_list->tail)
		return ;
	if (g_data.cursor == NULL)
		g_data.cursor = g_data.buffer_list->head;
	else
		g_data.cursor = g_data.cursor->next;
	while (g_data.cursor)
	{
		ft_putchar_fd(*((char *)g_data.cursor->content), 2);
		if (g_data.cursor == g_data.buffer_list->tail)
			break ;
		g_data.cursor = g_data.cursor->next;
	}
}

void	handle_delete(void)
{
	int				cnt[2];
	t_double_list	*iterator;

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
