NAME = minishell

LIBSH = libmsh.a

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

CC = gcc

UTILS_FILE = exit.c	init.c	signal.c	find_env_var.c\
prompt.c	is_redir.c

UTILS_PATH = utils/

TERMCAP_FILE = termcap.c	handle_ctrl.c	handle_arrow.c	handle_ctrl_arrow.c\
	get_key.c	handle_alt.c	handle_others.c	display_terminal.c

TERMCAP_PATH = termcap/

PARSE_FILE = get_input.c	lexer.c	parse.c	parse_error.c\
	create_cmd.c

PARSE_PATH = parse/

BULDIN_FILE = echo.c	env.c

BUILDIN_PATH = buildin/

EXECUTE_FILE = run_command.c	no_pipe_command.c	execute.c

EXECUTE_PATH = execute/

#PUT FILES HERE
SRCS_FILE += $(addprefix $(UTILS_PATH), $(UTILS_FILE))

SRCS_FILE += $(addprefix $(TERMCAP_PATH), $(TERMCAP_FILE))

SRCS_FILE += $(addprefix $(PARSE_PATH), $(PARSE_FILE))

SRCS_FILE += main_loop.c

SRCS_FILE += $(addprefix $(BUILDIN_PATH), $(BULDIN_FILE))

SRCS_FILE += $(addprefix $(EXECUTE_PATH), $(EXECUTE_FILE))

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.c=.o)

MAIN = srcs/main.c

LIBFT = libft/libft.a

LIBFLAGS = -L. -lmsh -L ./libft -lft -lncurses

#PUT HEADERS HERE
HEADER_FILE = minishell.h	xli.h yfu.h

HEADER_PATH = includes/

HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

all : $(NAME)
	echo "Compile OK"

$(NAME) : $(LIBSH) $(MAIN)
	$(CC) $(CFLAGS) -I $(HEADER_PATH)  $(MAIN) $(LIBFLAGS) -o $(NAME)

$(LIBSH) : $(HEADER) $(LIBFT) $(OBJS)
	ar rcs $(LIBSH) $(OBJS)
	ranlib $(LIBSH)
	echo "msh.a OK"

$(LIBFT) :
	$(MAKE) -C ./libft/

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

test : $(LIBSH)

bonus : $(NAME)
	echo "Compile Bonus OK"

clean :
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libft/
	echo "clean OK"

fclean :
	rm -rf $(OBJS) $(NAME) $(LIBSH)
	$(MAKE) fclean -C ./libft/
	echo "fclean OK"

re : fclean all

.PHONY: all clean fclean re bonus test

#.SILENT :
