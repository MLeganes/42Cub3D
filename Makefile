NAME		=	cub3D
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

S			=	src/
O			=	obj/

OBJS		=	$(patsubst $S%.c, $O%.o, $(SRCS))
SRCS		=	$Scub3D.c

LIBRARIES	=	-Llibft -lft -Llibmlx -lmlx -framework OpenGL -framework AppKit
INCLUDES	=	-I ./inc -Ilibft -Ilibmlx


all:		$(NAME)

# Linking...
$(NAME):	libft/libft.a libmlx/libmlx.a $(OBJS)
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m linking...\033[0m"
			@$(CC) $(OBJS) $(LIBRARIES) -o $(NAME)
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

# Compiling...
$O%.o:		$S%.c
			@[ -d $(O) ]	 || mkdir -p $(O)
			@echo "\033[1;32m$(NAME)\033[1;0m\033[32m compiling...\033[0m"
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
			@rm -rf $(O)
			@make -C libmlx clean
			@make -C libft clean
			@echo "\033[31mObjects Files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31mremoved.\033[0m"

fclean:		clean
			@make -C libft fclean
			@rm -f $(NAME)
			@rm -f $(NAME_LK)
			@echo "\033[1;31m$(NAME)\033[1;0m\033[31m Removed.\033[0m"

re: 		fclean $(NAME)

libft/libft.a:
			@make -C libft all

libmlx/libmlx.a:
			@make -C libmlx all

.PHONY: all clean fclean re