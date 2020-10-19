NAME = Cub3D

HEADER = cub3d.h

CC = clang
#BONUS OR NOT
#ifeq ($(DB),1)
#    CFLAGS	= -O3 -g3 -Wall -Wextra -Werror
#	LIBS	= -L libft/ -lft ${MLX_LNK} -lm
#	MKBONUS	= DB=1 -C srcs/bonus
#else
#	CFLAGS	= -O3 -Wall -Wextra -Werror
#	LIBS	= -L libft/ -lft ${MLX_LNK} -lm

# Optimization level 3 : O is a letter !!!!
CFLAGS = -O3 -Wall -Wextra -Werror -g
#INC = -I minilibx_opengl
LIBS = $(MLX_LNK) -lm

#ifeq ($(OS), Linux)
#	MLX_DIR	= minilibx-linux
#	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
#	SRCS	+=	srcs/events/mouse_bonus.c \
#				srcs/parser/resolution_parser.c
#else
MLX_DIR	= minilibx_opengl
MLX_LNK	= -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
#	SRCS	+=	srcs/events/mouse_mac_bonus.c \
#				srcs/parser/resolution_mac_parser.c
#endif
# B_HEADER = cub3d_bonus.h
SRCS = src/cub3d.c \
		src/checks/argvcheck.c \
		src/checks/parse_map.c\
		src/checks/check_map.c \
		src/libft/basics.c \
		src/libft/basics_bis.c\
		src/libft/get_next_line.c \
		src/utils/errors.c \
		src/textures/xpm.c \
		src/textures/colors.c \

OBJS = $(SRCS:.c=.o)

#BIN = *.o
#.c.o:
#	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INC}

#OBJS: $(SRCS)
#	$(CC) $(CFLAGS) $(SRCS)

all: $(NAME)

mlx: $(MLX-DIR)
	@echo "\033[34m-= Making libX.a... =-"
	@make -C $(MLX_DIR)

$(NAME): $(SRCS) $(OBJS) mlx
	@echo "\n\033[0;33mCompiling..."
	${CC} ${CFLAGS} ${OBJS} ${MLX_LNK} -o ${NAME}
	@echo "\033[32m   ______      __   _____ ____  "
	@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
	@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
	@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
	@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./Cub3D <map.cub> [--save]"

clean:
	@echo "\033[0;31mCleaning..."
	rm -f $(OBJS)
	# + $(B_OBJ)
	# + rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[34m-= Cleaning mlx... =-"
	@make clean -C $(MLX_DIR)
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	rm -f *.o
	@echo "\033[0m"

re: fclean all

# sqr: re
# 	./$(NAME) maps/sqr.cub

# bmp: re
# 	./$(NAME) maps/map.cub --save

# err: re
# 	./$(NAME) maps/none

# inv: re
# 	./$(NAME) maps/inv.cub

norm:
	@norminette $(SRCS) $(HEADER)
# + $(B_FIL) bonus/$(B_HEADER)
	@echo "\033[1;34mcub3d\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"

.PHONY: all clean fclean re norm
# + bonus test sqr bmp err inv ?
# makefile error *** commands commence before first target. stop 
# ===> manque un \ ou y'a une espace ou un saut à la ligne à la ligne indiquée
