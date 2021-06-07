/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:57:21 by yfu               #+#    #+#             */
/*   Updated: 2021/06/07 14:30:50 by yfu              ###   ########lyon.fr   */
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

void	lexer_back_slash(t_lexer *lexer, t_deque *token_buffer)
{
	if (lexer->quote)
	{
		deque_push_back(token_buffer, ft_strdup("\\"));
		lexer->last_key = others;
	}
	else if (lexer->dquote)
	{
		if (lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			lexer->last_key = others;
		}
		else if (lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			lexer->last_key = back_slash;
		}
		else
			lexer->last_key = back_slash;
	}
	else
	{
		if (lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			lexer->last_key = others;
		}
		else if (lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			lexer->last_key = back_slash;
		}
		else
			lexer->last_key = back_slash;
	}
}

void	lexer_quote(t_lexer *lexer, t_deque *token_buffer)
{
	if (lexer->quote)
		lexer->quote = 0;
	else if (lexer->dquote)
	{
		if (lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		else if (lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		deque_push_back(token_buffer, ft_strdup("\'"));
	}
	else
	{
		if (lexer->last_key == dollar)
		{
			deque_push_back(token_buffer, ft_strdup("$"));
			lexer->quote = 1;
		}
		else if (lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\'"));
		else
			lexer->quote = 1;
	}
	lexer->last_key = others;
}

void	lexer_dquote(t_lexer *lexer, t_deque *token_buffer)
{
	if (lexer->last_key == back_slash || lexer->quote)
		deque_push_back(token_buffer, ft_strdup("\""));
	else
	{
		if (lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		lexer->dquote ^= 1;
	}
	lexer->last_key = others;
}

void	lexer_semicolon(t_lexer *lexer, t_deque *tokens, t_deque *token_buffer)
{
	if (lexer->quote)
		deque_push_back(token_buffer, ft_strdup(";"));
	else if (lexer->dquote)
	{
		if (lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup("\\"));
		else if (lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		deque_push_back(token_buffer, ft_strdup(";"));
	}
	else if (lexer->last_key == back_slash)
			deque_push_back(token_buffer, ft_strdup(";"));
	else
	{
		if (lexer->last_key == dollar)
			deque_push_back(token_buffer, ft_strdup("$"));
		put_buffer_in_tokens(tokens, token_buffer);
		deque_push_back(tokens, ft_strdup(";"));
	}
	lexer->last_key = others;
}

void	lexer_redir_in(t_lexer *lexer, t_deque *token_buffer)
{(void)lexer;(void)token_buffer;}

void	lexer_redir_out(t_lexer *lexer, t_deque *token_buffer)
{(void)lexer;(void)token_buffer;}

void	lexer_pipe(t_lexer *lexer, t_deque *token_buffer)
{(void)lexer;(void)token_buffer;}

void	lexer_dollar(t_lexer *lexer, t_deque *token_buffer)
{(void)lexer;(void)token_buffer;}

void	lexer_space(t_lexer *lexer, t_deque *token_buffer, char input_char)
{(void)lexer;(void)token_buffer;(void)input_char;}

void	lexer_general(t_lexer *lexer, t_deque *token_buffer, char input_char)
{//need to deal with variable, last_key ..
	deque_push_back(token_buffer, ft_strdup(&input_char));
	lexer->last_key = others;
	(void)lexer;(void)token_buffer;(void)input_char;
}


t_deque	*lexer(char *input_string)
{
	t_deque	*tokens;
	t_deque	*token_buffer;
	t_lexer	*lexer;
	int		idx[1];

	lexer = lexer_init();
	tokens = deque_init();
	token_buffer = deque_init();
	idx[0] = -1;
	while (input_string[++idx[0]])
	{
		if (input_string[idx[0]] == '\\')
			lexer_back_slash(lexer, token_buffer);
		else if (input_string[idx[0]] == '\'')
			lexer_quote(lexer, token_buffer);
		else if (input_string[idx[0]] == '\"')
			lexer_dquote(lexer, token_buffer);
		else if (input_string[idx[0]] == ';')
			lexer_semicolon(lexer, tokens, token_buffer);
		else if (input_string[idx[0]] == '<')
			lexer_redir_in(lexer, token_buffer);
		else if (input_string[idx[0]] == '>')
			lexer_redir_out(lexer, token_buffer);
		else if (input_string[idx[0]] == '|')
			lexer_pipe(lexer, token_buffer);
		else if (input_string[idx[0]] == '$')
			lexer_dollar(lexer, token_buffer);
		else if (ft_isspace(input_string[idx[0]]))
			lexer_space(lexer, token_buffer, input_string[idx[0]]);
		else
			lexer_general(lexer, token_buffer, input_string[idx[0]]);
	}
	// if ... error ?
	// clear things ?
	return (tokens);
}

// in dquote, \ only got canceled if it's followed by $, ", \.
