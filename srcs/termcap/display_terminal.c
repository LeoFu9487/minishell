/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:47:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 03:24:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add a thing from cursor (cursor NULL means beginning)
//print from that thing to the end
//move cursor
void	insert_in_buffer(char c) //todo
{
	deque_push_back(g_data.buffer_list, ft_strdup(&c));
	ft_putchar_fd(c, 2);
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
		str[idx++] = *((char*)iterator->content);
		iterator = iterator->next;
	}
	str[idx] = 0;
	return (str);
}
