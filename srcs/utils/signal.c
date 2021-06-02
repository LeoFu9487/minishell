/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:06:43 by yfu               #+#    #+#             */
/*   Updated: 2021/06/02 23:36:02 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT) /* ctrl + C */
	{
		ft_putstr_fd("SIGINT\n", 1);
		exit(1);
	}
	if (signal == SIGQUIT) /* ctrl + \ */
	{
		ft_putstr_fd("SIGQUIT\n", 1);
		exit(2);
	}
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
