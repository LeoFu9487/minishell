/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:23 by yfu               #+#    #+#             */
/*   Updated: 2021/06/09 14:31:04 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLI_H
# define XLI_H

typedef struct	s_env
{
	char	*name;
	char	*value;
}				t_env;

void	builtin_echo(char **args);
void	builtin_env(char **args);
void	builtin_export(char **args);

#endif
