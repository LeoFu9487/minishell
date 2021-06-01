NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

CC = gcc

UTILS_FILE = exit.c	init.c	signal.c

UTILS_PATH = utils/

TERMCAP_FILE = termcap.c

TERMCAP_PATH = termcap/

#PUT FILES HERE
SRCS_FILE += $(addprefix $(UTILS_PATH), $(UTILS_FILE))

SRCS_FILE += $(addprefix $(TERMCAP_PATH), $(TERMCAP_FILE))

SRCS_FILE += main.c

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

LIBFLAGS = -L ./libft -lft -lncurses

#PUT HEADERS HERE
HEADER_FILE = minishell.h	xli.h yfu.h

HEADER_PATH = includes/

HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

all : $(NAME)
	echo "Compile OK"

$(NAME) : $(HEADER) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) $(OBJS) $(LIBFLAGS) -o $(NAME)

$(LIBFT) : 
	$(MAKE) -C ./libft/

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

bonus : $(NAME)
	echo "Compile Bonus OK"

clean : 
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libft/
	echo "clean OK"

fclean :
	rm -rf $(OBJS) $(NAME)
	$(MAKE) fclean -C ./libft/
	echo "fclean OK"

re : fclean all

.PHONY: all clean fclean re bonus

#.SILENT : 
