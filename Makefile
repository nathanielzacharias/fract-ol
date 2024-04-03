#target
NAME	=	fractol
CC		=	cc
CFLAGS	=	-Wextra -Wall -Werror
STDLIBS = 	-lXext -lX11 -lm

#minilibx as cloned from github 42 Paris
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

#libft
LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT 	   = $(LIBFT_PATH)$(LIBFT_NAME)

INC			= -I./includes -I./$(LIBFT_PATH) -I./$(MLX_PATH)

SRC_PATH	=	./src/
SRC			=	fractol.c \
				conversion_helpers.c \
				hooks.c \
				mlx_helpers.c \
				transforms.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(MLX) $(LIBFT) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) $(STDLIBS)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean