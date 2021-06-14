/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:23 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 14:22:17 by xli              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLI_H
# define XLI_H

int		var_key_len(char *var);
int		check_var_name(char *var);
void	sort_env(t_deque **unsorted_env);
int		is_new_var(char *var);
void	update_var(char *var);
void	builtin_echo(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_unset(char **args);

#endif
