/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:25:59 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 16:36:32 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_document(char *eof)
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
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
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
				message_exit(0, "", -1);
		}
		if (ft_strncmp(line, eof, len) != 0)
		{
			ft_putstr_fd(line, pipefd[1]);
			ft_putstr_fd("minishell: warning: here-document delimited", 2);
			ft_putstr_fd(" by end-of-file (wanted `", 2);
			ft_putstr_fd(eof, 2);
			ft_putendl_fd("\')", 2);
		}
		message_exit(0, "", -1);
	}
}

static void	check_fd(int fd, char *file_name)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file_name);
		message_exit(1, "", -1);
	}
}

static void	set_redir(char *redir, char *file_name)
{
	int	fd;

	if (ft_strncmp(redir, "<<", 3) == 0)
		here_document(file_name);
	else if (ft_strncmp(redir, "<", 2) == 0)
	{
		fd = open(file_name, O_RDONLY);
		check_fd(fd, file_name);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (ft_strncmp(redir, ">", 2) == 0)
	{
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		check_fd(fd, file_name);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0664);
		check_fd(fd, file_name);
		dup2(fd, STDOUT_FILENO);
		close(fd);
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
		if (is_redir(cmd->head->content))
		{
			set_redir(cmd->head->content, cmd->head->next->content);
			deque_pop_front(cmd, NULL);
		}
		else
			args[cnt++] = cmd->head->content;
		deque_pop_front(cmd, NULL);
	}
	execute(args);
}
