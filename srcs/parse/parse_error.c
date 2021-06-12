/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:39:51 by yfu               #+#    #+#             */
/*   Updated: 2021/06/12 23:44:31 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if there is error : change g_data, print error message, free new_token, return 1
// deal with >' (' error, not > error)
// problem : touch \>	touch \< touch \>\> touch \<\< touch \; touch \|
static int	check_redir(t_deque *tokens, t_end_of_command eoc)
{
	int				last_key_is_redir;
	t_double_list	*iterator;

	last_key_is_redir = 0;
	iterator = tokens->head;
	while (iterator)
	{
		if (is_redir(((t_token *)(iterator->content))->lexer_flag))
		{
			if (last_key_is_redir)
			{
				g_data.exit_status = 2;
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(((t_token *)(iterator->content))->str, 2);
				ft_putendl_fd("\'", 2);
				return (1);
			}
			else if (iterator == tokens->tail)
			{
				g_data.exit_status = 2;
				if (eoc == NewLine)
				{
					if (g_data.lexer_error == dquote)
						ft_putendl_fd("minishell: unexpected EOL while looking for matching `\"\'", 2);
					else if (g_data.lexer_error == quote)
						ft_putendl_fd("minishell: unexpected EOL while looking for matching `\'\'", 2);
					else if (g_data.lexer_error == backslash)
						ft_putendl_fd("minishell: unexpected EOL while looking for matching `\\\'", 2);
					else
						ft_putendl_fd("minishell: syntax error near unexpected token `newline\'", 2);
				}
				else if (eoc == Semicolon)
					ft_putendl_fd("minishell: syntax error near unexpected token `;\'", 2);
				else // pipe
					ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
				return (1);
			}
			last_key_is_redir = 1;
		}
		else
			last_key_is_redir = 0;
		iterator = iterator->next;
	}
	return (0);
}

static int	check_pipe(t_deque *tokens, t_end_of_command eoc)
{
	t_double_list	*iterator;
	t_deque			*new_token;
	int				result;

	new_token = deque_init();
	result = -1;
	iterator = tokens->head;
	while (iterator)
	{
		if (((t_token *)iterator->content)->lexer_flag != _pipe)
			deque_push_back(new_token, iterator->content);
		else if (iterator == tokens->tail) // | in the end
		{
			deque_clear(new_token, NULL);
			g_data.exit_status = 2;
			ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
			return (1);
		}
		if (((t_token *)iterator->content)->lexer_flag == _pipe || iterator == tokens->tail)
		{
			if (new_token->size > 0)
			{
				if (((t_token *)iterator->content)->lexer_flag != _pipe)
					result = check_redir(new_token, eoc);
				else
					result = check_redir(new_token, Pipe);
			}
			else
				ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
			if (new_token->size == 0 || result == 1)
			{
				deque_clear(new_token, NULL); // not deep copy, don't use ft_free
				g_data.exit_status = 2;
				return (1);
			}
			deque_clear(new_token, NULL); // not deep copy, don't use ft_free
			new_token = deque_init();
		}
		iterator = iterator->next;
	}
	deque_clear(new_token, NULL); // not deep copy
	return (0);
}

static int	check_semicolon(t_deque *tokens)
{
	t_double_list	*iterator;
	t_deque			*new_token;
	int				result;

	new_token = deque_init();
	result = -1;
	iterator = tokens->head;
	while (iterator)
	{
		if (((t_token *)iterator->content)->lexer_flag != _semicolon)
			deque_push_back(new_token, iterator->content);
		if (((t_token *)iterator->content)->lexer_flag == _semicolon || iterator == tokens->tail)
		{
			if (new_token->size > 0)
			{
				if (((t_token *)iterator->content)->lexer_flag != _semicolon)
					result = check_pipe(new_token, NewLine);
				else
					result = check_pipe(new_token, Semicolon);
			}
			else
				ft_putendl_fd("minishell: syntax error near unexpected token `;\'", 2);
			if (new_token->size == 0 || result == 1)
			{
				deque_clear(new_token, NULL); // not deep copy, don't use ft_free
				g_data.exit_status = 2;
				return (1);
			}
			deque_clear(new_token, NULL); // not deep copy, don't use ft_free
			new_token = deque_init();
		}
		iterator = iterator->next;
	}
	deque_clear(new_token, NULL); // not deep copy
	return (0);
}

int	check_parse_error(t_deque *tokens)
{
	return (check_semicolon(tokens));
}
