NAME = cub3D

HEADER = cub3d.h

CC = clang
CFLAGS = -Wall -Wextra -Werror -I $(HEADER)
RM = rm -f

#MLX = minilibx_opengl
#LXFLAGS = -lmlx -framework OpenGL -framework AppKit

# B_HEADER = cub3d_bonus.h

SRCS = src/main.c \
		src/checks/argvcheck.c \
		src/libft/basics.c \
		src/libft/get_next_line.c \
		src/utils/errors.c \

OBJS = $(SRCS.c=.o)

OBJS: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(HEADER)

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@echo "\n Removing objects"
	$(RM) *.o
	@echo "\n\033[0;33mCompiling..."
	$(CC)  $(CFLAGS) -c $(SRCS) $(OBJS)
	@echo "\033[0m"


clean:
	@echo "\033[0;31mCleaning..."
	rm -f $(OBJS)
	# + $(B_OBJ)
	# + rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test1: $(NAME) 
	$(NAME) ; ./a.out maps/test1.cub
# =====> no input file


# =====> no input file

test2: clean
	./$(NAME) maps/test1.cub --save
# ====> make: ./cub3D: No such file or directory

test3: $(CC) $(CFLAGS) $(SCRS)
# ====> No rule to make target `clang', needed by `test3'.  Stop.

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
