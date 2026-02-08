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

# include <libft.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <stdint.h>

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define R 67
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define TITLE "Chasing the dragon"
# define WIDTH 1920
# define HEIGHT 1080
# define WIDTH_MAP 500
# define HEIGHT_MAP 500
# define CELL_PIXEL_SIZE 15
# define CELL_PLAYER_SIZE 7
# define CELL_SIZE 10

# define WALL	'1'
# define EMPTY	'0'
# define NORTH	'N'
# define SOUTH	'S'
# define EAST	'E'
# define WEST	'W'

# define GREEN	"\x1b[32m"
# define RED	"\x1b[31m"
# define RESET	"\x1b[m"

typedef enum e_type
{
	empty,
	wall,
	player
}	t_type;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_min_map
{
	mlx_image_t	*map_img;
	int			cell_count_x;
	int			cell_count_y;
}	t_min_map;

typedef struct s_map
{
	char		*no_sprite_path;
	char		*so_sprite_path;
	char		*we_sprite_path;
	char		*ea_sprite_path;
	uint32_t	*rgb_floor;
	uint32_t	*rgb_celling;
	int			max_map_x;
	int			max_map_y;
	char		**map;
	t_min_map	*min_map;
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
	size_t	shots_left;
	size_t	spikes_left;
}	t_player;

typedef struct	s_game
{
	t_map		map;
	t_player	p;
	mlx_t		*mlx;
	t_draw		texture;
}	t_game;

// srcs/logic/movs.c
int	move_player(t_game *game, double new_x, double new_y);
int handle_key_press(int keycode, t_game *game);

// srcs/logic/shots.c
double	speedy_gonzales(t_player p);

// srcs/parse/check_map.c
int	check_map_closed(t_game *game);

// srcs/parse/format.c
int	is_valid_file(t_game *game);

// srcs/parse/map.c
int	open_map(t_game *game, char *input);

// srcs/utils/messages.c
int	print_msg(char *str, int exit);

// srcs/utils/utils.c
uint32_t	get_rgba(char *str);

// srcs/utils/convertor.c
t_vector2	cell2pixel(int x, int y);
t_vector2	pixel2cell(int x, int y);

// srcs/utils/ft_error.c
void	ft_error(void);

//	srcs/utils/get_player_pos.c
t_vector2	get_player_pixel_pos(t_game *game);

// srcs/init/init_sprites.c
void	draw_colors(t_game *game);
int	load_sprites(t_game *game);

// srcs/draw/draw.c
void	ft_on_resize(int32_t w, int32_t h, void *param);
void	ft_update_draw(void *g);
int	draw(t_game game);

// srcs/draw/min_map/draw_min_map.c
void	init_min_map(t_game *game);
void	draw_min_map(t_game *game);

// srcs/test/test.c
char	**ft_create_map(int width, int height);

#endif
