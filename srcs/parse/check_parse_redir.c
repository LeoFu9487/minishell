/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:45:45 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 22:09:15 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_parse_redir_sub_sub(t_end_of_command eoc)
{
	if (eoc == NewLine)
	{
		if (g_data.lexer_error == dquote || g_data.lexer_error == quote
			|| g_data.lexer_error == backslash)
			ft_putstr_fd("minishell: unexpected EOL while looking for ", 2);
		else
			ft_putstr_fd("minishell: syntax error", 2);
		if (g_data.lexer_error == dquote)
			ft_putendl_fd("matching `\"\'", 2);
		else if (g_data.lexer_error == quote)
			ft_putendl_fd("matching `\'\'", 2);
		else if (g_data.lexer_error == backslash)
			ft_putendl_fd("matching `\\\'", 2);
		else
			ft_putendl_fd(" near unexpected token `newline\'", 2);
	}
	else if (eoc == Semicolon)
		ft_putendl_fd("minishell: syntax error near unexpected token `;\'", 2);
	else
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
}

static int	check_parse_redir_sub(int last_key_is_redir, t_deque *tokens,
	t_double_list *iterator, t_end_of_command eoc)
{
	if (last_key_is_redir)
	{
		g_data.exit_status = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			2);
		ft_putstr_fd(((t_token *)(iterator->content))->str, 2);
		ft_putendl_fd("\'", 2);
		return (1);
	}
	else if (iterator == tokens->tail)
	{
		g_data.exit_status = 258;
		check_parse_redir_sub_sub(eoc);
		return (1);
	}
	return (0);
}

int	check_parse_redir(t_deque *tokens, t_end_of_command eoc)
{
	int				last_key_is_redir;
	t_double_list	*iterator;

	last_key_is_redir = 0;
	iterator = tokens->head;
	while (iterator)
	{
		if (is_redir(((t_token *)(iterator->content))->lexer_flag))
		{
			if (check_parse_redir_sub(last_key_is_redir, tokens, iterator, eoc))
				return (1);
			last_key_is_redir = 1;
		}
		else
			last_key_is_redir = 0;
		iterator = iterator->next;
	}
	return (0);
}
