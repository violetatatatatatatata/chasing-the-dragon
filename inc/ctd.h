/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ctd.h												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/27 14:15:03 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2026/01/28 15:01:11 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef CTD_H
# define CTD_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>

# include "../libs/libft/Includes/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1080
# define HEIGHT 720
# define TILE_SIZE 64

# define ESC	53
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124

# define WALL	'1'
# define EMPTY	'0'
# define NORTH	'N'
# define SOUTH	'S'
# define EAST	'E'
# define WEST	'W'

# define GREEN	"\x1b[32m"
# define RED	"\x1b[31m"
# define RESET	"\x1b[m"

typedef struct s_map
{
	char		*no_sprite_path;
	char		*so_sprite_path;
	char		*we_sprite_path;
	char		*ea_sprite_path;
	uint32_t	*rgb_floor;
	uint32_t	*rgb_celling;
	int			x_max;
	int			y_max;
	char		**map;
}	t_map;

typedef struct	s_draw
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
}	t_draw;

typedef struct	s_player
{
	double	x_pos;
	double	y_pos;
	double	pov;
}	t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*p;
	t_draw		texture;
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
int		print_msg(char *str, int exit);
uint32_t	get_rgba(char *str);

#endif
