/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_semicolon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:40:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 22:35:40 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_parse_semicolon_sub(t_double_list *iterator,
t_deque *new_token)
{
	int	result;

	result = -1;
	if (new_token->size > 0)
	{
		if (((t_token *)iterator->content)->lexer_flag != _semicolon)
			result = check_parse_pipe(new_token, NewLine);
		else
			result = check_parse_pipe(new_token, Semicolon);
	}
	else
		ft_putendl_fd("minishell: syntax error near unexpected token `;\'", 2);
	if (new_token->size == 0 || result == 1)
	{
		deque_clear(new_token, NULL);
		g_data.exit_status = 258;
		return (1);
	}
	deque_clear(new_token, NULL);
	return (0);
}

int	check_parse_semicolon(t_deque *tokens)
{
	t_double_list	*iterator;
	t_deque			*new_token;

	new_token = deque_init();
	iterator = tokens->head;
	while (iterator)
	{
		if (((t_token *)iterator->content)->lexer_flag != _semicolon)
			deque_push_back(new_token, iterator->content);
		if (((t_token *)iterator->content)->lexer_flag == _semicolon
			|| iterator == tokens->tail)
		{
			if (check_parse_semicolon_sub(iterator, new_token))
				return (1);
			new_token = deque_init();
		}
		iterator = iterator->next;
	}
	deque_clear(new_token, NULL);
	return (0);
}
