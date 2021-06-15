/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:08:09 by yfu               #+#    #+#             */
/*   Updated: 2021/06/15 15:21:09 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_pipe_builtin(t_deque *cmd) // need to redir ?
{
	if (cmd->size > 0 && ft_strncmp(((t_token *)cmd->head->content)->str,
			"exit", 5) == 0)
	{
		no_pipe_exit(cmd);
		return (1);
	}
	if (cmd->size > 0 && ft_strncmp(((t_token *)cmd->head->content)->str,
			"cd", 3) == 0)
	{
		no_pipe_cd(cmd);
		return (1);
	}
	if (cmd->size > 0 && ft_strncmp(((t_token *)cmd->head->content)->str,
			"export", 7) == 0)
	{
		no_pipe_export(cmd);
		return (1);
	}
	if (cmd->size > 0 && ft_strncmp(((t_token *)cmd->head->content)->str,
			"unset", 6) == 0)
	{
		no_pipe_unset(cmd);
		return (1);
	}
	return (0);
}

void	no_pipe_exit(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	builtin_exit(args);
	ft_free(args);
}

void	no_pipe_cd(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	//builtin_cd(args);
	ft_free(args);
}

void	no_pipe_export(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	//builtin_export(args);
	ft_free(args);
}

void	no_pipe_unset(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = ((t_token *)cmd->head->content)->str;
		deque_pop_front(cmd, NULL);
	}
	//builtin_unset(args);
	ft_free(args);	
}
