/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:22:00 by xli               #+#    #+#             */
/*   Updated: 2021/06/06 16:16:46 by xli              ###   ########lyon.fr   */
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

	while (*args && !ft_strncmp((*args), "-n", 2)) //check all the '-n'
	{
		i = 2; //first two char are '-n'
		while ((*args)[i] == 'n')
			i++;
		if ((*args)[i] == '\0') //if '\0' means only 'n' in the string >> n option = 1
			*option_n = 1;
		else //otherwise n option = 0 >> print out the string
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
	args++; //args[0] == echo "string"
	if (!(*args))
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	args = check_n(args, &option_n); //search for a n option
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option_n == 0)
		ft_putchar_fd('\n', 1);
}
