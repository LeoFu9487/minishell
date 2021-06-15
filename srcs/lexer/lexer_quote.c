/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:53:26 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:19:38 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_quote(t_deque *token_buffer)
{
	if (g_data.lexer->quote)
		g_data.lexer->quote = 0;
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		else if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		deque_push_back(token_buffer, ft_strdup("\'"));
	}
	else
	{
		if (g_data.lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			g_data.lexer->quote = 1;
		}
		else if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\'"));
		else
			g_data.lexer->quote = 1;
	}
	g_data.lexer->last_key = others;
}
