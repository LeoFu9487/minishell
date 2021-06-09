/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 01:31:35 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 02:23:58 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_env_char(void)
{
	char			**env;
	int				cnt;
	t_double_list	*iterator;

	env = ft_calloc(1 + g_data.env_list->size, sizeof(char *));
	cnt = 0;
	iterator = g_data.env_list->head;
	while (iterator)
	{
		env[cnt++] = iterator->content;
		iterator = iterator->next;
	}
	return (env);
}

static void	run_path(char *path, char **args, char **env)
{
	execve(path, args, env);
	ft_putstr_fd("minishell: ", 2);
	perror(args[0]);
	if (errno == 13)
		message_exit(126, "", -1);
	message_exit(127, "", -1);
}

static void	multiple_path(char *path, int ct[3], char **args, char **env)
{
	path[ct[1]++] = '/';
	path[ct[1]] = 0;
	ft_strcat(path, args[0]);
	execve(path, args, env);
	if (errno == 13)
		ct[2] = 1;
	ct[1] = 0;
}

static void	find_path(char **args, char **env)
{
	char	*path; // path that is going to be used in execve
	char	*var; // the value of global variable PATH
	int		ct[3];

	ct[2] = 0;
	var = find_env_var("PATH");
	path = ft_calloc(ft_strlen(var) + 5
			+ ft_strlen(args[0]), sizeof(char));
	ct[1] = 0;
	while (var[0])
	{
		if (var[0] != ':')
		{
			path[ct[1]++] = var[0];
			path[ct[1]] = 0;
		}
		if (var[0] == ':' || var[1] == 0)
			multiple_path(path, ct, args, env);
		++var;
	}
	ft_putstr_fd(args[0], 2);
	if (ct[2])
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": command not found", 2);
	message_exit(127 - ct[2], "", -1);
}

void	launch_bin(char **args)
{
	char	**env;

	env = build_env_char();
	if (ft_strchr(args[0], '/'))
		run_path(args[0], args, env);
	if (find_env_var_line("PATH") == NULL)
		run_path(args[0], args, env);
	find_path(args, env);
}
