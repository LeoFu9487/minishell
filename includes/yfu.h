/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yfu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:44 by yfu               #+#    #+#             */
/*   Updated: 2021/06/05 00:14:10 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFU_H
# define YFU_H
# define CTRL_A 1
# define CTRL_B 2
# define CTRL_D 4
# define CTRL_L 12
# define CTRL_V 22
# define BACKSPACE 127

typedef enum e_keys
{
	UP=9487,
	DOWN,
	LEFT,
	RIGHT,
	CTRL_UP,
	CTRL_DOWN,
	CTRL_LEFT,
	CTRL_RIGHT,
	HOME,
	END,
	ALT_A,
	ALT_B,
	ALT_L,
	DELETE,
	NOT_DEFINED
}t_keys;

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

void		raw_mode_switch(t_switch e);//ok

void		init_env(char **env);//todo
char		*get_input(void);//todo
t_deque		*lexer(char *input_string);//todo
void		parse_and_execute(t_deque *tokens);//todo
void		main_loop(void);//todo
void		init_all(char **env);//todo
void		handle_ctrl_a(void);//todo
void		handle_ctrl_b(void);//todo
void		handle_ctrl_d(void);//todo
void		handle_ctrl_l(void);//todo
void		handle_ctrl_v(void);//todo
void		handle_up(void);//todo
void		handle_down(void);//todo
void		handle_left(void);//todo
void		handle_right(void);//todo
void		handle_ctrl_up(void);//todo
void		handle_ctrl_down(void);//todo
void		handle_ctrl_left(void);//todo
void		handle_ctrl_right(void);//todo
unsigned	get_key();

#endif