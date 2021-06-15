/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:25:59 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 19:14:34 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_deque *cmd)
{
	char	**args;
	int		cnt;

	if (cmd->size == 0)
		message_exit(0, "", -1);
	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	execute(args);
}
