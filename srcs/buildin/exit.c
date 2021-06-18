/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 09:49:31 by xli               #+#    #+#             */
/*   Updated: 2021/06/18 14:38:44 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atoi_long(char *str)
{
	long long int	ct[3];

	if (!str || str[0] == 0)
		return (0);
	if (ft_isspace(*str))
		return (ft_atoi(str + 1));
	if (str[0] == '+' || str[0] == '-')
		ct[0] = 0;
	else
		ct[0] = -1;
	if (str[0] == '-')
		ct[2] = -1;
	else
		ct[2] = 1;
	ct[1] = 0;
	while (str[++ct[0]])
	{
		if (str[ct[0]] < '0' || str[ct[0]] > '9')
			return (ct[1] * ct[2]);
		ct[1] = 10 * ct[1] + str[ct[0]] - '0';
	}
	return ((long)ct[1] * ct[2]);
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
** Special case '     1    2  '
*/

static int	is_sp_case(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) || str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}


static void	exit_255_error(char *str)
{
	g_data.exit_status = 255;
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	message_exit(g_data.exit_status, ": numeric argument required\n", 2);
}

/*
** If no arg, exits the whole minishell(exit code = g_data.exit_status).
** If argument is not numeric or bigger than long max or smaller than long min, exit(exit code 255).
** If >= 2 args, error message and do not exit(g_data.exit_status = 1).
** Else exit with atoi(code).
*/

void	builtin_exit(char **args)
{
	if (args && !args[1])
		message_exit(g_data.exit_status, "exit\n", 1);
	else if (args[1] && !ft_isspace(args[1][0]) && (ft_strlen(args[1]) > 20 //case len of args[1] > len of long max
		|| ((args[1][0] != '-' && args[1][0] != '+' && !ft_isdigit(args[1][0]))
		|| !is_only_digit(&args[1][1])) //case first char is '-'
		|| ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '\0') //case only '-' or '+'
		|| (args[1][0] != '-' && ft_atoi_long(args[1]) < 0) //case args[1] > long max
		|| (args[1][0] == '-' && ft_atoi_long(args[1]) > 0))) //case args[1] < long min
		exit_255_error(args[1]);
	else if (is_sp_case(args[1]))
		exit_255_error(args[1]);
	else if (args && args[1] && args[2])
	{
		g_data.exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else
	{
		g_data.exit_status = ft_atoi_long(args[1]);
		message_exit(g_data.exit_status, "exit\n", 1);
	}
}
