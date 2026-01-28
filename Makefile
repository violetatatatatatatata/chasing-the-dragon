# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 15:11:03 by avelandr          #+#    #+#              #
#    Updated: 2026/01/28 15:42:00 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g -Iinc -Ilibs/libft/Includes -IMLX42/include

LIBFT_DIR   = libs/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = MLX42/build
MLX         = $(MLX_DIR)/libmlx42.a
LIBS        = $(LIBFT) $(MLX) -ldl -lglfw -pthread -lm

OBJ_DIR     = objs

SRC         = $(shell find srcs -name "*.c")
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)

RESET       = \033[0m
PINK        = \033[1;35m
BLUE        = \033[1;36m
GREEN       = \033[1;32m
VIOLET      = \033[38;2;185;39;233m

TOTAL_SRCS := $(words $(SRC))

all: print libft $(NAME)

print:
	@echo "                ⬛⬛⬛⬛⬛                "
	@echo "             ⬛⬛🟨🟨🟨🟨🟨⬛⬛            "
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

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ)
	@echo ""
	@echo "$(BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Exercise $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@curr=$$(find $(OBJ_DIR) -type f -name "*.o" | wc -l); \
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
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Objects cleaned.$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(BLUE)Executable cleaned.$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft print
