NAME	= fractol

CC		= cc
CFLAGS	= -Wextra -Wall -Werror

MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

#LIBS 	= -lmlx
#LPATH	= -L $(MLX_PATH)

SRC_PATH	=	./
SRC			=	fractol.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(MLX) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lXext -lX11 -lmlx -L $(MLX_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean