/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:58:12 by yfu               #+#    #+#             */
/*   Updated: 2021/06/17 13:27:43 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub1(t_deque *token_buffer)
{
	if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("\\"));
	else if (g_data.lexer->last_key == dollar)
		deque_push_back(token_buffer, ft_strdup("$"));
	deque_push_back(token_buffer, ft_strdup("<"));
}

void	lexer_redir_in(t_deque *tokens, t_deque *token_buffer, char *str,
int *idx)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("<"));
	else if (g_data.lexer->dquote)
		sub1(token_buffer);
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("<"));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
		if (str[(*idx) + 1] == '<')
		{
			++(*idx);
			deque_push_back(tokens, init_token("<<", _redir_in_d));
		}
		else
			deque_push_back(tokens, init_token("<", _redir_in));
	}
	g_data.lexer->last_key = others;
}
