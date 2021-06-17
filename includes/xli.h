/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:23 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 12:06:10 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLI_H
# define XLI_H

/*
** builtin
** simulates execve (args[0] will be ignored)
*/

int		var_key_len(char *var);
int		check_var_name(char *var);
void	sort_env(t_deque **unsorted_env);
int		is_new_var(char *var);
void	update_var(char *var);
void	builtin_echo(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_unset(char **args);
void	builtin_pwd(char **args);
void	builtin_export(char **args);
void	builtin_export(char **args);
void	builtin_pwd(char **args);
void	builtin_cd(char **args);

#endif
