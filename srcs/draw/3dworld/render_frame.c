/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 render_frame.c		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

static double	ft_calculate_ray_angle(int x, double player_angle, int width)
{
	double	camera_x;
	double	ray_angle;
	double	player_angle_rad;
	double	half_fov_rad;

	player_angle_rad = angle2rad(player_angle);
	half_fov_rad = angle2rad(FOV) / 2;
	camera_x = 2.0 * x / (double)width - 1.0;
	ray_angle = player_angle_rad + atan(camera_x * tan(half_fov_rad));
	return (ray_angle);
}

static t_column_render	ft_calculate_column_dimensions(double perp_dist,
	int height, int width)
{
	t_column_render	col;
	double			dist_proj;

	dist_proj = (width / 2.0) / tan((FOV * M_PI / 180.0) / 2.0);
	col.line_height = (int)((CELL_PIXEL_SIZE * dist_proj) / perp_dist);
	col.draw_start = -col.line_height / 2 + height / 2;
	if (col.draw_start < 0)
		col.draw_start = 0;
	col.draw_end = col.line_height / 2 + height / 2;
	if (col.draw_end >= height)
		col.draw_end = height - 1;
	return (col);
}

static int	ft_calculate_tex_x(t_ray ray, mlx_image_t *texture)
{
	int	tex_x;

	tex_x = (int)(ray.hit_x * (double)texture->width);
	if ((ray.side == 0 && ray.dir.x < 0)
		|| (ray.side == 1 && ray.dir.y > 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	render_frame(t_game *g)
{
	int					x;
	double				ray_angle;
	t_ray				ray;
	t_column_render		col;
	t_wall_draw			draw;

	ft_memset(g->img->pixels, 0, g->img->width
		* g->img->height * sizeof(int32_t));
	x = 0;
	while (x < (int)g->img->width)
	{
		ray_angle = ft_calculate_ray_angle(x, g->p.pov, g->img->width);
		ray = cast_ray(ray_angle, g);
		col = ft_calculate_column_dimensions(ray.perp_dist,
				g->img->height, g->img->width);
		draw.texture = select_wall_texture(g, ray);
		draw.tex_x = ft_calculate_tex_x(ray, draw.texture);
		draw.draw_start = col.draw_start;
		draw.draw_end = col.draw_end;
		draw.line_height = col.line_height;
		draw_wall_column(g, x, draw);
		x++;
	}
}
