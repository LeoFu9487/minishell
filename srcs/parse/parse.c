/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:15:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 20:03:06 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if > < end : unexpected token near 'newline'

/*
** parse step :
** 1. seperate by ; or EOL (if no arguments before ; then parse error)
** 2. seperate by pipes (if no arguments before or after then parse error)
** 3. separated by >(>>) and <(<<), (if nothing after then parse error)
*/

void	parse_and_execute(t_deque *tokens) // need to hanlde exit_status and pid
{
	t_deque			*new_token;
	t_double_list	*iterator;

	iterator = tokens->head;
	while (iterator)
	{
		ft_putendl_fd(iterator->content, 2);
		iterator = iterator->next;
	}
	if (parse_error(tokens))
		return ;
	if (g_data.lexer_error != NoError)
	{
		g_data.exit_status = 2;
		if (g_data.lexer_error == dquote)
			ft_putendl_fd("minishell: unexpected EOL while looking for matching `\"\'", 2);
		else
			ft_putendl_fd("minishell: unexpected EOL while looking for matching `\'\'", 2);
		return ;
	}
	(void)new_token;
}
