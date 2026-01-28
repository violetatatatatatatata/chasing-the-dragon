/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_min_map.c      								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	init_min_map(t_game *game)
{
	game->min_map = malloc(sizeof(t_min_map));
	game->min_map->map_img
		= mlx_new_image(game->mlx, WIDTH_MAP, HEIGHT_MAP);
	if (!game->min_map->map_img
		|| (mlx_image_to_window(game->mlx,
				game->min_map->map_img, WIDTH * 2 - WIDTH_MAP - 10, 10) < 0))
		ft_error();
	ft_memset(game->min_map->map_img->pixels, 255,
		game->min_map->map_img->width
		* game->min_map->map_img->height * sizeof(int32_t));
	game->min_map->cell_count = WIDTH_MAP / CELL_SIZE;
}

static void	ft_map_size(t_game *game)
{
	if (game->min_map->cell_count < game->max_map_x)
	{
		printf("HELP\n");
	}
}

void	draw_min_map(t_game *game)
{
	ft_map_size(game);
}
