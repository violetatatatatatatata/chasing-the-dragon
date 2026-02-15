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

/*static void	ft_calculate_view_and_projection(t_game *g, t_matrix4f view,
	t_matrix4f projection)
{
	matrix_identity(view);
	matrix_translate(view, g->p.x_pos, g->p.y_pos, 0.0f);
	//matrix_rotate_x(view, ft_deg_to_rad(g->camera.pitch));
	//matrix_rotate_y(view, ft_deg_to_rad(g->camera.yaw));
	ft_projection_matrix_perspective(projection, g);
}

/// @brief Calculates object projection
/// @param mvp 
/// @param obj 
/// @param view 
/// @param projection 
static void	ft_calculate_object_mvp(t_matrix4f mvp, t_object *obj,
	t_matrix4f view, t_matrix4f projection)
{
	t_matrix4f	model;
	t_matrix4f	view_model;

	matrix_identity(model);
	matrix_scale(model, obj->scale.x, obj->scale.y, obj->scale.z);
	matrix_rotate_x(model, ft_deg_to_rad(obj->rotation.x));
	matrix_rotate_y(model, ft_deg_to_rad(obj->rotation.y));
	matrix_rotate_z(model, ft_deg_to_rad(obj->rotation.z));
	matrix_translate(model, obj->position.x, obj->position.y, obj->position.z);
	matrix_multiply(view_model, view, model);
	matrix_multiply(mvp, projection, view_model);
}

void	ft_render_scene(t_game *g)
{
	t_matrix4f	view_matrix;
	t_matrix4f	projection_matrix;
	t_matrix4f	mvp_matrix;
	int			i;

	ft_calculate_view_and_projection(g, view_matrix, projection_matrix);
	i = 0;
	while (i < g->num_objects)
	{
		ft_calculate_object_mvp(mvp_matrix, &g->objects[i],
			view_matrix, projection_matrix);
		ft_draw_object(g, &g->objects[i], mvp_matrix);
		i++;
	}
}

static void	ft_matrix_calculate_mvp(t_matrix4f mvp, t_matrix4f model,
		t_matrix4f view, t_matrix4f projection)
{
	t_matrix4f	view_model;

	matrix_multiply(view_model, view, model);
	matrix_multiply(mvp, projection, view_model);
}

static void	ft_matrix_get_mvp(t_matrix4f mvp_matrix, float model_scale,
		t_game *g)
{
	t_matrix4f	projection_matrix;
	t_matrix4f	view_matrix;
	t_matrix4f	model_matrix;

	matrix_identity(model_matrix);
	matrix_rotate_x(model_matrix, ft_deg_to_rad(-90.0f));
	matrix_translate(model_matrix, 0.0f,
		0.0f, 0.0f);
	matrix_scale(model_matrix, model_scale, model_scale, model_scale);
	matrix_identity(view_matrix);
	matrix_translate(view_matrix,
		g->mlx->width / 4,
		g->mlx->height / 4,
		5.0f);
	matrix_rotate_z(view_matrix, ft_deg_to_rad(0.0f));
	matrix_rotate_x(view_matrix, ft_deg_to_rad(35.264f));
	matrix_rotate_y(view_matrix, ft_deg_to_rad(45.0f));
	matrix_identity(projection_matrix);
	projection_matrix_perspective(projection_matrix);
	ft_matrix_calculate_mvp(mvp_matrix, model_matrix,
		view_matrix, projection_matrix);
}

void	draw_3d(t_game *g)
{

}*/

void	clear_framebuffer(t_game *g)
{
	size_t	size;

	size = g->img->width * g->img->height * 4;
	ft_memset(g->img->pixels, 0, size);
}

double	calculate_ray_angle(int x, double player_angle)
{
	double	camera_x;
	double	ray_angle;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray_angle = player_angle + atan(camera_x * tan(FOV * 0.5));
	return (ray_angle);
}

t_column_render	calculate_column_dimensions(double perp_dist)
{
	t_column_render	col;

	col.line_height = (int)(HEIGHT / perp_dist);
	col.draw_start = -col.line_height / 2 + HEIGHT / 2;
	if (col.draw_start < 0)
		col.draw_start = 0;
	col.draw_end = col.line_height / 2 + HEIGHT / 2;
	if (col.draw_end >= HEIGHT)
		col.draw_end = HEIGHT - 1;
	return (col);
}

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
			return (g->texture.no_i);
		else
			return (g->texture.so_i);
	}
}

int	calculate_tex_x(t_ray ray, mlx_image_t *texture)
{
	int	tex_x;

	tex_x = (int)(ray.hit_x * (double)texture->width);
	if ((ray.side == 0 && ray.dir.x > 0)
		|| (ray.side == 1 && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

uint32_t	get_pixel_color(mlx_image_t *tex, int tex_x, int tex_y)
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
	tex_pos = (d.draw_start - HEIGHT / 2 + d.line_height / 2) * step;
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

void	render_frame(t_game *g)
{
	int					x;
	double				ray_angle;
	t_ray				ray;
	t_column_render		col;
	t_wall_draw			draw;

	clear_framebuffer(g);
	x = 0;
	while (x < WIDTH)
	{
		ray_angle = calculate_ray_angle(x, g->p.pov);
		ray = cast_ray(ray_angle, g);
		col = calculate_column_dimensions(ray.perp_dist);
		draw.texture = select_wall_texture(g, ray);
		draw.tex_x = calculate_tex_x(ray, draw.texture);
		draw.draw_start = col.draw_start;
		draw.draw_end = col.draw_end;
		draw.line_height = col.line_height;
		draw_wall_column(g, x, draw);
		x++;
	}
	mlx_image_to_window(g->mlx, g->img, 0, 0);
}
