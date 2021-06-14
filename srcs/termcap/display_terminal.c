/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:47:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 20:06:03 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** g_data.cursor's position won't be modified
** print the element since g_data.cursor's position
*/
void	print_the_rest_of_buffer(void)
{
	t_double_list	*iterator;
	int				cnt;

	if (g_data.cursor == NULL)
	{
		iterator = g_data.buffer_list->head;
		cnt = 1;
	}
	else
	{
		iterator = g_data.cursor;
		cnt = 0;
	}
	while (iterator)
	{
		ft_putchar_fd(*((char *)iterator->content), 2);
		iterator = iterator->next;
		++cnt;
	}
	while (--cnt)
		ft_putchar_fd('\b', 2);
}

void	insert_in_buffer(char c)
{
	t_double_list	*new;

	if (g_data.cursor == NULL)
	{
		deque_push_front(g_data.buffer_list, ft_strdup(&c));
		g_data.cursor = g_data.buffer_list->head;
		print_the_rest_of_buffer();
		return ;
	}
	if (g_data.cursor == g_data.buffer_list->tail)
	{
		deque_push_back(g_data.buffer_list, ft_strdup(&c));
		g_data.cursor = g_data.cursor->next;
		print_the_rest_of_buffer();
		return ;
	}
	new = double_list_init(ft_strdup(&c));
	new->last = g_data.cursor;
	new->next = g_data.cursor->next;
	++(g_data.buffer_list->size);
	g_data.cursor->next->last = new;
	g_data.cursor->next = new;
	g_data.cursor = new;
	print_the_rest_of_buffer();
}

char	*buffer_to_string(void)
{
	char			*str;
	int				idx;
	t_double_list	*iterator;

	idx = 0;
	str = ft_malloc(g_data.buffer_list->size + 1, sizeof(char));
	iterator = g_data.buffer_list->head;
	while (iterator)
	{
		str[idx++] = *((char *)iterator->content);
		iterator = iterator->next;
	}
	str[idx] = 0;
	return (str);
}
