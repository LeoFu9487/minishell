/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:23:14 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 20:48:24 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** change set_redir
** change no_pipe_command
** change run_command
** while running, if fd < 0, error else dup2
** run set_redir for every command
** check from 0 to size - 1  if there is fd < 0, if so, print the error message
** still run the command, but check if there is fd < 0, exit directly
*/

t_iofd	*init_iofd(int size)
{
	t_iofd	*iofd;
	int		cnt;

	iofd = ft_malloc(size, sizeof(t_iofd));
	cnt = -1;
	while (++cnt < size)
	{
		iofd[cnt].in_file = ft_strdup("STDIN");
		iofd[cnt].out_file = ft_strdup("STDOUT");
		iofd[cnt].stdin_fd = STDIN_FILENO;
		iofd[cnt].stdout_fd = STDOUT_FILENO;
	}
	return (iofd);
}

void	ft_free_iofd(t_iofd *iofd, int size)
{
	while (--size >= 0)
	{
		ft_free(iofd[size].in_file);
		ft_free(iofd[size].out_file);
	}
	ft_free(iofd);
}

static void	sub(t_deque *tokens)
{
	t_deque	*cmd_list;
	t_deque	*cur_cmd;

	cmd_list = deque_init();
	cur_cmd = deque_init();
	while (tokens->size > 0)
	{
		if (((t_token *)tokens->head->content)->lexer_flag == _pipe)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
		}
		else if (((t_token *)tokens->head->content)->lexer_flag != _semicolon)
			deque_push_back(cur_cmd, tokens->head->content);
		if (((t_token *)tokens->head->content)->lexer_flag == _semicolon
			|| tokens->size == 1)
		{
			deque_push_back(cmd_list, cur_cmd);
			cur_cmd = deque_init();
			create_pipe(cmd_list);
		}
		deque_pop_front(tokens, NULL);
	}
	deque_clear(cur_cmd, free_token);
	deque_clear(cmd_list, NULL);
}

void	create_cmd(t_deque *tokens)
{
	if (handle_heredoc(tokens))
		sub(tokens);
}
