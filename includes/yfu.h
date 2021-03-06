/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yfu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xli <xli@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:52:44 by yfu               #+#    #+#             */
/*   Updated: 2021/06/22 17:19:29 by xli              ###   ########lyon.fr   */
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
# define GET_KILLED 87

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
	nocolor_on,
	off
}t_switch;

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
	dquote,
	backslash
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

typedef enum e_lexer_flag
{
	_undefined,
	_semicolon,
	_redir_in,
	_redir_in_d,
	_redir_out,
	_redir_out_d,
	_pipe
}t_lexer_flag;

typedef struct s_token
{
	char			*str;
	t_lexer_flag	lexer_flag;
}t_token;

void			raw_mode_switch(t_switch e);
char			*buffer_to_string(void);
unsigned int	get_key(void);
void			print_the_rest_of_buffer(void);
void			handle_up(void);
void			handle_down(void);
void			insert_in_buffer(char c);
void			handle_backspace(void);
void			handle_left(void);
void			handle_right(void);
void			handle_home(void);
void			handle_end(void);
void			handle_delete(void);
void			handle_ctrl_d(void);
void			handle_ctrl_l(void);
int				check_parse(t_deque *tokens);
int				check_parse_semicolon(t_deque *tokens);
int				check_parse_pipe(t_deque *tokens, t_end_of_command eoc);
int				check_parse_redir(t_deque *tokens, t_end_of_command eoc);
void			create_cmd(t_deque *tokens);
int				is_redir(t_lexer_flag lexer_flag);
void			run_command(t_deque *cmd);
void			execute(char **args);
void			set_redir(char *redir, char *file_name, t_iofd *iofd);
void			no_pipe_command(t_deque *cmd, t_iofd *iofd);
void			launch_bin(char **args);
t_token			*init_token(char *str, t_lexer_flag lexer_flag); //deep copy
void			free_token(void *token);
void			print_unexpected_eof_message(char *eof);
void			print_unexpected_eol_message(void);
void			create_pipe(t_deque *cmd_list);
void			ft_free_iofd(t_iofd *iofd, int size);
t_iofd			*init_iofd(int size);
void			close_pipefd(int size, int **pipefd);
void			create_pipe_child(t_deque *cmd_list, int size,
					int **pipefd, t_iofd *iofd);
void			init_env(char **env);
char			*get_input(void);
t_deque			*lexer(char *input_string);
void			parse_and_execute(t_deque *tokens);
void			main_loop(void);
void			init_all(char **env);
void			put_buffer_in_tokens(t_deque *tokens,
					t_deque *token_buffer, t_lexer_flag lexer_flag);
void			lexer_back_slash(t_deque *token_buffer);
void			lexer_dollar(t_deque *token_buffer);
void			lexer_dquote(t_deque *token_buffer);
void			lexer_general(t_deque *token_buffer, char *str, int *idx);
void			lexer_pipe(t_deque *tokens, t_deque *token_buffer);
void			lexer_quote(t_deque *token_buffer);
void			lexer_redir_in(t_deque *tokens, t_deque *token_buffer,
					char *str, int *idx);
void			lexer_redir_out(t_deque *tokens, t_deque *token_buffer,
					char *str, int *idx);
void			lexer_semicolon(t_deque *tokens, t_deque *token_buffer);
void			lexer_space(t_deque *tokens, t_deque *token_buffer,
					char input_char);
void			lexer_wildcard(t_deque *token_buffer);
int				no_pipe_builtin(t_deque *cmd);
void			no_pipe_exit(t_deque *cmd);
void			no_pipe_cd(t_deque *cmd);
void			no_pipe_export(t_deque *cmd);
void			no_pipe_unset(t_deque *cmd);
int				set_color(char *input_string);
void			wild_card(t_deque *tokens, char *pattern);
int				has_wild_card(char *str);
int				match(char *pattern, char *str, char *star, char *sptr);
void			sort_string(t_deque *deque);
int				here_document(char *eof);
int				handle_heredoc(t_deque *tokens);
void			lexer_tilde(t_deque *token_buffer, char *input_string,
					int *idx);
char			*get_home(void);
void			print_fd_error(t_iofd *iofd);
int				file_exists(const char *filename);
void			here_document_child_process(char *eof, int *pipefd);
void			heredoc_ctrl_d(char *eof, int pipefd);
int				integrate_forks_for_pipe(int size, pid_t *pid);
t_deque			*get_files_not_dot(char *path);
t_deque			*get_files_start_from_dot(char *path);
void			wild_card_recursive(char *path, char *pattern, int *is_matched,
					t_deque *tokens);
int				str_is_space(char *str);

/*____todo____*/
void			handle_ctrl_a(void);
void			handle_ctrl_b(void);
void			handle_ctrl_v(void);
void			handle_ctrl_up(void);
void			handle_ctrl_down(void);
void			handle_ctrl_left(void);
void			handle_ctrl_right(void);
void			handle_alt_a(void);
void			handle_alt_b(void);
void			handle_alt_l(void);

#endif
