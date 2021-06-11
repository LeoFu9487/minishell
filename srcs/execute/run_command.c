/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:25:59 by yfu               #+#    #+#             */
/*   Updated: 2021/06/11 12:52:48 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_document(char *eof, t_iofd *iofd) // change here for return fd
{
	pid_t	pid;
	char	*line;
	int		pipefd[2];
	int		len;
	
	pipe(pipefd);
	pid = fork();
	if (pid) // parent process
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
	else // child process
	{
		close(pipefd[0]);
		len = ft_strlen(eof) + 1;
		ft_putstr_fd("> ", 2);
		while (get_next_line(g_data.stdin_fd, &line) > 0)
		{
			//problem : put into history
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
		{
			ft_putstr_fd(line, pipefd[1]);
			ft_putstr_fd("minishell: warning: here-document delimited", 2);
			ft_putstr_fd(" by end-of-file (wanted `", 2);
			ft_putstr_fd(eof, 2);
			ft_putendl_fd("\')", 2);
		}
		close(pipefd[1]);
		message_exit(0, "", -1);
	}
}

void	set_redir(char *redir, char *file_name, t_iofd *iofd) // change here for return fd
{
	int	fd;

	if (ft_strncmp(redir, "<<", 3) == 0)
		here_document(file_name, iofd);
	if (iofd->stdin_fd < 0 || iofd->stdout_fd < 0)
		return ;
	if (ft_strncmp(redir, "<", 2) == 0)
	{
		fd = open(file_name, O_RDONLY);
		if (iofd->stdin_fd != STDIN_FILENO)
			close(iofd->stdin_fd);
		iofd->stdin_fd = fd;
		ft_free(iofd->in_file);
		iofd->in_file = ft_strdup(file_name);
	}
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

void	run_command(t_deque *cmd)
{
	char	**args;
	int		cnt;

	args = ft_calloc(cmd->size + 1, sizeof(char *));
	cnt = 0;
	while (cmd->size > 0)
	{
		args[cnt++] = cmd->head->content;
		deque_pop_front(cmd, NULL);
	}
	execute(args);
}
