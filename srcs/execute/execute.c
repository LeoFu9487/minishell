/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 01:00:11 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 01:23:16 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_builtins(char **args)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		builtin_echo(args);
	//if (ft_strncmp(args[0], "cd", 3) == 0)
	//	builtin_cd(args);
	//if (ft_strncmp(args[0], "pwd", 4) == 0)
	//	builtin_pwd(args);
	//if (ft_strncmp(args[0], "export", 7) == 0)
	//	builtin_export(args);
	//if (ft_strncmp(args[0], "unset", 6) == 0)
	//	builtin_unset(args);
	if (ft_strncmp(args[0], "env", 4) == 0)
		builtin_env(args);
	//if (ft_strncmp(args[0], "exit", 5) == 0)
	//	builtin_exit(args);
}

void	execute(char **args) // need to execve or exit
{
	launch_builtins(args);
	exit(0);
}