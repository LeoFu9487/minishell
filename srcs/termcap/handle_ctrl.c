/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:45:34 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 01:38:11 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_a(void)
{
	ft_putendl_fd("ctrl-a", 2);
}

void	handle_ctrl_b(void)
{
	ft_putendl_fd("ctrl-b", 2);
}

void	handle_ctrl_d(void)
{
	ft_putendl_fd("ctrl-d", 2);
}

void	handle_ctrl_l(void)
{
	ft_putendl_fd("ctrl-l", 2);
}

void	handle_ctrl_v(void)
{
	ft_putendl_fd("ctrl-v", 2);
}