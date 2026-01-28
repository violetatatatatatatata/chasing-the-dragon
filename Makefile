# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 14:57:51 by avelandr          #+#    #+#              #
#    Updated: 2026/01/28 17:30:22 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g
INCLUDES    = -I./inc -I./libs/libft/Includes -I./libs/MLX42/include
LDFLAGS     = -L./libs/MLX42 -lmlx42 -L./libs/libft -lft -lglfw -ldl -lpthread -lm

SRC_DIR     = srcs
SRC         = $(shell find srcs -name "*.c")
OBJ         = $(SRC:.c=.o)

BOLD      = \033[1m
BLACK     = \033[1;30m
GREEN     = \033[1;32m
YELLOW    = \033[1;33m
BLUE      = \033[1;34m
MAGENTA   = \033[1;35m
CYAN      = \033[1;36m

TOTAL_SRCS := $(words $(SRC))

all: ctd print libft mlx42 $(NAME)

ctd:
	@echo "$(YELLOW)";
	@echo "        ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ";
	@echo "       ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗";
	@echo "       ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║";
	@echo "       ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║";
	@echo "       ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝";
	@echo "        ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ";
	@echo "$(RESET)";

print:
	@echo "                       ⬛⬛⬛⬛⬛                "
	@echo "                   ⬛⬛🟨🟨🟨🟨🟨⬛⬛            "
	@echo "               ⬛⬛🟦🟦⬛⬛⬛⬛⬛🟦🟦⬛⬛        "
	@echo "             ⬛🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦⬛      "
	@echo "           ⬛🟦🟦🟦🟦🟨🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦⬛    "
	@echo "           ⬛🟦🟨🟨🟨⬛⬛⬛⬛⬛⬛⬛🟨🟨🟨🟦⬛    "
	@echo "         ⬛🟨🟨⬛⬛⬛⬜⬜⬜🏼⬜⬜⬜⬛⬛⬛🟨🟨⬛  "
	@echo "         ⬛⬛⬛🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼⬛⬛⬛  "
	@echo "         ⬛🏼🏼🏼⬜⬜⬜⬜⬛⬜⬛⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "         ⬛🏼🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "         ⬛🏼🏼🏼⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🏼🏼🏼⬛  "
	@echo "           ⬛🏼🏼🏼⬜⬜⬜⬜🏼⬜⬜⬜⬜🏼🏼🏼⬛    "
	@echo "           ⬛🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼🏼⬛    "
	@echo "             ⬛🏼🏼🏼🏼🏼⬛⬛⬛🏼🏼🏼🏼🏼⬛      "
	@echo "           ⬛⬛⬛⬛🏼🏼🏼🏼🏼🏼🏼🏼🏼⬛⬛⬛⬛    "
	@echo "         ⬛🟥🟥🟥🟥⬛⬛⬛⬛⬛⬛⬛⬛⬛🟥🟥🟥🟥⬛  "
	@echo "       ⬛🟥🟥🟥⬛🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥⬛🟥🟥🟥⬛"
	@echo "       ⬛🟨🟨⬛🟥🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥🟥⬛🟨🟨⬛"
	@echo "       ⬛🟨🟨⬛🟥🟥🟥🟥🟥🟥⬛🟥🟥🟥🟥🟥🟥⬛🟨🟨⬛"
	@echo "         ⬛⬛⬛⬛⬛🟥🟥🟥🟥⬛🟥🟥🟥🟥⬛⬛⬛⬛⬛  "
	@echo "             ⬛🟫🟫⬛⬛⬛⬛⬛⬛⬛⬛⬛🟫🟫⬛      "
	@echo "           ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛    "
                  
libft:            
	@echo ""
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C ./libs/libft --no-print-directory

mlx42:
	@echo ""
	@echo "$(BLUE)Building MLX42...$(RESET)"
	@if [ ! -f "./libs/MLX42/libmlx42.so" ]; then \
		cd ./libs/MLX42 && cmake -B build && cmake --build build -j4; \
		mv build/libmlx42.so .; \
	fi
	@echo "$(BLUE)MLX42 done!$(RESET)"
	@echo ""
	@echo "$(BLUE)Building cub3D...$(RESET)"

$(NAME): $(OBJ)
	@echo ""
	@echo "$(BLUE)cub3D done!$(RESET)"
	@echo ""
	@echo "$(BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Exercise $(NAME) compiled successfully!$(RESET)"

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
	printf "\r$(BLUE)Compiling cub3D: $(YELLOW)[$$bar_str$$spaces] $(YELLOW)$$percent%% $(RESET)"

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

.PHONY: all clean fclean re libft mlx42 
