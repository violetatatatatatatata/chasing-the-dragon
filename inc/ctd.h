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
# include <stdbool.h>

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
# define FOV 60
# define RAY_LIMIT 4000
# define INJECT_DURATION 30
# define DRAGON_DIST 3.0 

# define M_PI 3.14159265358979323846

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

typedef struct s_vector2_f
{
	double	x;
	double	y;
}	t_vector2_f;

typedef struct s_vector2_i
{
	int	x;
	int	y;
}	t_vector2_i;

typedef struct s_vector4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vector4f;

typedef float	t_matrix4f[4][4];

typedef struct s_ray
{
	t_vector2_f	dir;
	t_vector2_i	map;
	t_vector2_f	side_dist;
	t_vector2_f	delta_dist;
	t_vector2_i	step;
	int			side;
	double		perp_dist;
	double		hit_x;
}	t_ray;

typedef struct s_raycast_result
{
	double	distance;
	double	wall_height;
}	t_raycast_result;

typedef struct s_column_render
{
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_column_render;

typedef struct s_wall_draw
{
	int				draw_start;
	int				draw_end;
	int				line_height;
	mlx_image_t		*texture;
	int				tex_x;
}	t_wall_draw;

typedef struct s_min_map
{
	mlx_image_t	*map_img;
	t_vector2_i	player_cell;
	t_vector2_i	player_offset;
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

typedef struct s_draw
{
	mlx_texture_t	*no_t;
	mlx_texture_t	*so_t;
	mlx_texture_t	*ea_t;
	mlx_texture_t	*we_t;
	mlx_image_t		*no_i;
	mlx_image_t		*so_i;
	mlx_image_t		*ea_i;
	mlx_image_t		*we_i;
	mlx_image_t		*dragon_i;
	mlx_texture_t	*dragon_t;
	mlx_texture_t	*arms_idle_t;
	mlx_image_t		*arms_idle_i;
	mlx_texture_t	*arms_inject_t;
	mlx_image_t		*arms_inject_i;
	mlx_texture_t   *hud_heroin_t[5];
    mlx_image_t     *hud_heroin_i[5];
    mlx_texture_t   *hud_smack_t[4];
    mlx_image_t     *hud_smack_i[4];
}	t_draw;

typedef struct	s_player
{
	double	x_pos;
	double	y_pos;
	double	pov;
	size_t	shots_left;
	size_t	spikes_left;
	bool	is_injecting;
	int		inject_timer;
}	t_player;

typedef struct	s_game
{
	t_map		map;
	t_player	p;
	mlx_t		*mlx;
	mlx_image_t	*img;
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

// srcs/raycast/raycast.c
t_raycast_result	raycast(double x_angle, double y_angle, t_game *g);
t_ray	cast_ray(double ray_angle, t_game *g);

// srcs/utils/matrix/matrix_identity.c
void	matrix_identity(t_matrix4f m);

// srcs/utils/matrix/matrix_multiply.c
void	matrix_multiply(t_matrix4f res, t_matrix4f a, t_matrix4f b);

// srcs/utils/matrix/matrix_rotation.c
void	matrix_rotate_x(t_matrix4f m, float angle);
void	matrix_rotate_y(t_matrix4f m, float angle);
void	matrix_rotate_z(t_matrix4f m, float angle);

// srcs/utils/matrix/matrix_scale.c
void	matrix_scale(t_matrix4f m, float x, float y, float z);

// srcs/utils/matrix/matrix_translate.c
void	matrix_translate(t_matrix4f m, float x, float y, float z);

// srcs/utils/matrix/matrix_vec4_multiply.c
void	matrix_vec4_multiply(t_vector4f *res, t_matrix4f m, t_vector4f v);

// srcs/utils/matrix/projection_matrix_perspective.c
void	projection_matrix_perspective(t_matrix4f projection_matrix,
		t_game *g);

// srcs/utils/init_vec4f.c
t_vector4f	init_vec4f(float x, float y, float z, float w);

// srcs/utils/messages.c
int	print_msg(char *str, int exit);

// srcs/utils/utils.c
uint32_t	get_rgba(char *str);

// srcs/utils/convertor.c
t_vector2_i	cell2pixel(int x, int y);
t_vector2_i	pixel2cell(int x, int y);

// srcs/utils/ft_error.c
void	ft_error(void);

//	srcs/utils/get_player_pos.c
t_vector2_i	get_player_pixel_pos(t_game *game);
t_vector2_i	get_player_cell_pos(t_game *game);

// srcs/init/init_sprites.c
void	draw_colors(t_game *game);
int	load_sprites(t_game *game);

// srcs/draw/draw.c
void	ft_on_resize(int32_t w, int32_t h, void *param);
void	ft_update_draw(void *g);
int	draw(t_game game);
void	render_frame(t_game *g);

// srcs/draw/min_map/draw_min_map.c
void	init_min_map(t_game *game);
void	draw_min_map(t_game *game);

// srcs/test/test.c
char	**ft_create_map(int width, int height);

void	update_dragon_visibility(t_game *game);
void	update_arms_animation(t_game *game);
void	draw_player(t_game *g);
void	draw_dragon(t_game *g);

#endif
