/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:22:00 by xli               #+#    #+#             */
/*   Updated: 2021/06/22 13:34:51 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if echo command is followed by one or more "-n" option.
** "-n -nnnnn -n -nn" is valid for exemple.
*/

static char	**check_n(char **args, int *option_n)
{
	int	i;

	while (*args && !ft_strncmp((*args), "-n", 2))
	{
		i = 2;
		while ((*args)[i] == 'n')
			i++;
		if ((*args)[i] == '\0')
			*option_n = 1;
		else
			return (args);
		args++;
	}
	return (args);
}

/*
** Prints the args on stdoud, separated by one space, and end the line by '\n'.
** If n option is present, doesn't print the last '\n'.
*/

void	builtin_echo(char **args)
{
	int	i;
	int	option_n;

	i = 0;
	option_n = 0;
	args++;
	if (!(*args))
		message_exit(0, "\n", 1);
	args = check_n(args, &option_n);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option_n == 0)
		ft_putchar_fd('\n', 1);
	message_exit(0, "", -1);
}
