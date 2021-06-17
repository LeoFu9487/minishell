/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:26 by xli               #+#    #+#             */
/*   Updated: 2021/06/18 01:11:16 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_oldpwd(void)
{
	char	*old_pwd;
	char	*pwd;

	pwd = ft_strjoin("PWD=", g_data.pwd);
	old_pwd = ft_strjoin("OLD", pwd);
	if (find_env_var("OLDPWD"))
	{
		deque_pop_one(g_data.env_list, find_env_var_line("OLDPWD"), NULL);
		deque_push_back(g_data.env_list, old_pwd);
	}
	else
		deque_push_back(g_data.env_list, old_pwd);
}

static void	update_env_pwd(void)
{
	char	*pwd;

	g_data.pwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", g_data.pwd);
	if (find_env_var("PWD"))
	{
		deque_pop_one(g_data.env_list, find_env_var_line("PWD"), NULL);
		deque_push_back(g_data.env_list, pwd);
	}
	else
		deque_push_back(g_data.env_list, pwd);
}

/*
** If PWD does not exsit anymore => error.
** Otherwise update PWD and OLDPWD.
*/

static int	update_pwd(char *str)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && str && !ft_strncmp(str, ".", 1))
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		pwd = g_data.pwd;
		g_data.pwd = ft_strjoin(pwd, "/.");
		free(pwd);
	}
	else if (cwd || !ft_strncmp(str, "~", 2))
	{
		update_env_oldpwd();
		update_env_pwd();
	}
	return (1);
}

/*
** If no arg, changes the working directory to $HOME if it exists.
** Otherwise changes the working directory using first arg.
** Handles absolute path, relative path and '~'.
*/

void	builtin_cd(char **args)
{
	g_data.exit_status = 0;
	if (args && (!args[1] || (args[1] && args[1][0] == '~')))
	{
		if (chdir(find_env_var("HOME"))) //fail to find HOME
		{
			g_data.exit_status = 1;
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return ;
		}
	}
	else if (args[1] && args[1][0] == '-') //cd does not handle options
	{
		g_data.exit_status = 1;
		ft_putendl_fd("cd: does not take options", 2);
	}
	else if (chdir(args[1]))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	update_pwd(args[1]);
}
