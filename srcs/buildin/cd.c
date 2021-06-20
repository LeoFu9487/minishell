/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:26 by xli               #+#    #+#             */
/*   Updated: 2021/06/20 15:17:12 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_oldpwd(void)
{
	char	*old_pwd;
	char	*pwd;

	pwd = ft_strjoin("PWD=", g_data.pwd);
	old_pwd = ft_strjoin("OLD", pwd);
	ft_free(pwd);
	if (find_env_var("OLDPWD"))
	{
		deque_pop_one(g_data.env_list, find_env_var_line("OLDPWD"), ft_free);
		deque_push_back(g_data.env_list, old_pwd);
	}
	else
		deque_push_back(g_data.env_list, old_pwd);
}

static void	update_env_pwd(void)
{
	char	*pwd;

	ft_free(g_data.pwd);
	g_data.pwd = ft_getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", g_data.pwd);
	if (find_env_var("PWD"))
	{
		deque_pop_one(g_data.env_list, find_env_var_line("PWD"), ft_free);
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

	cwd = ft_getcwd(NULL, 0);
	if (!cwd && str && !ft_strncmp(str, ".", 2))
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		pwd = g_data.pwd;
		g_data.pwd = ft_strjoin(pwd, "/.");
		ft_free(pwd);
	}
	else if ((cwd || !ft_strncmp(str, "~", 2))
		&& !chdir(find_env_var("PWD")) && !chdir(find_env_var("OLDPWD")))
	{
		update_env_oldpwd();
		update_env_pwd();
	}
	ft_free(cwd);
	return (1);
}

/*
** Switch between OLDPWD and PWD
*/

static void	switch_pwd(void)
{
	char	*temp;
	char	*old_pwd;
	char	*pwd;

	if (chdir(find_env_var("OLDPWD")))
	{
		g_data.exit_status = 1;
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return ;
	}
	temp = find_env_var("PWD");
	old_pwd = ft_strjoin("OLDPWD=", temp);
	temp = find_env_var("OLDPWD");
	pwd = ft_strjoin("PWD=", temp);
	ft_free(temp);
	deque_pop_one(g_data.env_list, find_env_var_line("OLDPWD"), ft_free);
	deque_push_back(g_data.env_list, old_pwd);
	deque_pop_one(g_data.env_list, find_env_var_line("PWD"), ft_free);
	deque_push_back(g_data.env_list, pwd);
	ft_putendl_fd(find_env_var("PWD"), 2);
}

/*
** If no arg, changes the working directory to $HOME if it exists.
** Otherwise changes the working directory using first arg.
** Handles absolute path, relative path and '~'.
*/

void	builtin_cd(char **args)
{
	g_data.exit_status = 0;
	if (!args[1] || !ft_strncmp(args[1], "~", 2)
		|| !ft_strncmp(args[1], "--", 3))
	{
		if (chdir(find_env_var("HOME"))) //fail to find HOME
		{
			g_data.exit_status = 1;
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return ;
		}
	}
	else if (args[1] && !ft_strncmp(args[1], "-", 2))
		switch_pwd();
	else if (chdir(args[1]))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	update_pwd(args[1]);
}
