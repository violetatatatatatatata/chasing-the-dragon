/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_roof_floor.c  		   						:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	init_roof_floor(t_game *g)
{
	g->img_cube_map = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g->mlx, g->img_cube_map, 0, 0);
	draw_roof_floor(g);
}

void	draw_roof_floor(t_game *g)
{
	t_vector2_i	pos;

	pos.x = 0;
	while (pos.x < WIDTH)
	{
		pos.y = 0;
		while (pos.y < HEIGHT)
		{
			if (pos.y < HEIGHT / 2)
				mlx_put_pixel(g->img_cube_map, pos.x, pos.y,
					*(g->map.rgb_celling));
			else
				mlx_put_pixel(g->img_cube_map, pos.x, pos.y,
					*(g->map.rgb_floor));
			pos.y++;
		}
		pos.x++;
	}
}
