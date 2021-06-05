/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:57:57 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 03:36:09 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_up(void)
{
	int		cnt;
	char	*str;

	if (g_data.history_iterator == NULL)
		g_data.history_iterator = g_data.history->tail;
	else if (g_data.history_iterator != g_data.history->head)
		g_data.history_iterator = g_data.history_iterator->last;
	else
		return ;
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd('\b', 2);
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd(' ', 2);
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd('\b', 2);
	deque_clear(g_data.buffer_list, ft_free);
	g_data.buffer_list = deque_init();
	g_data.cursor = NULL;
	cnt = -1;
	str = g_data.history_iterator->content;
	while (str[++cnt])
		insert_in_buffer(str[cnt]);
}

void	handle_down(void)
{
	int		cnt;
	char	*str;

	if (g_data.history_iterator == NULL)
		return ;
	else
		g_data.history_iterator = g_data.history_iterator->next;
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd('\b', 2);
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd(' ', 2);
	cnt = -1;
	while (++cnt < g_data.buffer_list->size)
		ft_putchar_fd('\b', 2);
	deque_clear(g_data.buffer_list, ft_free);
	g_data.buffer_list = deque_init();
	g_data.cursor = NULL;
	if (g_data.history_iterator == NULL)
		return ;
	cnt = -1;
	str = g_data.history_iterator->content;
	while (str[++cnt])
		insert_in_buffer(str[cnt]);
}

void	handle_left(void)
{
	ft_putendl_fd("left", 2);
}

void	handle_right(void)
{
	ft_putendl_fd("right", 2);
}
