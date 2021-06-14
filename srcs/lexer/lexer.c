/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:57:21 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 22:59:50 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_init(void)
{
	g_data.lexer_error = NoError;
	g_data.lexer = ft_malloc(1, sizeof(t_lexer));
	g_data.lexer->dquote = 0;
	g_data.lexer->quote = 0;
	g_data.lexer->last_key = others;
}

void	put_buffer_in_tokens(t_deque *tokens, t_deque *token_buffer,
t_lexer_flag lexer_flag)
{
	char			*str;
	int				idx;
	t_double_list	*iterator;

	if (token_buffer->size == 0)
		return ;
	str = ft_calloc(token_buffer->size + 1, sizeof(char));
	idx = 0;
	iterator = token_buffer->head;
	while (iterator)
	{
		str[idx++] = *((char *)iterator->content);
		iterator = iterator->next;
		deque_pop_front(token_buffer, ft_free);
	}
	deque_push_back(tokens, init_token(str, lexer_flag));
	ft_free(str);
}

void	lexer_back_slash(t_deque *token_buffer)
{
	if (g_data.lexer->quote)
	{
		deque_push_back(token_buffer, ft_strdup("\\"));
		g_data.lexer->last_key = others;
	}
	else if (g_data.lexer->dquote)
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

void	lexer_semicolon(t_deque *tokens, t_deque *token_buffer)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup(";"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup(";"));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup(";"));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
		deque_push_back(tokens, init_token(";", _semicolon));
	}
	g_data.lexer->last_key = others;
}

void	lexer_redir_in(t_deque *tokens, t_deque *token_buffer, char *str, int *idx)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("<"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup("<"));
	}
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
			deque_push_back(tokens, init_token("<<", _redir_out_d));
		}
		else
			deque_push_back(tokens, init_token("<", _redir_out));
	}
	g_data.lexer->last_key = others;
}

void	lexer_redir_out(t_deque *tokens, t_deque *token_buffer, char *str, int *idx)
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
	g_data.lexer->last_key = others;
}

void	lexer_pipe(t_deque *tokens, t_deque *token_buffer)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_strdup("|"));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup("|"));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_strdup("|"));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
		deque_push_back(tokens, init_token("|", _pipe));
	}
	g_data.lexer->last_key = others;
}

void	lexer_dollar(t_deque *token_buffer)
{
	if (g_data.lexer->quote)
	{
		deque_push_back(token_buffer, ft_strdup("$"));
		g_data.lexer->last_key = others;
	}
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			g_data.lexer->last_key = others;
		}
		else if (g_data.lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			// in bash should be treated as "$$" "..."
			// but we don't deal with "$$", so it is treated as
			// "$" "$..." in minishell
			// which is, while it doesn't follow the argument format
			// $ is treated as a normal char  
		}
		else
			g_data.lexer->last_key = dollar;
	}
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

void	lexer_space(t_deque *tokens, t_deque *token_buffer, char input_char)
{
	if (g_data.lexer->quote)
		deque_push_back(token_buffer, ft_substr(&input_char, 0 ,1));
	else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_substr(&input_char, 0 ,1));
	}
	else if (g_data.lexer->last_key == back_slash)
		deque_push_back(token_buffer, ft_substr(&input_char, 0 ,1));
	else
	{
		if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
	}
	g_data.lexer->last_key = others;
}

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

t_deque	*lexer(char *input_string)
{
	t_deque	*tokens;
	t_deque	*token_buffer;
	int		idx[1];

	lexer_init();
	tokens = deque_init();
	token_buffer = deque_init();
	idx[0] = -1;
	while (input_string[++idx[0]])
	{
		if (input_string[idx[0]] == '\\')
			lexer_back_slash(token_buffer);
		else if (input_string[idx[0]] == '\'')
		{
			lexer_quote(token_buffer);
			if (g_data.lexer->quote == 0 && (ft_isspace(input_string[idx[0] + 1]) || input_string[idx[0] + 1] == '\0') && token_buffer->size == 0)
				deque_push_back(tokens, init_token("", _undefined));
		}
		else if (input_string[idx[0]] == '\"')
		{
			lexer_dquote(token_buffer);
			if (g_data.lexer->dquote == 0 && (ft_isspace(input_string[idx[0] + 1]) || input_string[idx[0] + 1] == '\0') && token_buffer->size == 0)
				deque_push_back(tokens, init_token("", _undefined));
		}
		else if (input_string[idx[0]] == ';')
			lexer_semicolon(tokens, token_buffer);
		else if (input_string[idx[0]] == '<')
			lexer_redir_in(tokens, token_buffer, input_string, idx);
		else if (input_string[idx[0]] == '>')
			lexer_redir_out(tokens, token_buffer, input_string, idx);
		else if (input_string[idx[0]] == '|')
			lexer_pipe(tokens, token_buffer);
		else if (input_string[idx[0]] == '$')
			lexer_dollar(token_buffer);
		else if (ft_isspace(input_string[idx[0]]))
			lexer_space(tokens, token_buffer, input_string[idx[0]]);
		else
			lexer_general(token_buffer, input_string, idx);
		if (input_string[idx[0]] == 0)
			break ;
	}
	if (g_data.lexer->quote)
		g_data.lexer_error = quote;
	else if (g_data.lexer->dquote)
		g_data.lexer_error = dquote;
	else if (g_data.lexer->last_key == dollar)
		deque_push_back(token_buffer, ft_strdup("$"));
	else if (g_data.lexer->last_key == back_slash)
		g_data.lexer_error = backslash;
	if (g_data.lexer_error == NoError)
		put_buffer_in_tokens(tokens, token_buffer, _undefined);
	deque_clear(token_buffer, ft_free);
	ft_free(g_data.lexer);
	return (tokens);
}
