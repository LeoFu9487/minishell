/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:54:40 by yfu               #+#    #+#             */
/*   Updated: 2021/06/12 20:25:20 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	main_loop(void)
{
	char	*input_string;
	t_deque	*tokens;

	while (1)
	{
		g_data.pid = 0;
		raw_mode_switch(on);
		print_prompt();
		input_string = get_input();
		raw_mode_switch(off);
		tokens = lexer(input_string);
		if (tokens->size > 0)
		{
			if (ft_strncmp(input_string, g_data.history->tail->content, ft_strlen(input_string)) != 0)
				deque_push_back(g_data.history, input_string); // when it's written in history, don't free input_string
			parse_and_execute(tokens);
		}
		else
		{
			ft_free(input_string);
			if (g_data.lexer_error != NoError)
			{
				g_data.exit_status = 2;
				if (g_data.lexer_error == dquote)
					ft_putendl_fd("minishell: unexpected EOL while looking for matching `\"\'", 2);
				else if (g_data.lexer_error == quote)
					ft_putendl_fd("minishell: unexpected EOL while looking for matching `\'\'", 2);
				else
					ft_putendl_fd("minishell: unexpected EOL while looking for matching `\\\'", 2);
			}
		}
		deque_clear(tokens, ft_free);
	}
}
