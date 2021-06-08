/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:15:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 02:17:13 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_execute(t_deque *tokens) // need to hanlde exit_status and pid
{
	t_double_list	*iterator;

	iterator = tokens->head;
	while (iterator)
	{
		ft_putendl_fd(iterator->content, 2);
		iterator = iterator->next;
	}
	(void)tokens;
}
