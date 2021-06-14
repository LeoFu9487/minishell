/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:12:45 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 19:06:57 by yfu              ###   ########lyon.fr   */
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
