/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:23:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 21:48:18 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_unexpected_eof_message(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putendl_fd("\')", 2);
}

void	print_unexpected_eol_message(void)
{
	g_data.exit_status = 2;
	ft_putstr_fd("minishell: unexpected EOL while looking for matching `",
		2);
	if (g_data.lexer_error == dquote)
		ft_putendl_fd("\"\'", 2);
	else if (g_data.lexer_error == quote)
		ft_putendl_fd("\'\'", 2);
	else if (g_data.lexer_error == backslash)
		ft_putendl_fd("\\\'", 2);
}

static void	print_stdin_fd_error(t_iofd *iofd)
{
	ft_putstr_fd(iofd->in_file, 2);
	ft_putstr_fd(": ", 2);
	if (!file_exists(iofd->in_file))
		ft_putendl_fd("No such file or directory", 2);
	else if (is_dir(iofd->in_file))
		ft_putendl_fd("Is a redirectory", 2);
	else
		ft_putendl_fd("Permission denied", 2);
}

static void	print_stdout_fd_error(t_iofd *iofd)
{
	ft_putstr_fd(iofd->out_file, 2);
	ft_putstr_fd(": ", 2);
	if (!file_exists(iofd->out_file))
		ft_putendl_fd("No such file or directory", 2);
	else if (is_dir(iofd->out_file))
		ft_putendl_fd("Is a redirectory", 2);
	else
		ft_putendl_fd("Permission denied", 2);
}

void	print_fd_error(t_iofd *iofd)
{
	ft_putstr_fd("minishell: ", 2);
	if (iofd->stdin_fd < 0)
		print_stdin_fd_error(iofd);
	else
		print_stdout_fd_error(iofd);
}
