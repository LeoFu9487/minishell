/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_util0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:17:31 by xli               #+#    #+#             */
/*   Updated: 2021/06/22 14:35:48 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** First char must be alpha or '_', the rest until null-terminated / '=' / '+='
** must be alphanum ('_' is not forbidden).
** Return 1 if var's name is valid
**/

int	check_var_name(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		g_data.exit_status = 1;
		return (0);
	}
	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+'
		&& (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (1);
	g_data.exit_status = 1;
	return (0);
}

/**
** If i > 0, var is a new var, else, var already exits in env list.
**/

int	is_new_var(char *var)
{
	int				i;
	char			*var_key;
	char			*var_temp;
	t_double_list	*temp;

	i = 0;
	var_temp = ft_substr(var, 0, var_key_len(var));
	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (ft_strncmp(var_temp, var_key, ft_strlen(var))
			|| (int)ft_strlen(var_temp) != var_key_len(temp->content))
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

static void	update_var_norm0(char *var, int const key_len, t_double_list *temp)
{
	char	*str;

	if (var[key_len] == '=')
	{
		ft_free(temp->content);
		temp->content = var;
	}
	else if (var[key_len] == '+' && var[key_len + 1] == '=')
	{
		str = ft_calloc(ft_strlen(temp->content)
				+ (ft_strlen(var) - key_len - 2) + 1, sizeof(char));
		ft_strcat(str, temp->content);
		ft_strcat(str, ft_substr(var, key_len + 2, ft_strlen(var)));
		temp->content = str;
	}
}

void	update_var(char *var)
{
	int				key_len;
	char			*var_key;
	t_double_list	*temp;

	key_len = var_key_len(var);
	if (var[key_len] == '\0')
		return ;
	temp = g_data.env_list->head;
	while (temp)
	{
		var_key = ft_substr(temp->content, 0, var_key_len(temp->content));
		if (!ft_strncmp(var, var_key, var_key_len(var))
			&& (int)var_key_len(var) == var_key_len(temp->content))
			update_var_norm0(var, key_len, temp);
		temp = temp->next;
	}
}
