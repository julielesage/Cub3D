# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlesage <jlesage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/11 16:03:42 by jlesage           #+#    #+#              #
#    Updated: 2021/02/02 22:51:58 by jlesage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER = cub3d.h

CC = clang

CFLAGS = -O3 -Wall -Wextra -Werror -g
LIBS = $(MLX_LNK) -lm

SRCS = src/cub3d.c \
		src/checks/argvcheck.c \
		src/checks/parse_map.c\
		src/checks/check_map.c \
		src/checks/sprite_and_lastchecks.c\
		src/libft/basics.c \
		src/libft/basics_bis.c\
		src/libft/get_next_line.c \
		src/utils/errors.c \
		src/textures/bitmap.c \
		src/textures/xpm.c \
		src/textures/colors.c \
		src/textures/sprite.c \
		src/raycasting/screen.c \
		src/raycasting/raycasting.c \
		src/game/movements.c \

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR	= minilibx_linux
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lm -lXext -lX11 -lbsd
	SRCS	+=	src/linuxVsMac/linux.c \

else
	MLX_DIR	= minilibx_opengl
	MLX_LNK	= -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	SRCS	+=	src/linuxVsMac/mac.c \

endif

OBJS = $(SRCS:.c=.o)

all: $(NAME)

mlx: $(MLX-DIR)
	@echo "\033[34m-= Making libX.a... =-"
	@make 2>/dev/null -C $(MLX_DIR)

$(NAME): $(SRCS) $(OBJS) mlx
	@echo "\n\033[0;33mCompiling..."
	${CC} ${CFLAGS} ${OBJS} ${MLX_LNK} -o ${NAME}
	@echo "\033[32m   ______      __   _____ ____  "
	@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
	@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
	@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
	@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./cub3D <map.cub> [--save]"

bmp: re
	./$(NAME) maps/square.cub --save

clean:
	@echo "\033[0;31mCleaning..."
	rm -f $(OBJS)
	rm -f cub3Dimage.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[34m-= Cleaning mlx... =-"
	@make clean -C $(MLX_DIR)
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	rm -f *.o
	rm -f cub3Dimage.bmp
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re norm
