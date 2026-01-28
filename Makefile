# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 14:57:51 by avelandr          #+#    #+#              #
#    Updated: 2026/01/28 16:16:24 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g
INCLUDES    = -I./inc -I./libs/libft/Includes -I./libs/MLX42/include
LDFLAGS     = -L./libs/MLX42 -lmlx42 -L./libs/libft -lft -lglfw -ldl -lpthread -lm

# Busca todos los archivos .c en srcs y subdirectorios
SRC_DIR     = srcs
SRC 		= $(shell find $(SRC_DIR) -name "*.c" -not -path "*/so_long/*")
OBJ         = $(SRC:.c=.o)

RESET       = \033[0m
PINK        = \033[1;35m
BLUE        = \033[1;36m
GREEN       = \033[1;32m
VIOLET      = \033[38;2;185;39;233m

TOTAL_SRCS := $(words $(SRC))

all: print libft mlx42 $(NAME)

print:
	@echo "                ⬛⬛⬛⬛⬛                "
	@echo "            ⬛⬛🟨🟨🟨🟨🟨⬛⬛            "
	@echo "        ⬛⬛🟦🟦⬛⬛⬛⬛⬛🟦🟦⬛⬛        "
	@echo "      ⬛🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦⬛      "
	@echo "    ⬛🟦🟦🟦🟦🟨🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦⬛    "
	@echo "    ⬛🟦🟨🟨🟨⬛⬛⬛⬛⬛⬛⬛🟨🟨🟨🟦⬛    "
	@echo "  ⬛🟨🟨⬛⬛⬛⬜⬜⬜🏼⬜⬜⬜⬛⬛⬛🟨🟨⬛  "
	@echo "  ⬛⬛⬛🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼⬛⬛⬛  "
	@echo "  ⬛🏼🏼🏼⬜⬜⬜⬜⬛⬜⬛⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "  ⬛🏼🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "  ⬛🏼🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "    ⬛🏼🏼🏼⬜⬜⬜⬜🏼⬜⬜⬜⬜🏼🏼🏼⬛    "
	@echo "    ⬛🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼⬛    "
	@echo "      ⬛🏼🏼🏼🏼🏼⬛⬛⬛🏼🏼🏼🏼🏼⬛      "
	@echo "    ⬛⬛⬛⬛🏼🏼🏼🏼🏼🏼🏼🏼🏼⬛⬛⬛⬛    "
	@echo "  ⬛🟥🟥🟥🟥⬛⬛⬛⬛⬛⬛⬛⬛⬛🟥🟥🟥🟥⬛  "
	@echo "⬛🟥🟥🟥⬛🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥⬛🟥🟥🟥⬛"
	@echo "⬛🟨🟨⬛🟥🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥🟥⬛🟨🟨⬛"
	@echo "⬛🟨🟨⬛🟥🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥🟥⬛🟨🟨⬛"
	@echo "  ⬛⬛⬛⬛⬛🟥🟥🟥🟥⬛🟥🟥🟥🟥⬛⬛⬛⬛⬛  "
	@echo "      ⬛🟫🟫⬛⬛⬛⬛⬛⬛⬛⬛⬛🟫🟫⬛      "
	@echo "    ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛    "

# Construir libft primero
libft:
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C ./libs/libft --no-print-directory

# Construir MLX42 si no está construido
mlx42:
	@echo "$(BLUE)Building MLX42...$(RESET)"
	@if [ ! -f "./libs/MLX42/libmlx42.so" ]; then \
		cd ./libs/MLX42 && cmake -B build && cmake --build build -j4; \
		mv build/libmlx42.so .; \
	fi

$(NAME): $(OBJ)
	@echo ""
	@echo "$(BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Exercise $(NAME) compiled successfully!$(RESET)"

# Regla para compilar archivos .c
%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@curr=$$(find $(SRC_DIR) -type f -name "*.o" 2>/dev/null | wc -l); \
	percent=$$(( $$curr * 100 / $(TOTAL_SRCS) )); \
	bar_len=$$(( $$percent / 2 )); \
	bar_str=""; \
	i=0; \
	while [ $$i -lt $$bar_len ]; do bar_str="$${bar_str}▓"; i=$$((i+1)); done; \
	spaces=""; \
	i=0; \
	rest=$$((50 - $$bar_len)); \
	while [ $$i -lt $$rest ]; do spaces="$${spaces}░"; i=$$((i+1)); done; \
	printf "\r$(BLUE)Compiling: $(PINK)[$$bar_str$$spaces] $(PINK)$$percent%% $(RESET)"

clean:
	@rm -f $(OBJ)
	@make -C ./libs/libft clean  --no-print-directory
	@echo "$(BLUE)Objects cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C ./libs/libft fclean  --no-print-directory
	@if [ -f "./libs/MLX42/libmlx42.a" ]; then rm -f ./libs/MLX42/libmlx42.a; fi
	@echo "$(BLUE)Executable cleaned.$(RESET)"

re: fclean all

# Regla para ejecutar (opcional)
run: all
	@./$(NAME)

.PHONY: all clean fclean re libft mlx42 run
