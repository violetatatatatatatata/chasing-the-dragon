/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 movs.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/24 14:09:02 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2026/01/27 16:13:43 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

int	move_player(t_game *game, double new_x, double new_y)
{
	char	next_cell;
	int		grid_x;
	int		grid_y;

	grid_x = (int)new_x;
	grid_y = (int)new_y;
	next_cell = game->map.map[grid_y][grid_x];
	if (next_cell == WALL)
		return (0);
	game->p.x_pos = new_x;
	game->p.y_pos = new_y;
	return (1);
}

int handle_key_press(int keycode, t_game *game)
{
	int		input;
	double	speed;
	double	mov;

	speed = 0.1;
	input = 0.0;
	mov = 0.0;
//	if (keycode == ESC)
//		return (exit_game(game));
//	else if (keycode == SPA)
//		input = hero_shoot(game);
	if (keycode == W || keycode == A)
		mov += speed;
	else if (keycode == D || keycode == S)
		mov -= speed;
	if (keycode == W || keycode == D)
		input = move_player(game, game->p.x_pos, mov);
	else if (keycode == S || keycode == A)
		input = move_player(game, mov, game->p.y_pos);
//	if (input)
//		render_map();
	return (input);
}
