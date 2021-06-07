/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/07 08:19:27 by yfu              ###   ########lyon.fr   */
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
	int				exit_status;
	t_deque			*env_list;
	t_deque			*history;
	t_deque			*buffer_list;
	char			*clip_board;
	t_double_list	*cursor;
	t_double_list	*history_iterator;
}g_data;

/*
** builtin
** simulates execve (args[0] will be ignored)
*/

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

char	*find_env_var_line(char *key);//return the whole line, don't free after calling this function
char	*find_env_var(char *key);//return the value that corresponds to the key, ft_free after the use of this function
/*
** return NULL if not foudn (for both of them)
**
** example : 
** char *str = find_env_var_line("SHLVL");
** ft_putendl_fd(str, 1); //output : SHLVL=2
** 
** char *str2 = find_env_var("SHLVL");
** ft_putendl_fd(str2, 1); // output : 2
** ft_free(str2); // need to free after used
*/

#endif
