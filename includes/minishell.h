/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/03 02:48:05 by yfu              ###   ########lyon.fr   */
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
# define PROMPT_MESSAGE "minishell $> "

struct s_data
{
	t_deque	*env_list;
	t_deque	*history;
	int		exit_status;
	int		empty_buffer;
}g_data;

/*
** builtin
** simulates execve (args[0] will be ignored)
*/

void	builtin_echo(char **args);//todo
void	builtin_cd(char **args);//todo
void	builtin_pwd(char **args);//todo
void	builtin_export(char **args);//todo
void	builtin_unset(char **args);//todo
void	builtin_env(char **args);//todo
void	builtin_exit(char **args);//todo

/*
** utils :
** message_exit(int exit_code, char *message, int fd)
** : free everything, put message in fd and exit(exit_code)
*/

void	message_exit(int exit_code, char *message, int fd);
void	catch_signal(void);//todo

#endif