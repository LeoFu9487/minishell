/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yfu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:44 by yfu               #+#    #+#             */
/*   Updated: 2021/06/11 12:28:57 by yfu              ###   ########lyon.fr   */
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
	UP = 9487,
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
/*____ok_____*/

typedef enum e_lexer_key
{
	others = 0,
	back_slash,
	dollar
}t_lexer_key;

typedef enum e_lexer_key_2
{
	NoError = 0,
	quote,
	dquote
}t_lexer_key_2;

typedef enum e_end_of_command
{
	NewLine = 0,
	Semicolon,
	Pipe
}t_end_of_command;

typedef struct s_lexer
{
	int			quote;
	int			dquote;
	t_lexer_key	last_key;
}t_lexer;

typedef struct s_iofd
{
	int		stdin_fd;
	int		stdout_fd;
	char	*in_file;
	char	*out_file;
}t_iofd;

void		raw_mode_switch(t_switch e);
char		*buffer_to_string(void);
unsigned	get_key();
void		print_the_rest_of_buffer();
void		handle_up(void);
void		handle_down(void);
void		insert_in_buffer(char c);
void		handle_backspace(void);
void		handle_left(void);
void		handle_right(void);
void		handle_home(void);
void		handle_end(void);
void		handle_delete(void);
void		handle_ctrl_d(void);
int			check_parse_error(t_deque *tokens);
void		create_cmd(t_deque *tokens);
int			is_redir(char *str);
void		run_command(t_deque *cmd);
void		execute(char **args);
void		set_redir(char *redir, char *file_name, t_iofd *iofd);
void		no_pipe_command(t_deque *cmd, t_iofd *iofd);
void		launch_bin(char **args);

/*____todo____*/
void		init_env(char **env);//todo
char		*get_input(void);//todo
t_deque		*lexer(char *input_string);//todo
void		parse_and_execute(t_deque *tokens);//todo
void		main_loop(void);//todo
void		init_all(char **env);//todo
void		handle_ctrl_a(void);//todo
void		handle_ctrl_b(void);//todo
void		handle_ctrl_l(void);//todo
void		handle_ctrl_v(void);//todo
void		handle_ctrl_up(void);//todo
void		handle_ctrl_down(void);//todo
void		handle_ctrl_left(void);//todo
void		handle_ctrl_right(void);//todo
void		handle_alt_a(void);//todo
void		handle_alt_b(void);//todo
void		handle_alt_l(void);//todo

/*
** todo : 
** 1. exit code
** 2. ctrl-C, ctrl-D, ctrl-\
** 3. exit_status
*/

#endif
