/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 00:56:35 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 01:23:07 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub(char *str, int idx[2])
{
	if (ft_strncmp(str, "YELLOW", 7) == 0)
	{
		g_data.color = YELLOW;
		idx[1] = 1;
	}
	if (ft_strncmp(str, "BLUE", 5) == 0)
	{
		g_data.color = BLUE;
		idx[1] = 1;
	}
	if (ft_strncmp(str, "PURPLE", 7) == 0)
	{
		g_data.color = PURPLE;
		idx[1] = 1;
	}
	if (ft_strncmp(str, "CYAN", 5) == 0)
	{
		g_data.color = CYAN;
		idx[1] = 1;
	}
	if (ft_strncmp(str, "WHITE", 6) == 0)
	{
		g_data.color = WHITE;
		idx[1] = 1;
	}
}

int	set_color(char *input_string)
{
	char	*str;
	int		idx[2];

	str = ft_strdup(input_string);
	idx[0] = -1;
	while (str[++idx[0]])
		str[idx[0]] = ft_toupper(str[idx[0]]);
	idx[1] = 0;
	if (ft_strncmp(str, "BLACK", 6) == 0)
	{
		g_data.color = BLACK;
		idx[1] = 1;
	}
	if (ft_strncmp(str, "RED", 4) == 0 || ft_strncmp(str, "GREEN", 6) == 0)
		idx[1] = 1;
	if (ft_strncmp(str, "RED", 4) == 0)
		g_data.color = RED;
	if (ft_strncmp(str, "GREEN", 6) == 0)
		g_data.color = GREEN;
	sub(str, idx);
	ft_free(str);
	return (idx[1]);
}
