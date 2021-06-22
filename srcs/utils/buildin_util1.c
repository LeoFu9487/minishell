/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:33 by xli               #+#    #+#             */
/*   Updated: 2021/06/22 14:34:10 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Length of variable before '=' or '+='
**/

int	var_key_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
		i++;
	return (i);
}

/*
** Sort env list by alphabetical order
*/

void	sort_env(t_deque **unsorted_env)
{
	t_double_list	*temp[3];

	temp[0] = (*unsorted_env)->head;
	while (temp[0])
	{
		temp[1] = (*unsorted_env)->head;
		while (temp[1]->next)
		{
			if (ft_strncmp(temp[1]->content, temp[0]->content, 1)
				> 0)
			{
				temp[2] = temp[1]->content;
				temp[1]->content = temp[0]->content;
				temp[0]->content = temp[2];
			}
			temp[1] = temp[1]->next;
		}
		temp[0] = temp[0]->next;
	}
}
