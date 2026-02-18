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

static uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (0);
	pixel = &tex->pixels[(y * tex->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static double	calculate_ray_angle(int x, double player_angle)
{
	double	camera_x;
	//double	ray_dir_x;
	//double	ray_dir_y;
	//double	plane_x;
	//double	plane_y;

	(void)player_angle;
	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	return (player_angle + atan(camera_x * tan((FOV * M_PI / 180.0) / 2.0)));
}

static mlx_texture_t	*select_wall_texture(t_game *g, t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.dir.x > 0)
			return (g->texture.ea_t);
		else
			return (g->texture.we_t);
	}
	else
	{
		if (ray.dir.y > 0)
			return (g->texture.so_t);
		else
			return (g->texture.no_t);
	}
}

static void	draw_wall_column(t_game *g, int x, int line_height, int draw_start, int draw_end, t_ray ray, mlx_texture_t *tex)
{
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			tex_x;
	uint32_t	color;
	double		wall_x;

	if (ray.side == 0)
		wall_x = g->p.y_pos + ray.perp_dist * ray.dir.y;
	else
		wall_x = g->p.x_pos + ray.perp_dist * ray.dir.x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
		tex_x = tex->width - tex_x - 1;

	step = 1.0 * tex->height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_pixel_color(tex, tex_x, tex_y);
		mlx_put_pixel(g->img, x, y, color);
		y++;
	}
}

void	render_frame(t_game *g)
{
	int			x;
	double		ray_angle;
	t_ray		ray;
	int			line_height;
	int			draw_start;
	int			draw_end;
	mlx_texture_t	*tex;

	x = 0;
	while (x < WIDTH)
	{
		ray_angle = calculate_ray_angle(x, g->p.pov);
		ray = cast_ray(ray_angle, g);
		if (ray.perp_dist < 0.0001) ray.perp_dist = 0.0001;
		line_height = (int)(HEIGHT / ray.perp_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
		tex = select_wall_texture(g, ray);
		draw_wall_column(g, x, line_height, draw_start, draw_end, ray, tex);

		x++;
	}
}
