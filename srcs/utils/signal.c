/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:06:43 by yfu               #+#    #+#             */
/*   Updated: 2021/06/07 01:19:53 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT) /* ctrl + C */
	{
		ft_putstr_fd("SIGINT\n", 1);
		raw_mode_switch(off);
		exit(1);
	}
	if (signal == SIGQUIT) /* ctrl + \ */
	{
		ft_putstr_fd("SIGQUIT\n", 1);
		raw_mode_switch(off);
		exit(2);
	}
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
