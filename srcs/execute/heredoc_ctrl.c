/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 21:46:44 by yfu               #+#    #+#             */
/*   Updated: 2021/06/18 21:51:29 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_ctrl_d(char *eof, int pipefd)
{
	static char	*real_eof;
	static int	real_pipefd;

	if (eof == NULL)
	{
		print_unexpected_eof_message(real_eof);
		close(real_pipefd);
		message_exit(0, "", -1);
	}
	real_eof = eof;
	real_pipefd = pipefd;
}
