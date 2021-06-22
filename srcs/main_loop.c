/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:54:40 by yfu               #+#    #+#             */
/*   Updated: 2021/06/22 17:22:00 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_empty_process(char *input_string, t_deque *tokens)
{
	if (ft_strncmp(input_string, g_data.history->tail->content,
			ft_strlen(input_string) + 1) != 0)
		deque_push_back(g_data.history, input_string);
	parse_and_execute(tokens);
}

static void	empty_process(char *input_string)
{
	if (g_data.lexer_error != NoError)
	{
		if (ft_strncmp(input_string, g_data.history->tail->content,
				ft_strlen(input_string) + 1) != 0)
			deque_push_back(g_data.history, input_string);
		g_data.exit_status = 2;
		print_unexpected_eol_message();
	}
	else
	{
		if (!str_is_space(input_string))
			g_data.exit_status = 0;
		ft_free(input_string);
	}
}

void	main_loop(void)
{
	char	*input_string;
	t_deque	*tokens;

	while (1)
	{
		g_data.pid = 0;
		print_prompt();
		input_string = get_input();
		raw_mode_switch(off);
		if (set_color(input_string))
			deque_push_back(g_data.history, input_string);
		else
		{
			tokens = lexer(input_string);
			if (tokens->size > 0)
				no_empty_process(input_string, tokens);
			else
				empty_process(input_string);
			deque_clear(tokens, free_token);
		}
	}
}
