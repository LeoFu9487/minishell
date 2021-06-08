/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:57:21 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 02:07:50 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*lexer_init(void)
{
	t_lexer	*lexer;

	lexer = ft_malloc(1, sizeof(t_lexer));
	lexer->dquote = 0;
	lexer->quote = 0;
	lexer->last_key = others;
	return (lexer);
}

void	put_buffer_in_tokens(t_deque *tokens, t_deque *token_buffer)
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
	deque_push_back(tokens, str);
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
		put_buffer_in_tokens(tokens, token_buffer);
		deque_push_back(tokens, ft_strdup(";"));
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
		put_buffer_in_tokens(tokens, token_buffer);
		deque_push_back(token_buffer, ft_strdup("<"));
		if (str[(*idx) + 1] == '<')
		{
			++(*idx);
			deque_push_back(token_buffer, ft_strdup("<"));
		}
		put_buffer_in_tokens(tokens, token_buffer);
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
		put_buffer_in_tokens(tokens, token_buffer);
		deque_push_back(token_buffer, ft_strdup(">"));
		if (str[(*idx) + 1] == '>')
		{
			++(*idx);
			deque_push_back(token_buffer, ft_strdup(">"));
		}
		put_buffer_in_tokens(tokens, token_buffer);
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
		put_buffer_in_tokens(tokens, token_buffer);
		deque_push_back(tokens, ft_strdup("|"));
	}
	g_data.lexer->last_key = others;
}

void	lexer_dollar(t_deque *token_buffer)//todo
{
	(void)token_buffer;
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
		put_buffer_in_tokens(tokens, token_buffer);
	}
	g_data.lexer->last_key = others;
}

void	lexer_general(t_deque *token_buffer, char *str, int *idx)//todo
{//need to especially deal with $?, environment variables
	//if (g_data.lexer->quote)
	//	deque_push_back(token_buffer, ft_substr(&input_char, 0 ,1));
	/*else if (g_data.lexer->dquote)
	{
		if (g_data.lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (g_data.lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_substr(&input_char, 0 ,1));
	}
	else
	{
		
	}*/
	g_data.lexer->last_key = others;
	(void)token_buffer;(void)str;(void)idx;
}

t_deque	*lexer(char *input_string)
{
	t_deque	*tokens;
	t_deque	*token_buffer;
	int		idx[1];

	g_data.lexer = lexer_init();
	tokens = deque_init();
	token_buffer = deque_init();
	idx[0] = -1;
	while (input_string[++idx[0]])
	{
		if (input_string[idx[0]] == '\\')
			lexer_back_slash(token_buffer);
		else if (input_string[idx[0]] == '\'')
			lexer_quote(token_buffer);
		else if (input_string[idx[0]] == '\"')
			lexer_dquote(token_buffer);
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
		if (input_string[idx[0]] == 0) // idx[0] may be modified in some functions so this line is necessary
			break ;
	}
	// if ... error ?
	// clear things ? (put the last into tokens)
	// free everything that was malloc / init ?
	return (tokens);
}

// in dquote, \ only got canceled if it's followed by $, ", \.
