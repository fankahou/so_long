SRC = main.c \
	utils.c \
	parse.c \
	parse1.c \
	put.c \
	put1.c \
	init.c \
	enermy.c

OBJ = $(SRC:.c=.o)

NAME = so_long

LIBFT = libft/libft.a

MLX_FLAGS = -L. -lmlx -framework OpenGL -framework AppKit

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) libmlx.dylib -o $(NAME) $(MLX_FLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

web:
	emcc \
	$(shell find . -maxdepth 1 -name "*.c" ! -name "mlx_bridge.c") \
	mlx_bridge.c \
	libft/*.c \
	-I. -Iincludes -Ilibft \
	-o index.html \
	--shell-file shell.html \
	-s USE_SDL=2 \
	-s USE_SDL_IMAGE=2 \
	-s SDL2_IMAGE_FORMATS='["xpm"]' \
	-s NO_EXIT_RUNTIME=1 \
	-s ASSERTIONS=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	--preload-file textures@/textures \
	--preload-file maps@/maps \
	-D __EMSCRIPTEN__
	python3 -m http.server 9999


.PHONY: all clean fclean re
