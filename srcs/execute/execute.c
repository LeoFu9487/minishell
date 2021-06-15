/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 01:00:11 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 15:21:04 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub(char **args)
{
	if (ft_strncmp(args[0], "unset", 6) == 0)
	{
		//builtin_unset(args);
		message_exit(g_data.exit_status, "", -1);
	}
	if (ft_strncmp(args[0], "env", 4) == 0)
		builtin_env(args);
	if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		close(STDOUT_FILENO);
		builtin_exit(args);
		message_exit(g_data.exit_status, "", -1);
	}
}

void	launch_builtins(char **args)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		builtin_echo(args);
	if (ft_strncmp(args[0], "cd", 3) == 0)
	{
		//builtin_cd(args);
		message_exit(g_data.exit_status, "", -1);
	}
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		builtin_pwd(args);
	if (ft_strncmp(args[0], "export", 7) == 0)
	{
		//builtin_export(args);
		message_exit(g_data.exit_status, "", -1);
	}
	sub(args);
}

void	execute(char **args)
{
	launch_builtins(args);
	launch_bin(args);
}
