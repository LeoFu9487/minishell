/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:58:24 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:23:18 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub1(t_deque *token_buffer, t_deque *tokens, int *idx, char *str)
{
	if (g_data.lexer->last_key == dollar)
		deque_push_back(token_buffer, ft_strdup("$"));
	put_buffer_in_tokens(tokens, token_buffer, _undefined);
	if (str[(*idx) + 1] == '>')
	{
		++(*idx);
		deque_push_back(tokens, init_token(">>", _redir_in_d));
	}
	else
		deque_push_back(tokens, init_token(">", _redir_in));
}

void	lexer_redir_out(t_deque *tokens, t_deque *token_buffer, char *str,
int *idx)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup(">"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup(">"));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup(">"));
	else
		sub1(token_buffer, tokens, idx, str);
	g_data.lexer->last_key = others;
}
