/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:42:12 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 00:06:07 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input(void)
{
	char *str = NULL;
	unsigned key;
	int cnt = 0;
	while (1)
	{
		key = get_key();
		if (ft_isprint(key) || key == '\n')
		{
		}
		if (++cnt >= 10)
			break;
	}
	//remember to keep track of g_data.empty_buffer
	return (str);
}
