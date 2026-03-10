/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_movement.c		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

static t_directions	get_directions(double angle)
{
	t_directions	dir;

	dir.forward_x = cos(angle);
	dir.forward_y = -sin(angle);
	dir.right_x = sin(angle);
	dir.right_y = cos(angle);
	return (dir);
}

static t_vector2_f	get_movement_from_dir(int keycode, double speed,
	t_directions dir)
{
	t_vector2_f	move;

	move.x = 0;
	move.y = 0;
	if (keycode == MLX_KEY_W)
	{
		move.x = dir.forward_x * speed;
		move.y = dir.forward_y * speed;
	}
	else if (keycode == MLX_KEY_S)
	{
		move.x = -dir.forward_x * speed;
		move.y = -dir.forward_y * speed;
	}
	else if (keycode == MLX_KEY_D)
	{
		move.x = dir.right_x * speed;
		move.y = dir.right_y * speed;
	}
	else if (keycode == MLX_KEY_A)
	{
		move.x = -dir.right_x * speed;
		move.y = -dir.right_y * speed;
	}
	return (move);
}

t_vector2_f	get_movement(int keycode, double angle, double speed)
{
	t_directions	dir;

	dir = get_directions(angle);
	return (get_movement_from_dir(keycode, speed, dir));
}
