/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 00:56:35 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 02:03:58 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_color(char *str)
{
	if (ft_strncmp(str, "BLACK", 6) == 0)
		return (1);
	if (ft_strncmp(str, "RED", 4) == 0)
		return (1);
	if (ft_strncmp(str, "GREEN", 6) == 0)
		return (1);
	if (ft_strncmp(str, "YELLOW", 7) == 0)
		return (1);
	if (ft_strncmp(str, "BLUE", 5) == 0)
		return (1);
	if (ft_strncmp(str, "PURPLE", 7) == 0)
		return (1);
	if (ft_strncmp(str, "CYAN", 5) == 0)
		return (1);
	if (ft_strncmp(str, "WHITE", 6) == 0)
		return (1);
	return (0);
}

static char	*color_str(char *str)
{
	if (ft_strncmp(str, "BLACK", 6) == 0)
		return (BLACK);
	if (ft_strncmp(str, "RED", 4) == 0)
		return (RED);
	if (ft_strncmp(str, "GREEN", 6) == 0)
		return (GREEN);
	if (ft_strncmp(str, "YELLOW", 7) == 0)
		return (YELLOW);
	if (ft_strncmp(str, "BLUE", 5) == 0)
		return (BLUE);
	if (ft_strncmp(str, "PURPLE", 7) == 0)
		return (PURPLE);
	if (ft_strncmp(str, "CYAN", 5) == 0)
		return (CYAN);
	if (ft_strncmp(str, "WHITE", 6) == 0)
		return (WHITE);
	return (NULL);
}

int	set_prompt_color(char *str)
{
	if (*(str++) != 'P')
		return (0);
	while (*str == '_')
		++str;
	if (!is_color(str))
		return (0);
	g_data.prompt_color = color_str(str);
	return (1);
}

int	set_color(char *str)
{
	if (set_prompt_color(str))
		return (1);
	if (!is_color(str))
		return (0);
	g_data.color = color_str(str);
	return (1);
}
