/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:22:00 by xli               #+#    #+#             */
/*   Updated: 2021/06/03 16:22:03 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argc(char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	return (argc);
}

void	builtin_echo(char **args)
{
	int	option_n;
	int	ct;

	option_n = 0;
	ct = 1;
	if (argc(args) > 1)
	{
		while (args[ct] && !ft_strncmp(args[ct], "-n", 3))
		{
			option_n = 1;
			ct++;
		}
		while (args[ct])
		{
			ft_putstr_fd(args[ct], 1);
			if (args[ct + 1])
				ft_putchar_fd(' ', 1);
			ct++;
		}
	}
	if (option_n == 0)
		ft_putchar_fd('\n', 1);
}
