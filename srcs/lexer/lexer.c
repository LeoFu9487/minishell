/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:57:21 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 03:23:04 by yfu              ###   ########lyon.fr   */
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
	if (lexer_flag == _undefined && has_wild_card(str))
		wild_card(tokens, str);
	else
		deque_push_back(tokens, init_token(str, lexer_flag));
	ft_free(str);
}

static void	sub2(t_deque *tokens, t_deque *token_buffer,
char *input_string, int idx[1])
{
	if (input_string[idx[0]] == ';')
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
	else if (input_string[idx[0]] == '*')
		lexer_wildcard(token_buffer);
	else
		lexer_general(token_buffer, input_string, idx);
}

static int	sub1(t_deque *tokens, t_deque *token_buffer, char *input_string,
int idx[1])
{
	if (input_string[idx[0]] == '\\')
		lexer_back_slash(token_buffer);
	else if (input_string[idx[0]] == '\'')
	{
		lexer_quote(token_buffer);
		if (g_data.lexer->quote == 0 && (ft_isspace(input_string[idx[0] + 1])
				|| input_string[idx[0] + 1] == '\0') && token_buffer->size == 0)
			deque_push_back(tokens, init_token("", _undefined));
	}
	else if (input_string[idx[0]] == '\"')
	{
		lexer_dquote(token_buffer);
		if (g_data.lexer->dquote == 0 && (ft_isspace(input_string[idx[0] + 1])
				|| input_string[idx[0] + 1] == '\0') && token_buffer->size == 0)
			deque_push_back(tokens, init_token("", _undefined));
	}
	else
		sub2(tokens, token_buffer, input_string, idx);
	if (input_string[idx[0]] == 0)
		return (1);
	return (0);
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
		if (sub1(tokens, token_buffer, input_string, idx))
			break ;
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
