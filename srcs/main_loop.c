/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:54:40 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 03:24:18 by yfu              ###   ########lyon.fr   */
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
		raw_mode_switch(off);
		tokens = lexer(input_string);
		if (tokens && tokens->size > 0)
		{
			deque_push_back(g_data.history, input_string); // when it's written in history, don't free input_string
			if (g_data.lexer_error == 0)
				parse_and_execute(tokens);
		}
		else
			ft_free(input_string);
		deque_clear(tokens, ft_free);
	}
}
