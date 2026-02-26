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
	if (keycode == MLX_KEY_LEFT)
		game->p.pov += ROTATION_SPEED;
	if (keycode == MLX_KEY_RIGHT)
		game->p.pov -= ROTATION_SPEED;
	game->p.pov += 360 * (game->p.pov < 0);
	game->p.pov -= 360 * (game->p.pov > 360);
	return (0);
}
