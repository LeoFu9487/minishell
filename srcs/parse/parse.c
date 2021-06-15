/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:15:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 21:36:48 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if > < end : unexpected  near 'newline'

/*
** parse step :
** 1. seperate by ; or EOL (if no arguments before ; then parse error)
** 2. seperate by pipes (if no arguments before or after then parse error)
** 3. separated by >(>>) and <(<<), (if nothing after then parse error)
*/

void	parse_and_execute(t_deque *tokens)
{
	if (check_parse(tokens))
		return ;
	if (g_data.lexer_error != NoError)
	{
		print_unexpected_eol_message();
		return ;
	}
	create_cmd(tokens);
	g_data.pid = 0;
}
