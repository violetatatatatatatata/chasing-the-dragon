/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 raycast.c      									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

static void	ft_set_ray_step_side(t_ray *r, t_game *g)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (g->p.x_pos - r->map.x * CELL_PIXEL_SIZE)
			/ fabs(r->dir.x);
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = ((r->map.x + 1) * CELL_PIXEL_SIZE - g->p.x_pos)
			/ fabs(r->dir.x);
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (g->p.y_pos - r->map.y * CELL_PIXEL_SIZE)
			/ fabs(r->dir.y);
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = ((r->map.y + 1) * CELL_PIXEL_SIZE - g->p.y_pos)
			/ fabs(r->dir.y);
	}
}

static t_ray	ft_init_ray(double ray_angle, t_game *g)
{
	t_ray	r;

	r.dir.x = cos(ray_angle);
	r.dir.y = sin(ray_angle);
	r.map.x = (int)(g->p.x_pos / CELL_PIXEL_SIZE);
	r.map.y = (int)(g->p.y_pos / CELL_PIXEL_SIZE);
	r.delta_dist.x = CELL_PIXEL_SIZE / fabs(r.dir.x);
	r.delta_dist.y = CELL_PIXEL_SIZE / fabs(r.dir.y);
	ft_set_ray_step_side(&r, g);
	return (r);
}

static void	ft_dda_loop(t_ray *r, t_game *g)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (r->map.x >= 0 && r->map.x < g->map.max_map_x
			&& r->map.y >= 0 && r->map.y < g->map.max_map_y
			&& g->map.map[r->map.y][r->map.x] == '1')
			hit = 1;
	}
}

t_ray	cast_ray(double ray_angle, t_game *g)
{
	t_ray	r;
	double	t;
	double	wall_x;
	double	view_dot;
	double	player_angle_rad;

	r = ft_init_ray(ray_angle, g);
	ft_dda_loop(&r, g);
	if (r.side == 0)
		t = r.side_dist.x - r.delta_dist.x;
	else
		t = r.side_dist.y - r.delta_dist.y;
	player_angle_rad = angle2rad(g->p.pov);
	view_dot = cos(ray_angle) * cos(player_angle_rad)
		+ sin(ray_angle) * sin(player_angle_rad);
	r.perp_dist = t * view_dot;
	if (r.side == 0)
		wall_x = g->p.y_pos + t * r.dir.y;
	else
		wall_x = g->p.x_pos + t * r.dir.x;
	wall_x -= floor(wall_x / CELL_PIXEL_SIZE) * CELL_PIXEL_SIZE;
	r.hit_x = wall_x / CELL_PIXEL_SIZE;
	return (r);
}

t_raycast_result	raycast(double x_angle, double y_angle, t_game *g)
{
	t_vector2_f	pos;
	t_vector2_f	angle;
	double		distance;
	t_vector2_i	cell;
	int			i;

	pos.x = g->p.x_pos;
	pos.y = g->p.y_pos;
	angle.x = cos(x_angle);
	angle.y = sin(y_angle);
	cell = pixel2cell((int)pos.x, (int)pos.y);
	//printf("START PLAYER PIXEL: %fX, %fY\n", pos.x, pos.y);
	//printf("START PLAYER CELL: %iX, %iY\n", cell.x, cell.y);
	i = 0;
	while (1)
	{
		cell = pixel2cell((int)pos.x, (int)pos.y);
		if (g->map.map[cell.y][cell.x] == '1')
		{
	//		printf("PLAYER PIXEL: %fX, %fY\n", pos.x, pos.y);
	//		printf("PLAYER CELL: %iX, %iY\n", cell.x, cell.y);
	//		printf("HIT\n");
			break ;
		}
		pos.x += angle.x * 0.1f;
		pos.y += angle.y * 0.1f;
		i++;
		if (i > RAY_LIMIT)
		{
	//		printf("PLAYER PIXEL: %fX, %fY\n", pos.x, pos.y);
	//		printf("PLAYER CELL: %iX, %iY\n", cell.x, cell.y);
	//		printf("LIMIT\n");
			break ;
		}
	}
	distance = sqrt((pos.x - g->p.x_pos) * 2 + (pos.y - g->p.y_pos) * 2);
	return ((t_raycast_result){distance, (300) / distance});
}
