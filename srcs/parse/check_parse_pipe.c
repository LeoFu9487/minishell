/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:45:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 22:49:08 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_parse_pipe_sub_2(t_deque *new_token, t_end_of_command eoc,
t_double_list *iterator)
{
	int	result;

	result = -1;
	if (new_token->size > 0)
	{
		if (((t_token *)iterator->content)->lexer_flag != _pipe)
			result = check_parse_redir(new_token, eoc);
		else
			result = check_parse_redir(new_token, Pipe);
	}
	else
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
	if (new_token->size == 0 || result == 1)
	{
		deque_clear(new_token, NULL);
		g_data.exit_status = 258;
		return (1);
	}
	deque_clear(new_token, NULL);
	return (0);
}

static void	check_parse_pipe_sub_1(t_deque *new_token)
{
	deque_clear(new_token, NULL);
	g_data.exit_status = 258;
	ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 2);
}

int	check_parse_pipe(t_deque *tokens, t_end_of_command eoc)
{
	t_double_list	*iterator;
	t_deque			*new_token;

	new_token = deque_init();
	iterator = tokens->head;
	while (iterator)
	{
		if (((t_token *)iterator->content)->lexer_flag != _pipe)
			deque_push_back(new_token, iterator->content);
		else if (iterator == tokens->tail)
		{
			check_parse_pipe_sub_1(new_token);
			return (1);
		}
		if (((t_token *)iterator->content)->lexer_flag == _pipe
			|| iterator == tokens->tail)
		{
			if (check_parse_pipe_sub_2(new_token, eoc, iterator))
				return (1);
			new_token = deque_init();
		}
		iterator = iterator->next;
	}
	deque_clear(new_token, NULL);
	return (0);
}
