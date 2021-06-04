/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:57:57 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 01:37:44 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_up(void)
{
	ft_putendl_fd("up", 2);
}

void	handle_down(void)
{
	ft_putendl_fd("down", 2);
}

void	handle_left(void)
{
	ft_putendl_fd("left", 2);
}

void	handle_right(void)
{
	ft_putendl_fd("right", 2);
}
