/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:57:57 by yfu               #+#    #+#             */
/*   Updated: 2021/06/13 21:34:35 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_line(void)
{
	int				cnt;
	t_double_list	*iterator;

	iterator = g_data.cursor;
	while (iterator) // move to the beginning
	{
		ft_putchar_fd('\b', 2);
		iterator = iterator->last;
	}
	cnt = 0;
	while (cnt++ < g_data.buffer_list->size)
		ft_putchar_fd(' ', 2);
	cnt = 0;
	while (cnt++ < g_data.buffer_list->size)
		ft_putchar_fd('\b', 2);
	deque_clear(g_data.buffer_list, ft_free);
	g_data.buffer_list = deque_init();
	g_data.cursor = NULL;
}

void	handle_up(void)
{
	int				cnt[2];
	char			*str;

	if (g_data.history_iterator == NULL)
		g_data.history_iterator = g_data.history->tail;
	else if (g_data.history_iterator != g_data.history->head)
		g_data.history_iterator = g_data.history_iterator->last;
	else
		return ;
	clean_line();
	cnt[0] = -1;
	str = g_data.history_iterator->content;
	while (str[++cnt[0]])
		insert_in_buffer(str[cnt[0]]);
}

void	handle_down(void)
{
	int		cnt;
	char	*str;

	if (g_data.history_iterator == NULL)
		return ;
	else
		g_data.history_iterator = g_data.history_iterator->next;
	clean_line();
	if (g_data.history_iterator == NULL)
		return ;
	cnt = -1;
	str = g_data.history_iterator->content;
	while (str[++cnt])
		insert_in_buffer(str[cnt]);
}

void	handle_left(void)
{
	if (g_data.cursor == NULL)
		return ;
	g_data.cursor = g_data.cursor->last;
	ft_putchar_fd('\b', 2);
}

void	handle_right(void)
{
	if (g_data.cursor == g_data.buffer_list->tail)
		return ;
	if (g_data.cursor == NULL)
		g_data.cursor = g_data.buffer_list->head;
	else
		g_data.cursor = g_data.cursor->next;
	if (g_data.cursor)
		ft_putchar_fd(*((char*)g_data.cursor->content), 2);
}
