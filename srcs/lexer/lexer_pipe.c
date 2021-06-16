/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:53:10 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 13:13:04 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub(t_deque *token_buffer)
{
	if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("\\"));
	else if (g_data.lexer->last_key == dollar)
		deque_push_back(token_buffer, ft_strdup("$"));
	deque_push_back(token_buffer, ft_strdup("|"));
}

void	lexer_pipe(t_deque *tokens, t_deque *token_buffer, char *str, int *idx)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("|"));
	else if (g_data.lexer->dquote)
		sub(token_buffer);
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("|"));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
		if (str[*idx + 1] == '|')
		{
			++(*idx);
			deque_push_back(tokens, init_token("||", _logical_or));
		}
		else
			deque_push_back(tokens, init_token("|", _pipe));
	}
	g_data.lexer->last_key = others;
}
