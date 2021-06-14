/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:06:32 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 22:38:59 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	get_composed_key_6(unsigned char c[10])
{
	if (c[1] != 91 || c[2] != 49 || c[3] != 59 || c[4] != 53)
		return (NOT_DEFINED);
	if (c[5] == 65)
	{
		handle_ctrl_up();
		return (CTRL_UP);
	}
	if (c[5] == 66)
	{
		handle_ctrl_down();
		return (CTRL_DOWN);
	}
	if (c[5] == 67)
	{
		handle_ctrl_right();
		return (CTRL_RIGHT);
	}
	if (c[5] == 68)
	{
		handle_ctrl_left();
		return (CTRL_LEFT);
	}
	return (NOT_DEFINED);
}

static unsigned int	get_composed_key_4(unsigned char c[10])
{
	if (c[1] != 91 || c[3] != 126)
		return (NOT_DEFINED);
	if (c[2] == 53)
	{
		handle_home();
		return (HOME);
	}
	if (c[2] == 54)
	{
		handle_end();
		return (END);
	}
	if (c[2] == 51)
	{
		handle_delete();
		return (DELETE);
	}
	return (NOT_DEFINED);
}

static unsigned int	get_composed_key_3(unsigned char c[10])
{
	if (c[1] != 91)
		return (NOT_DEFINED);
	if (c[2] == 65)
	{
		handle_up();
		return (UP);
	}
	if (c[2] == 66)
	{
		handle_down();
		return (DOWN);
	}
	if (c[2] == 67)
	{
		handle_right();
		return (RIGHT);
	}
	if (c[2] == 68)
	{
		handle_left();
		return (LEFT);
	}
	return (NOT_DEFINED);
}

static unsigned int	get_composed_key_2(unsigned char c[10])
{
	if (c[1] == 97)
	{
		handle_alt_a();
		return (ALT_A);
	}
	if (c[1] == 98)
	{
		handle_alt_b();
		return (ALT_B);
	}
	if (c[1] == 108)
	{
		handle_alt_l();
		return (ALT_L);
	}
	return (NOT_DEFINED);
}

unsigned int	get_key(void)
{
	unsigned char	c[10];
	int				cnt;

	cnt = read(g_data.stdin_fd, c, 10);
	if (cnt < 1)
		message_exit(87, "get_key_error", 2);
	if (c[0] == CTRL_D)
		handle_ctrl_d();
	if (c[0] == CTRL_L)
		handle_ctrl_l();
	if (c[0] == BACKSPACE)
		handle_backspace();
	if (c[0] != 27 || cnt == 1)
		return ((unsigned)c[0]);
	if (cnt == 2)
		return (get_composed_key_2(c));
	if (cnt == 3)
		return (get_composed_key_3(c));
	if (cnt == 4)
		return (get_composed_key_4(c));
	if (cnt == 6)
		return (get_composed_key_6(c));
	return (NOT_DEFINED);
}
