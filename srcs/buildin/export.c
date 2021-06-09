/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:43:07 by xli               #+#    #+#             */
/*   Updated: 2021/06/09 09:23:08 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sorts the env_list and prints it on stdout.
*/

void	print_sorted_env(char **args)
{
	int				sorted;
	t_double_list	*temp;

	(void)args;
	sorted = 0;
	temp = g_data.env_list->head;
	while (temp && temp->next)
	{
		if (temp->content > temp->next->content)
		{
			ft_sort((int *)temp, (int *)temp->next, ft_ascending);
			sorted = 1;
		}
		temp = temp->next;
	}
	while (sorted);
	temp = g_data.env_list->head;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(temp->content, 1);
		temp = temp->next;
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
**	UTILS
**	Length of variable before '=' or '+='
**/

int	var_len(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '=')
		i++;
	return (i);
}

/**
** Return 1 if var does not exsit in env list
**/

int	is_new_var(char *var)
{
	int				var_len; //len of var before '=' or '+='
	int				i;
	t_double_list	*temp;

	var_len = var_len(var);
	temp = g_data.env_list->head;
	while (temp)
	{
		if (ft_strncmp(var, temp->content, var_len)
			|| var_len(var) != var_len(temp->content)
			return (1);
		temp = temp->next;
	}
	return (0);
}

/*
** If no arguments, prints all the var sorted by alphabetical order on stdout.
** If arguments, adds the new var to env / update the values if already exist.
** Doesn't take any options.
*/

void	builtin_export(char **args)
{
	int	i;

	if (args && !args[1]) //export with no argument
		print_sorted_env(args);
	if (args[1][0] == '-') //export does not handle options
		ft_putendl_fd("export: does not take options", 2);
	i = 0;
	while (args[++i])
	{
		if (!check_var_name(args[1])) //if var's name is not valid >> error
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (is_new_var(args[i])) //if var does not exsit in env list

		else //if var exsits in env list >> update env list
	}
}
