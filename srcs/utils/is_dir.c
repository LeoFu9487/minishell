/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:12:45 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 20:30:18 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(const char *path)
{
	struct stat	stat_buffer;

	if (stat(path, &stat_buffer) != 0)
		return (0);
	return (S_ISDIR(stat_buffer.st_mode));
}

int	file_exists(const char *filename)
{
	struct stat	stat_buffer;

	return (stat(filename, &stat_buffer) == 0);
}
