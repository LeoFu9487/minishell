/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:49:31 by xli               #+#    #+#             */
/*   Updated: 2021/06/13 21:51:05 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atoi_long(const char *str)
{
	long	nb;
	long	sign;
	long	i;

	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((long)(nb * sign));
}

/*
** Returns 1 if the string is only made of digit, return 0 otherwise.
*/

static int	is_only_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(ft_isdigit(str[i])))
			return (0);
	return (1);
}

/*
** If no arg, exits the whole minishell(exit code = g_data.exit_status).
** If >= 2 args, error message and do not exit(g_data.exit_status = 1).
** If only one arg AND it's positive or negetive num AND it's smaller than long,
** exit with atoi(code).
** If argument is not numeric or bigger than a long, exit(exit code 255).
*/

void	builtin_exit(char **args)
{
	int l;

	l = ft_atoi(args[1]);
	printf("%d\n", l);
	if (args && !args[1])
		message_exit(g_data.exit_status, "exit\n", 2);
	else if (args && args[1] && args[2])
	{
		g_data.exit_status = 1;
		ft_putendl_fd("exit: too many arguments", 2);
	}
	else if (args[1] && (ft_strlen(args[1]) > 20 //case len of args[1] > len of long max
		|| ((args[1][0] != '-' && args[1][0] != '+' && !ft_isdigit(args[1][0]))
		|| !is_only_digit(&args[1][1])) //case first char is '-'
		|| ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '\0') //case only '-' or '+'
		|| (args[1][0] != '-' && ft_atoi_long(args[1]) < 0) //case args[1] > long max
		|| (args[1][0] == '-' && ft_atoi_long(args[1]) > 0))) //case args[1] < long min
	{
		g_data.exit_status = 255;
		printf("exit\nexit: %s: numeric argument required\n", args[1]);
		message_exit(g_data.exit_status, "", 2);
	}
	g_data.exit_status = ft_atoi_long(args[1]);
	message_exit(g_data.exit_status, "exit\n", 2);
}

