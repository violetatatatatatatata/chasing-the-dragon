/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:15:03 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/27 18:42:18 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTD_H
# define CTD_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "../libs/libft/Includes/libft.h"
//# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1080
# define HEIGHT 720
# define TILE_SIZE 64

# define ESC    53
# define W      13
# define A      0
# define S      1
# define D      2
# define LEFT   123
# define RIGHT  124

# define WALL   '1'
# define EMPTY  '0'
# define NORTH  'N'
# define SOUTH  'S'
# define EAST   'E'
# define WEST   'W'

# define GREEN  "\x1b[32m"
#define RED     "\x1b[31m"
# define RESET  "\x1b[m"

struct s_cell;

typedef struct s_vector2d
{
	int				x;
	int				y;
	struct s_cell	*cell;
}	t_vector2d;

typedef struct s_cell
{
	t_vector2d		pos;
	//enum e_type		type;
	struct s_cell	*no;
	struct s_cell	*so;
	struct s_cell	*we;
	struct s_cell	*ea;
}	t_cell;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*no_sprite_path;
	char		*so_sprite_path;
	char		*we_sprite_path;
	char		*ea_sprite_path;
	char		*rgb_floor;
	char		*rgb_celling;
	char		**map;
//	t_list		*map_lines;
	t_cell		*cells;
}	t_game;

// srcs/logic/movs.c
int move_player(t_game *game, int new_x, int new_y);
int handle_key_press(int keycode, t_game *game);

// srcs/parse/format.c
int check_map_closed(t_game *game);
int	is_valid_file(t_game *game);

// srcs/parse/map.c
int	open_map(t_game *game, char *input);

// srcs/main.c
int	main(int argc, char **argv);

// srcs/utils/messages.c
int	print_msg(char *str, int exit);

#endif
