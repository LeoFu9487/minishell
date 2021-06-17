/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:14:19 by yfu               #+#    #+#             */
/*   Updated: 2021/06/17 13:15:22 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redir_in(char *file_name, t_iofd *iofd)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (iofd->stdin_fd != STDIN_FILENO)
		close(iofd->stdin_fd);
	iofd->stdin_fd = fd;
	ft_free(iofd->in_file);
	iofd->in_file = ft_strdup(file_name);
}

void	set_redir(char *redir, char *file_name, t_iofd *iofd)
{
	int	fd;

	if (iofd->stdin_fd < 0 || iofd->stdout_fd < 0)
		return ;
	if (ft_strncmp(redir, "<<", 3) == 0)
	{
		if (iofd->stdin_fd != STDIN_FILENO)
			close(iofd->stdin_fd);
		iofd->stdin_fd = *((int *)g_data.heredoc_fd->head->content);
		deque_pop_front(g_data.heredoc_fd, ft_free);
		ft_free(iofd->in_file);
		iofd->in_file = ft_strdup("heredoc");
	}
	else if (ft_strncmp(redir, "<", 2) == 0)
		set_redir_in(file_name, iofd);
	else
	{
		if (ft_strncmp(redir, ">", 2) == 0)
			fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (iofd->stdout_fd != STDOUT_FILENO)
			close(iofd->stdout_fd);
		iofd->stdout_fd = fd;
		ft_free(iofd->out_file);
		iofd->out_file = ft_strdup(file_name);
	}
}
