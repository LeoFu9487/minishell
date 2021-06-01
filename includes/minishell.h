/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/01 13:53:12 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "xli.h"
# include "yfu.h"

/*
** builtin
*/

void	builtin_echo(char **args, t_deque *env);
void	builtin_cd(char **args, t_deque *env);
void	builtin_pwd(char **args, t_deque *env);
void	builtin_export(char **args, t_deque *env);
void	builtin_unset(char **args, t_deque *env);
void	builtin_env(char **args, t_deque *env);
void	builtin_exit(char **args, t_deque *env);

#endif