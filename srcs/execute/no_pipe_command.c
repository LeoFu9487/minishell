/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:27:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 23:27:21 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipe_command(t_deque *cmd) // cmd is a list of tokens
{
	(void)cmd;
	// didn't open any fork yet
	//don't open a fork if the command is exit
}
