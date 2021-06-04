/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:06:32 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 00:15:03 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** UP : 27 91 65
** DOWN : 27 91 66
** RIGHT : 27 91 67
** LEFT : 27 91 68
** CTRL-D : 4
** CTRL-LEFT : 27 91 49 59 53 68 
** CTRL-RIGHT : 27 91 49 59 53 67
** CTRL-UP : 27 91 49 59 53 65 
** CTRL-DOWN : 27 91 49 59 53 66
** HOME : 27 91 53 126 !
** END : 27 91 54 126 !
** Ctrl-L : 12
** Alt-L : 27 108 !
** Ctrl-B : 2
** Alt-B : 27 98 !
** Ctrl-A : 1
** Alt-A : 27 97 !
** Ctrl-V : 22
** Delete : 27 91 51 126 !
** Backspace : 127 !
** 
** Ctrl-L : copy a whole line
** Alt-L : cut a whole line
** Ctrl-B : copy the line before the cursor
** Alt-B : cut the line before the cursor
** Ctrl-A : copy the line after the cursor
** Alt-A : cut the line after the cursor
** Ctrl-V : paste
*/
static unsigned	get_complicated_key()
{
	
}

unsigned get_key()
{
	unsigned char	c[10];
	int				cnt;

	cnt = read(0, c, 10);
	if (cnt < 1)
		message_exit(87, "get_key_error", 2);
	if (c[0] == CTRL_A)
		handle_ctrl_a();
	if (c[0] == CTRL_B)
		handle_ctrl_b();
	if (c[0] == CTRL_D)
		handle_ctrl_d();
	if (c[0] == CTRL_L)
		handle_ctrl_l();
	if (c[0] == CTRL_V)
		handle_ctrl_v();
	if (c[0] == BACKSPACE)
		handle_backspace();
	if (c[0] != 27)
		return ((unsigned char)c[0]);
	return (get_complicated_key());
}