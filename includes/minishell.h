/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/14 11:45:59 by xli              ###   ########lyon.fr   */
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
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define NOCOLOR "\x1B[0m"

struct s_data
{
	t_lexer_key_2	lexer_error;
	int				exit_status;
	pid_t			pid;
	t_deque			*env_list;
	t_deque			*history;
	t_deque			*buffer_list;
	char			*clip_board;
	t_double_list	*cursor;
	t_double_list	*history_iterator;
	t_lexer			*lexer;
	int				stdin_fd;
	int				stdout_fd;
	int				term_width;
	int				term_height;
}g_data;

/*
** builtin
** simulates execve (args[0] will be ignored)
*/

void	builtin_cd(char **args);//todo
void	builtin_pwd(char **args);//todo
void	builtin_unset(char **args);//todo

/*
** utils :
** message_exit(int exit_code, char *message, int fd)
** : free everything, put message in fd and exit(exit_code)
*/

void	message_exit(int exit_code, char *message, int fd);
void	catch_signal(void);//todo
void	print_prompt(void);
int		is_dir(const char *path);

t_double_list	*find_env_var_line(char *key);//return the whole line, don't free after calling this function
char			*find_env_var(char *key);//return the value that corresponds to the key, ft_free after the use of this function
/*
** return NULL if not found (for both of them)
**
** example :
** char *str = find_env_var_line("SHLVL")->content;
** ft_putendl_fd(str, 1); //output : SHLVL=2
**
** char *str2 = find_env_var("SHLVL");
** ft_putendl_fd(str2, 1); // output : 2
** ft_free(str2); // need to free after used
*/

#endif
