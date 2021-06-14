/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:59:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 20:08:15 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
