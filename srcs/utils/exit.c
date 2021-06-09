/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:17:50 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 04:03:07 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** message_exit(int exit_code, char *message, int fd)
** : free everything, put message in fd and exit(exit_code)
*/

void	message_exit(int exit_code, char *message, int fd)
{
	raw_mode_switch(off);
	ft_putstr_fd(message, fd);
	ft_free_all();
	exit(exit_code);
}
