/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:45:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 21:47:02 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parse_pipe(t_deque *tokens, t_end_of_command eoc)
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
					result = check_parse_redir(new_token, eoc);
				else
					result = check_parse_redir(new_token, Pipe);
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
