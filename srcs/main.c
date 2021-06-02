/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:24:34 by yfu               #+#    #+#             */
/*   Updated: 2021/06/03 00:29:23 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_all(char **env) //todo
{
	//init g_data
	g_data.exit_status = 0;
	g_data.empty_buffer = 1;
	g_data.history = deque_init();
	init_env(env);
	//put env_list
	//change SHLVL and other variables ?
	(void)env;
}

static void	main_loop(void)
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
		ft_free(input_string);
		deque_clear(tokens, ft_free);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc > 1)
		message_exit(1, "minishell doesn't allow any argument", 2);
	init_all(env);
	catch_signal();
	main_loop();
	message_exit(0, "", -1);
}
