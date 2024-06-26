


NAME	:= Game
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast 
LIBMLX	:= ~/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= put_mlxs_.c map_utils_.c  map_utiles.c long_utils.c move_utils.c map_join_utils.c so_long.c so_long_checks.c
OBJS	:= ${SRCS:.c=.o}
MLX_FLAGS    = ~/MLX42/build/libmlx42.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit	
all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C  $(LIBMLX)/build -j4


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(MLX_FLAGS) $(LIBS) $(HEADERS) -o $(NAME)
	
%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
fclean: clean
	@rm -rf $(NAME)
re: clean all