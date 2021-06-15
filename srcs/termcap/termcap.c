/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:49:16 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 00:49:13 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ICANON : canonical mode
** canonical mode : input line is available when encounter delimiter (NL)
** noncanonical mode : input is availbale immediately
** MIN == 1, TIME == 0 : read blocks when 1 byte is read
*/

static t_termcap	*init_termcap(void)
{
	t_termcap	*termcap;

	termcap = ft_malloc(1, sizeof(t_termcap));
	tcgetattr(STDIN_FILENO, &(termcap->original));
	termcap->raw = termcap->original;
	termcap->raw.c_lflag &= ~(ICANON | ECHO);
	termcap->raw.c_cc[VMIN] = 1;
	termcap->raw.c_cc[VTIME] = 0;
	return (termcap);
}

/*
** raw_mode_switch(on);
** raw_mode_switch(off);
*/

void	raw_mode_switch(t_switch e)
{
	static t_termcap	*termcap = NULL;

	if (!termcap)
		termcap = init_termcap();
	if (e == on)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &(termcap->raw));
		ft_putstr_fd(g_data.color, 2);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &(termcap->original));
		ft_putstr_fd(NOCOLOR, 2);
	}
}
