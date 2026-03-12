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
}

static uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;

	if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (0);
	p = &tex->pixels[(y * tex->width + x) * 4];
	return (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
}

void	draw_roof_floor(t_game *g)
{
	t_vector2_i	pos;
	int			tex_x;
	int			tex_y;

	g->texture.yo_i = mlx_texture_to_image(g->mlx, g->texture.yo_t);
	g->texture.dragon_i = mlx_texture_to_image(g->mlx, g->texture.dragon_t);
	pos.x = 0;
	while (pos.x < WIDTH)
	{
		pos.y = 0;
		while (pos.y < HEIGHT)
		{
			if (pos.y < HEIGHT / 2)
			{
				tex_x = (pos.x * g->texture.yo_t->width) / WIDTH;
				tex_y = (pos.y * g->texture.yo_t->height) / (HEIGHT / 2);
				mlx_put_pixel(g->img_cube_map, pos.x, pos.y,
					get_texture_pixel(g->texture.yo_t, tex_x, tex_y));
			}
			else
				mlx_put_pixel(g->img_cube_map, pos.x, pos.y,
					*(g->map.rgb_floor));
			pos.y++;
		}
		pos.x++;
	}
}
