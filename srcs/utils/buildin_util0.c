/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_util0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:17:31 by xli               #+#    #+#             */
/*   Updated: 2021/06/15 15:14:15 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**	Length of variable before '=' or '+='
**/

int	var_key_len(char *var)
{
	int i;

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

/*
** First char must be alpha, the rest until null-terminated / '=' / '+='
** must be alphanum ('_' is not forbidden).
** Return 1 if var's name is valid
**/

int	check_var_name(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) || var[0] == '_')
		return (0);
	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+'
		&& (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (1);
	return (0);
}

/**
** If i > 0, var is a new var, else, var already exits in env list.
**/

int	is_new_var(char *var)
{
	int				i;
	char			*var_key;
	t_double_list	*temp;

	i = 0;
	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (ft_strncmp(var, var_key, ft_strlen(var))
			|| (int)ft_strlen(var) != var_key_len(temp->content))
			i++;
		else
		{
			i = 0;
			break ;
		}
		temp = temp->next;
	}
	return (i);
}

/*
** If var does not have any value(no '='), do nothing.
** Else if('='), frees the previous var and adds the new one value.
** Else('+='), cat previous value and new one.
*/
/*
void	update_var(char *var)
{
	int				key_len;
	char			*var_key;
	char			*str;
	t_double_list	*temp;

	key_len = var_key_len(var);
	if (var[key_len] == '\0') //var does not have any value(no '=')
		return ;
	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (!ft_strncmp(var, var_key, ft_strlen(var))
			|| (int)ft_strlen(var) == var_key_len(temp->content))
		{
			if (var[key_len] == '=') //input: var = value
			{
				deque_pop_one(g_data.env_list, temp, NULL);
				temp->content = var;
			}
			else if (var[key_len] == '+') //input: var += value
			{
				str = ft_calloc(ft_strlen(find_env_var(temp) + (ft_strlen(temp->content) - key_len - 1)) + 1);
			}
		}
		temp = temp->next;
	}
}
*/
