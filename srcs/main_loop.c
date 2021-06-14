/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:54:40 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 18:56:25 by yfu              ###   ########lyon.fr   */
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
		g_data.exit_status = 2;
		if (ft_strncmp(input_string, g_data.history->tail->content,
				ft_strlen(input_string) + 1) != 0)
			deque_push_back(g_data.history, input_string);
		ft_putstr_fd("minishell: unexpected EOL while looking for matching `",
			2);
		if (g_data.lexer_error == dquote)
			ft_putendl_fd("\"\'", 2);
		else if (g_data.lexer_error == quote)
			ft_putendl_fd("\'\'", 2);
		else
			ft_putendl_fd("\\\'", 2);
	}
	else
		ft_free(input_string);
}

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
			no_empty_process(input_string, tokens);
		else
			empty_process(input_string);
		deque_clear(tokens, free_token);
	}
}
