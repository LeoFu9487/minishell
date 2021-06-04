/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:59:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 01:40:07 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_backspace(void)
{
	ft_putendl_fd("backspace", 2);
}

void	handle_home(void)
{
	ft_putendl_fd("home", 2);
}

void	handle_end(void)
{
	ft_putendl_fd("end", 2);
}

void	handle_delete(void)
{
	ft_putendl_fd("delete", 2);
}