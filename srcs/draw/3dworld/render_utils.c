/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_3d.c  		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

mlx_image_t	*select_wall_texture(t_game *g, t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.dir.x > 0)
			return (g->texture.we_i);
		else
			return (g->texture.ea_i);
	}
	else
	{
		if (ray.dir.y > 0)
			return (g->texture.so_i);
		else
			return (g->texture.no_i);
	}
}

static uint32_t	get_pixel_color(mlx_image_t *tex, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

void	draw_wall_column(t_game *g, int x, t_wall_draw d)
{
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	uint32_t	color;

	step = (double)d.texture->height / d.line_height;
	tex_pos = (d.draw_start - (int)g->img->height / 2
			+ d.line_height / 2) * step;
	y = d.draw_start;
	while (y < d.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)d.texture->height)
			tex_y = d.texture->height - 1;
		tex_pos += step;
		color = get_pixel_color(d.texture, d.tex_x, tex_y);
		mlx_put_pixel(g->img, x, y, color);
		y++;
	}
}
