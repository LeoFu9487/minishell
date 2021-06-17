/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 00:34:12 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 01:03:36 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char c)
{
	if (c == '/' || c == 0 || ft_isspace(c) || c == ';' || c == '>' || c == '<'
	|| c == '|')
		return (1);
	return (0);
}

static void	add_home_to_token_buffer(t_deque *token_buffer)
{
	char	*str[2];

	str[0] = get_home();
	str[1] = str[0];
	while (*str[0])
		deque_push_back(token_buffer, ft_substr(str[0]++, 0, 1));
	ft_free(str[1]);
}

void	lexer_tilde(t_deque *token_buffer, char *input_string,
int *idx)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("~"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup("~"));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("~"));
	else if (g_data.lexer->last_key == dollar)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup("~"));
	}
	else
	{
		if (token_buffer->size == 0 && check(input_string[*idx + 1]))
			add_home_to_token_buffer(token_buffer);
		else
			deque_push_back(token_buffer, ft_strdup("~"));
	}
}