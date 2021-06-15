/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:52:11 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:21:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub1(t_deque *token_buffer)
{
	if (g_data.lexer->last_key == back_slash)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = others;
	}
	else if (g_data.lexer->last_key == dollar)
		deque_push_back(token_buffer, ft_strdup("$"));
	else
		g_data.lexer->last_key = dollar;
}

void	lexer_dollar(t_deque *token_buffer)
{
	if (g_data.lexer->quote)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = others;
	}
	else if (g_data.lexer->dquote)
		sub1(token_buffer);
	else if (g_data.lexer->last_key == back_slash)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = others;
	}
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = dollar;
	}
}
