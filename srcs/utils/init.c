/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 16:42:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/13 14:22:04 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*init_token(char *str, t_lexer_flag lexer_flag)
{
	t_token	*token;

	token = ft_malloc(1, sizeof(t_token));
	token->str = ft_strdup(str);
	token->lexer_flag = lexer_flag;
	return (token);
}

void	init_all(char **env)
{
	g_data.stdin_fd = dup(STDIN_FILENO);
	g_data.stdout_fd = dup(STDOUT_FILENO);
	g_data.exit_status = 0;
	g_data.buffer_list = NULL;
	g_data.pid = 0;
	g_data.history = deque_init();
	deque_push_back(g_data.history, "You have no history before this.");
	g_data.clip_board = NULL;
	if (tgetent(NULL, getenv("TERM")) != 1)
	{
		g_data.term_width = -1;
		g_data.term_height = -1;
	}
	else
	{
		g_data.term_height = tgetnum("li");
		g_data.term_width = tgetnum("co");
	}
	init_env(env);
}

static int	count_shlvl(char *str)
{
	long long	num[2]; // 18 digits max 999,999,999,999,999,999
	int			cnt[2];

	if (!str)
		return (1);
	while (ft_isspace(*str))
		++str;
	num[1] = 1LL;
	if (*str == '-')
		num[1] = -1LL;
	if (*str == '+' || *str == '-')
		++str;
	cnt[0] = -1;
	while (str[++cnt[0]])
		if (!ft_isdigit(str[cnt[0]]))
			return (1);
	num[0] = 0LL;
	cnt[0] = -1;
	while (str[++cnt[0]])
	{
		if (num[0] > 922337203685477580LL)
			return (1);
		num[0] = num[0] * 10LL + (long long)(str[cnt[0]] - '0');
	}
	cnt[1] = (int)(num[0] * num[1] + 1LL);
	if (cnt[1] < 0)
		return (0);
	if (cnt[1] > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(cnt[1], 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		return (1);
	}
	return (cnt[1]);
}

static void	modify_shlvl()
{
	char		*str[2];
	char		*args[3];

	str[0] = find_env_var("SHLVL");
	args[0] = "export";
	args[2] = 0;
	str[1] = ft_itoa(count_shlvl(str[0]));
	ft_free(str[0]);
	args[1] = ft_calloc(20, sizeof(char));
	ft_strcat(args[1], "SHLVL=");
	ft_strcat(args[1], str[1]);
	ft_free(str[1]);
	builtin_export(args);
	ft_free(args[1]);
}

/*
** bigger than int : problem : 2147483648->0, 99999999999999999999999999999999999->1
** export SHLVL=9999999999     1410065408
**
** from limit to max_int : 
**
** from 0 to limit : 
**
** negative number -> 0 (but -999999999999999999999 -> 1)
**
** number mix with others : -> 1
**
** non-numerics : -> 1
**
** non-existant : -> 1 
*/


void	init_env(char **env)
{
	int		idx[2];

	g_data.env_list = deque_init();
	idx[0] = -1;
	while (env[++idx[0]])
		deque_push_back(g_data.env_list, env[idx[0]]);
	modify_shlvl();
}
