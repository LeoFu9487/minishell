/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:23 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 11:46:05 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLI_H
# define XLI_H

void	builtin_echo(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_export(char **args);
void	builtin_pwd(char **args);

#endif
