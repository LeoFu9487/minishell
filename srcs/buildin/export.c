/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:43:07 by xli               #+#    #+#             */
/*   Updated: 2021/06/15 16:11:19 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
** If no arguments, prints all the var sorted by alphabetical order on stdout.
** If arguments, adds the new var to env / update the values if already exist.
** Doesn't take any options.
*/

void	builtin_export(char **args)
{
	int	i;

	g_data.exit_status = 0;
	if (args && !args[1]) //export with no argument
		print_sorted_env();
	if (args[1] && args[1][0] == '-') //export does not handle options
	{
		g_data.exit_status = 1;
		ft_putendl_fd("export: does not take options", 2);
	}
	i = 0;
	while (args[++i])
	{
		if (!check_var_name(args[i])) //if var's name is not valid >> error
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		//else if (is_new_var(args[i])) //if var does not exsit in env list
		//	printf("new var\n");
		else if (!is_new_var(args[i])) //if var exsits in env list >> update env list
		{
			ft_putendl_fd("IN", 2);
			update_var(args[i]);
		}
	}
}
