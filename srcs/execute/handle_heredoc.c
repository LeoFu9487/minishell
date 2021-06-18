/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:30:24 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 22:02:26 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_document_child_process(char *eof, int *pipefd)
{
	int		len;
	char	*line;

	close(pipefd[0]);
	len = ft_strlen(eof) + 1;
	heredoc_ctrl_d(eof, pipefd[1]);
	raw_mode_switch(nocolor_on);
	ft_putstr_fd("> ", 2);
	line = get_input();
	while (line)
	{
		if (strncmp(line, eof, len) != 0)
		{
			ft_putstr_fd("> ", 2);
			ft_putendl_fd(line, pipefd[1]);
			ft_free(line);
		}
		else
		{
			close(pipefd[1]);
			ft_free(line);
			message_exit(0, "", -1);
		}
		line = get_input();
	}
}

static void	clear_heredoc_fd(void)
{
	while (g_data.heredoc_fd->size > 0)
	{
		close(*((int *)g_data.heredoc_fd->head->content));
		deque_pop_front(g_data.heredoc_fd, ft_free);
	}
}

static int	here_document_parent_process(int pipefd[2])
{
	int	status;
	int	*fd;

	close(pipefd[1]);
	waitpid(g_data.pid, &status, 0);
	g_data.heredoc_process = 0;
	if (WIFEXITED(status) && WEXITSTATUS(status) == GET_KILLED)
	{
		close(pipefd[0]);
		clear_heredoc_fd();
		g_data.exit_status = 1;
		ft_putendl_fd("", 2);
		return (0);
	}
	fd = ft_malloc(1, sizeof(int));
	*fd = pipefd[0];
	deque_push_back(g_data.heredoc_fd, fd);
	return (1);
}

int	here_document(char *eof)
{
	int		pipefd[2];

	pipe(pipefd);
	g_data.pid = fork();
	g_data.heredoc_process = 1;
	if (g_data.pid)
		return (here_document_parent_process(pipefd));
	else
		here_document_child_process(eof, pipefd);
	return (0);
}

int	handle_heredoc(t_deque *tokens)
{
	t_double_list	*iterator[2];

	deque_clear(g_data.heredoc_fd, ft_free);
	g_data.heredoc_fd = deque_init();
	g_data.heredoc_process = 0;
	iterator[0] = tokens->head;
	while (iterator[0])
	{
		if (((t_token *)iterator[0]->content)->lexer_flag == _redir_in_d)
		{
			iterator[0] = iterator[0]->next;
			if (here_document(((t_token *)iterator[0]->content)->str) == 0)
				return (0);
		}
		iterator[0] = iterator[0]->next;
	}
	return (1);
}
