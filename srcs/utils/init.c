/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 16:42:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/04 17:55:59 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(char **env) //todo
{
	//init g_data
	g_data.exit_status = 0;
	g_data.empty_buffer = 1;
	g_data.history = deque_init();
	init_env(env);
}

void	init_env(char **env) //todo
{
	int		idx[2];
	int		shlvl;
	char	*str[3];

	g_data.env_list = deque_init();
	idx[0] = -1;
	while (env[++idx[0]])
	{
		if (ft_strncmp(env[idx[0]], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(env[idx[0]] + 6);
			if (++shlvl > 999)
			{
				ft_putstr_fd("minishell: warning: shell level (", 2);
				ft_putnbr_fd(shlvl, 2);
				ft_putendl_fd(") too high, resetting to 1", 2);
				deque_push_back(g_data.env_list, "SHLVL=1");
			}
			else
			{
				str[1] = ft_itoa(shlvl);
				str[0] = ft_malloc(7 + ft_strlen(str[1]), sizeof(char));
				str[2] = "SHLVL=";
				idx[1] = -1;
				while (++idx[1] < 7)
					str[0][idx[1]] = str[2][idx[1]];
				idx[1] = -1;
				while (str[1][++idx[1]])
					str[0][6 + idx[1]] = str[1][idx[1]];
				str[0][6 + idx[1]] = 0;
				deque_push_back(g_data.env_list, str[0]);
				ft_free(str[1]);
			}
		}
		else
			deque_push_back(g_data.env_list, env[idx[0]]);
	}
	if (shlvl == -1) //not found : not finished yet
	{
		
	}
	//change SHLVL and other variables ?
	t_double_list	*it = g_data.env_list->head;
	while (it)
	{
		ft_putendl_fd(it->content, 2);
		it = it->next;
	}
	//problem : what if atoi bigger than int
}