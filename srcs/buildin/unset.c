/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:56:14 by xli               #+#    #+#             */
/*   Updated: 2021/06/14 17:25:50 by xli              ###   ########lyon.fr   */
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
				//printf("IN\n");
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

	if ((args && !args[1]))
		message_exit(0, "", 1);
	if (args[1] && args[1][0] == '-')
		message_exit(1, "unset: does not take options\n", 2);
	i = 0;
	while (args[++i])
	{
		if (!check_var_name(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			message_exit(1, "': not a valid identifier\n", 2);
		}
		else if (!is_new_var(args[i]))
			unset_var(args[i]);
	}
	message_exit(0, "", -1);
}
