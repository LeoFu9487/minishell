/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:42:12 by yfu               #+#    #+#             */
/*   Updated: 2021/06/03 00:28:03 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	while (1)
	{
		char buffer[1];
		read(0, buffer, 1);
		if (buffer[0] == '\n')
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
	}
	//remember to keep track of g_data.empty_buffer
	return ("");
}
