# Target executable
NAME = fractol

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

# Source files
SRC_FILES	=	fractol.c \
				conversion_helpers.c \
				hooks.c \
				mlx_helpers.c \
				transforms.c

# Object files
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Includes
INC = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Dependency files
# DEP_FILES = $(OBJ_FILES:.o=.d)

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

# Include dependency files
# -include $(DEP_FILES)

# Default rule
all: $(NAME)

# Linking rule
$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIBS)

# Library rules
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

# Clean rule
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

# Fclean rule
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Re rule
re: fclean all

# PHONY
.PHONY: all clean fclean re
