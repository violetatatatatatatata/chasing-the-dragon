/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 rotation.c  		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

int	handle_key_press_rot(int keycode, t_game *game)
{
	game->p.pov += !((keycode == MLX_KEY_LEFT) && (keycode == MLX_KEY_RIGHT))
		* (keycode == MLX_KEY_LEFT) * ROTATION_SPEED;
	game->p.pov -= !((keycode == MLX_KEY_LEFT) && (keycode == MLX_KEY_RIGHT))
		* (keycode == MLX_KEY_RIGHT) * ROTATION_SPEED;
	game->p.pov += 360 * (game->p.pov < 0);
	game->p.pov -= 360 * (game->p.pov > 360);
	return (0);
}
