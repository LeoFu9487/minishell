/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_back_slash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:51:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:06:49 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub1(t_deque *token_buffer)
{
	deque_push_back(token_buffer, ft_strdup("\\"));
	g_data.lexer->last_key = others;
}

static void	sub2(t_deque *token_buffer)
{
	if (g_data.lexer->last_key == back_slash)
	{
		deque_push_back(token_buffer, ft_strdup("\\"));
		g_data.lexer->last_key = others;
	}
	else if (g_data.lexer->last_key == dollar)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = back_slash;
	}
	else
		g_data.lexer->last_key = back_slash;
}

void	lexer_back_slash(t_deque *token_buffer)
{
	if (g_data.lexer->quote)
		sub1(token_buffer);
	else if (g_data.lexer->dquote)
		sub2(token_buffer);
	else
	{
		if (g_data.lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			g_data.lexer->last_key = others;
		}
		else if (g_data.lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			g_data.lexer->last_key = back_slash;
		}
		else
			g_data.lexer->last_key = back_slash;
	}
}
