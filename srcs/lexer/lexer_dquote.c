/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:52:31 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 04:07:09 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_dquote(t_deque *token_buffer)
{
	if (g_data.lexer->last_key == back_slash || g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("\""));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->dquote ^= 1;
	}
	g_data.lexer->last_key = others;
}
