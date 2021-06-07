/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:57:21 by yfu               #+#    #+#             */
/*   Updated: 2021/06/07 10:44:27 by yfu              ###   ########lyon.fr   */
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
//problem : how to deal with redir ...
void	lexer_back_slash(t_lexer *lexer, t_deque *token_buffer)
{
	if (lexer->quote || lexer->last_key == back_slash)
	{
		deque_push_back(token_buffer, ft_strdup("\\"));
		lexer->last_key = others;
	}
	else
		lexer->last_key = back_slash;
}

void	lexer_quote(t_lexer *lexer, t_deque *token_buffer)
{
	if (lexer->quote)
		lexer->quote = 0;
	else if (lexer->dquote)
	{
		if (lexer->last_key == back_slash)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			deque_push_back(token_buffer, ft_strdup("\'"));
		}
		else
			deque_push_back(token_buffer, ft_strdup("\'"));
	}
	else if (lexer->last_key == back_slash)
	{
		if (lexer->dquote)
		{
			deque_push_back(token_buffer, ft_strdup("\\"));
			deque_push_back(token_buffer, ft_strdup("\'"));
		}
		else
			deque_push_back(token_buffer, ft_strdup("\'"));
	}
	
	lexer->last_key = others;
}

void	lexer_dquote(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_semicolon(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_redir_in(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_redir_out(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_pipe(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_dollar(t_lexer *lexer, t_deque *token_buffer)
{}

void	lexer_space(t_lexer *lexer, t_deque *token_buffer, char input_char)
{}

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
	while (++input_string[++idx[0]])
	{
		if (input_string[idx[0]] == '\\')
			lexer_back_slash(lexer, token_buffer);
		else if (input_string[idx[0]] == '\'')
			lexer_quote(lexer, token_buffer);
		else if (input_string[idx[0]] == '\"')
			lexer_dquote(lexer, token_buffer);
		else if (input_string[idx[0]] == ';')
			lexer_semicolon(lexer, token_buffer);
		else if (input_string[idx[0] == '<'])
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
		{
			//... normal things
		}
	}
	// if ... error ?
	// clear things ?
}

// in dquote, \ only got canceled if it's followed by $, ", \.
