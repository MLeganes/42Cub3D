NAME	= so_long
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
OBJS	= $(patsubst %.c, %.o, $(SRCS))
SRCS	= 

%.o: %.c
	$(CC) $(FLAGS) -Ilibmlx -Ilibft -D -c $< -o $@

all: $(NAME)

$(NAME): libft/libft.a libmlx/libmlx.a $(OBJS)
	$(CC) -Llibmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

clean:
	rm -f *.o
	rm -f *.out
	make -C libmlx clean
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f $(NAME_LK)

re: fclean $(NAME)

libft/libft.a:
	make -C libft all

libmlx/libmlx.a:
	make -C libmlx all