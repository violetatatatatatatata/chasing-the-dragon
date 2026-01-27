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
	game->min_map->map_img = mlx_new_image(game->mlx, 256, 256);
	if (!game->min_map->map_img
		|| (mlx_image_to_window(game->mlx, game->min_map->map_img, 0, 0) < 0))
		ft_error();
	mlx_put_pixel(game->min_map->map_img, 0, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, WIDTH - 1, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, 255, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, 257, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, 260, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, 254, 0, 0xFF0000FF);
	mlx_put_pixel(game->min_map->map_img, 0, 255, 0xFF0000FF);
}

void	draw_min_map()
{
	
}
