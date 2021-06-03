/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yfu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:44 by yfu               #+#    #+#             */
/*   Updated: 2021/06/03 02:53:11 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFU_H
# define YFU_H

typedef struct s_termcap
{
	struct termios	original;
	struct termios	raw;
}t_termcap;

typedef enum e_switch
{
	on = 0,
	off
}t_switch;

void	raw_mode_switch(t_switch e);
void	init_env(char **env);
char	*get_input(void);
t_deque	*lexer(char *input_string);
void	parse_and_execute(t_deque *tokens);

#endif