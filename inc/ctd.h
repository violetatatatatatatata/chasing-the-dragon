/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:07:53 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/21 19:55:22 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTD_H
# define CTD_H

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define TITLE "Chasing the dragon"
# define WIDTH 1920
# define HEIGHT 1080
# define WIDTH_MAP 512
# define HEIGHT_MAP 256
# define PATH "sprites/tree_nord.png"

# include <libft.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <stdint.h>

enum e_type
{
	wall,
	empty,
	player
};

typedef struct s_vector2d
{
	int	x;
	int	y;
}	t_vector2d;

typedef struct s_cell	t_cell;

typedef struct s_cell
{
	t_vector2d	pos;
	enum e_type	cell_type;
	t_cell		*no;
	t_cell		*so;
	t_cell		*we;
	t_cell		*ea;
}	t_cell;

typedef struct s_min_map
{
	mlx_image_t	*map_img;
}	t_min_map;

typedef struct s_game
{
	char		**map;
	char		*no_sprite_path;
	char		*so_sprite_path;
	char		*we_sprite_path;
	char		*ea_sprite_path;
	char		*rgb_floor;
	char		*rgb_celling;
	mlx_t		*mlx;
	t_min_map	*min_map;
}	t_game;

/*		DRAW		*/
int		draw(void);

/*		DRAW_MIN_MAP	*/
void	init_min_map(t_game *game);

/*		UTILS		*/
void	ft_error(void);
#endif
