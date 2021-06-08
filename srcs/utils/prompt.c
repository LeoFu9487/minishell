/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:36:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 16:46:35 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	if (g_data.exit_status == 0)
		ft_putstr_fd(GREEN, 2);
	else
		ft_putstr_fd(RED, 2);
	ft_putnbr_fd(g_data.exit_status, 2);
	ft_putstr_fd(NOCOLOR, 2);
	if (g_data.exit_status < 10)
		ft_putstr_fd("   ", 2);
	else if (g_data.exit_status < 100)
		ft_putstr_fd("  ", 2);
	else
		ft_putstr_fd(" ", 2);
	ft_putstr_fd(PROMPT_MESSAGE, 2);
}
