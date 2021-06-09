/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:43:07 by xli               #+#    #+#             */
/*   Updated: 2021/06/09 15:25:05 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
**	UTILS
**	Length of variable before '=' or '+='
**/

static int	var_key_len(char *var)
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

static void	sort_env(t_deque **unsorted_env)
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
** Duplicates the env_list, sort it and prints it out with " " around env values.
*/

static void	print_sorted_env(void)
{
	t_double_list	*temp;
	t_double_list	*it;
	t_deque			*dup_env;
	char			*var_key;

	temp = g_data.env_list->head;
	dup_env = deque_init();
	while (temp)
	{
		deque_push_back(dup_env, temp->content);
		temp = temp->next;
	}
	sort_env(&dup_env);
	it = dup_env->head;
	while (it)
	{
		var_key = ft_substr(it->content, 0, var_key_len(it->content));
		if (find_env_var(var_key))
			printf("declare -x %s=\"%s\"\n", var_key, find_env_var(var_key));
		else
			printf("declare -x %s\n", var_key);
		it = it->next;
	}
}

/*
** First char must be alpha, the rest until null-terminated / '=' / '+='
** must be alphanum ('_' is not forbidden).
** Return 1 if var's name is valid
**/

/*static int	check_var_name(char *var)
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
}*/

/**
** Return 1 if var does not exsit in env list
**/

/*static int	is_new_var(char *var)
{
	int				var_len; //len of var before '=' or '+='
	t_double_list	*temp;

	var_len = var_name_len(var);
	temp = g_data.env_list->head;
	while (temp)
	{
		if (ft_strncmp(var, temp->content, var_len)
			|| var_name_len(var) != var_name_len(temp->content))
			return (1);
		temp = temp->next;
	}
	return (0);
}*/

/*
** Reallocates an array of *char (previous variables + new ones from export).
*/

//int	create_new_env()

/*
** If no arguments, prints all the var sorted by alphabetical order on stdout.
** If arguments, adds the new var to env / update the values if already exist.
** Doesn't take any options.
*/

void	builtin_export(char **args)
{
	//int	i;

	if (args && !args[1]) //export with no argument
		print_sorted_env();
	/*
	if (args[1][0] == '-') //export does not handle options
		message_exit(1, "export: does not take options\n", 2);
	i = 0;
	while (args[++i])
	{
		if (!check_var_name(args[1])) //if var's name is not valid >> error
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			message_exit(1, "", 2);
		}
		else if (is_new_var(args[i])) //if var does not exsit in env list
			printf("new var");
		else //if var exsits in env list >> update env list
			printf("old var");
	}
	*/
	message_exit(0, "", -1);
}
