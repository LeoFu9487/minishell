/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:56:14 by xli               #+#    #+#             */
/*   Updated: 2021/06/15 16:02:12 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(char *var)
{
	int				key_len;
	char			*var_key;
	t_double_list	*temp;

	key_len = ft_strlen(var);
	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (!ft_strncmp(var, var_key, ft_strlen(var))
			&& (int)ft_strlen(var) == var_key_len(temp->content))
		{
			if (ft_strchr(temp->content, '='))
			{
				deque_pop_one(g_data.env_list, temp, NULL);
				break ;
			}
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
	int		i;

	g_data.exit_status = 0;
	if ((args && !args[1]))
		return ;
	if (args[1] && args[1][0] == '-')
	{
		g_data.exit_status = 1;
		ft_putendl_fd("unset: does not take options\n", 2);
	}
	i = 0;
	while (args[++i])
	{
		if (!check_var_name(args[i]) || ((check_var_name(args[i]) 
			&& (args[i][ft_strlen(args[i]) - 1] == '+' 
			|| args[i][ft_strlen(args[i]) - 1] == '='))))
		{
			g_data.exit_status = 1;
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (!is_new_var(args[i]))
			unset_var(args[i]);
	}
}
