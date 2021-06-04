/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_arrow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:57:57 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 01:36:58 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_up(void)
{
	ft_putendl_fd("ctrl-up", 2);
}

void	handle_ctrl_down(void)
{
	ft_putendl_fd("ctrl-down", 2);
}

void	handle_ctrl_left(void)
{
	ft_putendl_fd("ctrl-left", 2);
}

void	handle_ctrl_right(void)
{
	ft_putendl_fd("ctrl-right", 2);
}
