/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:56:14 by xli               #+#    #+#             */
/*   Updated: 2021/06/22 14:23:48 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(char *var)
{
	char			*var_key;
	t_double_list	*temp;

	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (!ft_strncmp(var, var_key, ft_strlen(var))
			&& (int)ft_strlen(var) == var_key_len(temp->content))
		{
			deque_pop_one(g_data.env_list, temp, NULL);
			break ;
		}
		temp = temp->next;
	}
}

/*
** Unset does not take any option.
** If no arg/exsiting env with no value/new env do nothing.
** If name of the arg is an invalid env => error.
** Else remove the arg from the env list.
*/

void	builtin_unset(char **args)
{
	g_data.exit_status = 0;
	if ((args && !args[1]))
		return ;
	if (args[1] && args[1][0] == '-')
	{
		g_data.exit_status = 1;
		ft_putendl_fd("unset: does not take options", 2);
		return ;
	}
	while (*(++args))
	{
		if (!check_var_name(*args) || ((check_var_name(*args)
					&& (args[0][ft_strlen(*args) - 1] == '+'
					|| args[0][ft_strlen(*args) - 1] == '='))))
		{
			g_data.exit_status = 1;
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(*args, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (!is_new_var(*args) && ft_strncmp(*args, "_", 2) != 0)
			unset_var(*args);
	}
}
