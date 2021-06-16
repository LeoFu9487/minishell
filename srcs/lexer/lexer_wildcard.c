/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 03:24:05 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 03:34:35 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_wildcard(t_deque *token_buffer)
{
	char	*str;

	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("*"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		if (g_data.lexer->last_key != dollar)
			deque_push_back(token_buffer, ft_strdup("*"));
	}
	else
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("*"));
		else if (g_data.lexer->last_key == others)
		{
			str = ft_calloc(2, sizeof(char));
			str[0] = -1;
			deque_push_back(token_buffer, str);
		}
	}
	g_data.lexer->last_key = others;
}
