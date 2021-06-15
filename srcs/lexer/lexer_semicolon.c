/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:58:37 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:19:23 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_semicolon(t_deque *tokens, t_deque *token_buffer)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup(";"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup(";"));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup(";"));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
		deque_push_back(tokens, init_token(";", _semicolon));
	}
	g_data.lexer->last_key = others;
}
