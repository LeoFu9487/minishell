/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:34:03 by yfu               #+#    #+#             */
/*   Updated: 2021/06/17 13:29:41 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_lexer_flag lexer_flag)
{
	if (lexer_flag == _redir_in || lexer_flag == _redir_in_d
		|| lexer_flag == _redir_out || lexer_flag == _redir_out_d)
		return (1);
	return (0);
}
