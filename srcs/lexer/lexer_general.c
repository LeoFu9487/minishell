/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:52:45 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 03:52:58 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	lexer_general(t_deque *token_buffer, char *str, int *idx)
{
	char	*var[2];
	int		cnt;

	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_substr(str, *idx, 1));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			deque_push_back(token_buffer, ft_substr(str, *idx, 1));
		}
		else if (g_data.lexer->last_key == dollar)
		{
			if (str[*idx] == '?')
				var[0] = find_env_var("$?");
			else if (str[*idx] >= '0' && str[*idx] <= '9') // not supported yet
				var[0] = NULL;
			else if (ft_isalnum(str[*idx]) == 0 && str[*idx] != '_')
			{
				var[0] = NULL;
				deque_push_back(token_buffer, ft_strdup("$"));
				deque_push_back(token_buffer, ft_substr(str, *idx, 1));
			}
			else
			{
				var[1] = ft_substr(str, *idx, ft_strlen(str) - *idx);
				cnt = 0;
				while (var[1][cnt] && (ft_isalnum(var[1][cnt]) || var[1][cnt] == '_'))
					++cnt;
				var[1][cnt] = 0;
				var[0] = find_env_var(var[1]);
				ft_free(var[1]);
				(*idx) += cnt - 1;
			}
			if (var[0])
			{
				cnt = -1;
				while (var[0][++cnt])
					deque_push_back(token_buffer, ft_substr(var[0] + cnt, 0, 1));
				ft_free(var[0]);
			}
		}
		else
			deque_push_back(token_buffer, ft_substr(str, *idx, 1));
	}
	else if (g_data.lexer->last_key == dollar)
	{
		if (str[*idx] == '?')
			var[0] = find_env_var("$?");
		else if (str[*idx] >= '0' && str[*idx] <= '9') // not supported yet
			var[0] = NULL;
		else if (ft_isalnum(str[*idx]) == 0 && str[*idx] != '_')
		{
			var[0] = NULL;
			deque_push_back(token_buffer, ft_strdup("$"));
			deque_push_back(token_buffer, ft_substr(str, *idx, 1));
		}
		else
		{
			var[1] = ft_substr(str, *idx, ft_strlen(str) - *idx);
			cnt = 0;
			while (var[1][cnt] && (ft_isalnum(var[1][cnt]) || var[1][cnt] == '_'))
				++cnt;
			var[1][cnt] = 0;
			var[0] = find_env_var(var[1]);
			ft_free(var[1]);
			(*idx) += cnt - 1;
		}
		if (var[0])
		{
			cnt = -1;
			while (var[0][++cnt])
				deque_push_back(token_buffer, ft_substr(var[0] + cnt, 0, 1));
			ft_free(var[0]);
		}
	}
	else
		deque_push_back(token_buffer, ft_substr(str, *idx, 1));
	g_data.lexer->last_key = others;
}

