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
	char			next_cell;
	t_vector2_i		grid;

	grid = pixel2cell((int)new_x, (int)new_y);
	if (!game->map.map)
		return (0);
	if (grid.y < 0 || grid.y >= game->map.max_map_y)
		return (0);
	if (grid.x < 0 || grid.x >= game->map.max_map_x)
		return (0);
	next_cell = game->map.map[grid.y][grid.x];
	if (next_cell == WALL)
		return (0);
	game->p.x_pos = new_x;
	game->p.y_pos = new_y;
	return (1);
}

static void	recharge_spikes(t_player *p)
{
	p->spikes_left = 3;
	p->shots_left = 3;
}

int	handle_key_press(int keycode, t_game *game)
{
	int		input;
	double	speed;
	double	mov;

	input = 0;
	mov = 0.0;
	speed = speedy_gonzales(game->p);
//	if (keycode == ESC)
//		return (exit_game(game));
	if (keycode == MLX_KEY_SPACE)
	{
		if (!game->p.is_injecting)
		{
			game->p.is_injecting = true;
			game->p.inject_timer = INJECT_DURATION;
		}
	}
	if (keycode == R)
		recharge_spikes(&game->p);
	else if (keycode == MLX_KEY_W || keycode == MLX_KEY_D)
		mov += speed;
	else if (keycode == MLX_KEY_A || keycode == MLX_KEY_S)
		mov -= speed;
	if (keycode == MLX_KEY_A || keycode == MLX_KEY_D)
		input = move_player(game, game->p.x_pos + mov, game->p.y_pos);
	else if (keycode == MLX_KEY_W || keycode == MLX_KEY_S)
		input = move_player(game, game->p.x_pos, game->p.y_pos + mov);
//	if (input)
//		render_map();
	return (input);
}
