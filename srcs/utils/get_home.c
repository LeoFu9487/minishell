/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 00:52:58 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 01:16:57 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(void)
{
	char	*str;

	str = find_env_var("HOME");
	if (str)
		return (str);
	return (ft_strdup("~"));
}

/*
** #include <pwd.h>
** char	*get_home(void)
** {
** 	char	*homedir;
**
** 	homedir = find_env_var("HOME");
** 	if (homedir)
** 		return (homedir);
** 	homedir = getpwuid(getuid())->pw_dir;
** 	return (homedir);
**}
*/
