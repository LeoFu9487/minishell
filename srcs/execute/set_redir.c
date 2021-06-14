/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:14:19 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 19:30:40 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_unexpected_eof_message(char *line, int pipefd[2], char *eof)
{
	ft_putstr_fd(line, pipefd[1]);
	ft_putstr_fd("minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putendl_fd("\')", 2);
}

static void	here_document_child_process(char *eof, int pipefd[2])
{
	int		len;
	char	*line;

	close(pipefd[0]);
	len = ft_strlen(eof) + 1;
	ft_putstr_fd("> ", 2);
	while (get_next_line(g_data.stdin_fd, &line) > 0)
	{
		if (ft_strncmp(line, eof, len) != 0)
		{
			ft_putstr_fd("> ", 2);
			ft_putendl_fd(line, pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			message_exit(0, "", -1);
		}
	}
	if (ft_strncmp(line, eof, len) != 0)
		print_unexpected_eof_message(line, pipefd, eof);
	close(pipefd[1]);
	message_exit(0, "", -1);
}

static void	here_document(char *eof, t_iofd *iofd)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		if (iofd->stdin_fd < 0 || iofd->stdout_fd < 0)
			return ;
		if (iofd->stdin_fd != STDIN_FILENO)
			close(iofd->stdin_fd);
		iofd->stdin_fd = pipefd[0];
		ft_free(iofd->in_file);
		iofd->in_file = ft_strdup("heredoc");
	}
	else
		here_document_child_process(eof, pipefd);
}

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

	if (ft_strncmp(redir, "<<", 3) == 0)
	{
		here_document(file_name, iofd);
		return ;
	}
	if (iofd->stdin_fd < 0 || iofd->stdout_fd < 0)
		return ;
	if (ft_strncmp(redir, "<", 2) == 0)
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
