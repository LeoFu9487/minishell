/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:23:15 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 20:01:51 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_unexpected_eof_message(char *line, int pipefd[2], char *eof)
{
	ft_putstr_fd(line, pipefd[1]);
	ft_putstr_fd("minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putendl_fd("\')", 2);
}

void	print_unexpected_eol_message(void)
{
	g_data.exit_status = 2;
	if (g_data.lexer_error == right_parenthese)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `)\'", 2);
		return ;
	}
	ft_putstr_fd("minishell: unexpected EOL while looking for matching `",
		2);
	if (g_data.lexer_error == left_parenthese)
		ft_putendl_fd("(\'", 2);
	else if (g_data.lexer_error == dquote)
		ft_putendl_fd("\"\'", 2);
	else if (g_data.lexer_error == quote)
		ft_putendl_fd("\'\'", 2);
	else if (g_data.lexer_error == backslash)
		ft_putendl_fd("\\\'", 2);
}
