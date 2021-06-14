/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:42:12 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 19:51:15 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char			*str;
	unsigned int	key;

	g_data.buffer_list = deque_init();
	g_data.cursor = NULL;
	g_data.history_iterator = NULL;
	while (1)
	{
		key = get_key();
		if (ft_isprint(key))
			insert_in_buffer((char)key);
		else if (key == '\n')
		{
			str = buffer_to_string();
			deque_clear(g_data.buffer_list, ft_free);
			g_data.buffer_list = NULL;
			ft_putchar_fd('\n', 2);
			break ;
		}
	}
	return (str);
}
