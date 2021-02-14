NAME := cub3D

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	PLATFORM := LINUX
endif
ifeq ($(UNAME_S), Darwin)
	PLATFORM := MACOS
endif

ifeq ($(PLATFORM), LINUX)
	INCLUDE := /usr/include
	MINILIB := libmlx_Linux.a
	MINILIB_DIR := minilibx_linux
	LIBS := libmlx_Linux.a -L/usr/lib -lXext -lX11 -lm
endif

ifeq ($(PLATFORM), MACOS)
	INCLUDE := /usr/local/include
	MINILIB := libmlx.dylib
	MINILIB_DIR := minilibx_mms_20200219
	#MINILIB_DIR := minilibx_opengl_20191021
	LIBS := libmlx.dylib -framework OpenGL -framework Appkit
	#LIBS := -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit
endif

SRCS = src/cub.c\
	   src/init.c\
	   src/parse.c\
	   src/parse_id.c\
	   src/parse_map.c\
	   src/parse_validate_map.c\
	   src/parse_utils.c\
	   src/init_game.c\
	   src/raycast.c\
	   src/calc_walls.c\
	   src/calc_walls2.c\
	   src/calc_sprite.c\
	   src/utils.c\
	   src/key_press.c\
	   src/bitmap.c\
	   src/free.c\

RSRCS = src/cub.c\
	   src/init.c\
	   src/parse.c\
	   src/parse_id.c\
	   src/parse_map.c\
	   src/parse_validate_map.c\
	   src/parse_utils.c\
	   src/utils.c\
	   src/free.c\


CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

ROBJS = $(RSRCS:.c=.o)

CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(MINILIB_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT) $(MINILIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIB):
	make -C $(MINILIB_DIR)
	cp $(MINILIB_DIR)/$(MINILIB) .

read: $(ROBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(ROBJS) $(LIBFT) -o $(NAME)

sani:
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

readtest: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) src/yohai.c $(LIBS) $(LIBFT) -o $(NAME)

test:
	$(CC) $(CFLAGS) linux/main.c $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MINILIB_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re fclean clean
