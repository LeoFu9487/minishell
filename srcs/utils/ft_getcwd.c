/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 01:17:29 by yfu               #+#    #+#             */
/*   Updated: 2021/06/20 14:23:14 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(char *buf, size_t size)
{
	char	*str[2];

	str[0] = getcwd(buf, size);
	if (str[0] == NULL)
		return (NULL);
	str[1] = ft_strdup(str[0]);
	free(str[0]);
	return (str[1]);
}
