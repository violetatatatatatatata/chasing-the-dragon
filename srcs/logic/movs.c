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

int move_player(t_map *m, double new_x, double new_y)
{
	char	next_cell;

	next_cell = m->map[new_y][new_x];
	if (next_cell == WALL)
		return (0);
	map.x_pos = new_x;
	map.y_pos = new_y;
	return (1);
}

int handle_key_press(int keycode, t_game *game)
{
	int		input;
	double	mov;

	input = 0;
	if (keycode == ESC)
		return (exit_game(game));
	else if (keycode == SPA)
		input = hero_shoot(game);
	else if (keycode == W || keycode == A)
		mov += 0.01;
	else if (keycode == D || keycode == S)
		mov -= 0.01;
	if (keycode == W || keycode == D)
		input = move_player(game->map, game->map.x_pos, mov);
	else if (keycode == S || keycode == A)
		input = move_player(game->map, mov, game->map.y_pos);
	if (input)
		render_map();
	return (input);
}
