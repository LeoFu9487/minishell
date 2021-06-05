/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:54:40 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 02:55:58 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	main_loop(void)
{
	char	*input_string;
	t_deque	*tokens;

	while (1)
	{
		raw_mode_switch(on);
		ft_putstr_fd(PROMPT_MESSAGE, 2);
		input_string = get_input();
		tokens = lexer(input_string);
		if (tokens->size > 0)
		{
			deque_push_back(g_data.history, input_string);
			raw_mode_switch(off);
			parse_and_execute(tokens);
		}
		//don't free input_string because it's in history
		deque_clear(tokens, ft_free);
	}
}
