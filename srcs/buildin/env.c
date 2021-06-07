/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 10:04:56 by xli               #+#    #+#             */
/*   Updated: 2021/06/07 10:25:41 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if there is '=' in the env variable
*/

static int	is_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		return (1);
	return (0);
}

/*
** Prints all the environnement variables with values on stdout.
** Without any options or any arguments.
*/

void	builtin_env(char **args)
{
	t_double_list	*temp;

	temp = g_data.env_list->head;
	if (*(args + 1))
		ft_putendl_fd("env: does not take options or arguments", 2);
	while (temp)
	{
		if (is_equal(temp->content))
			ft_putendl_fd(temp->content, 1);
		temp = temp->next;
	}
}
