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

static void	recharge_spikes(t_player *p)
{
	p->spikes_left = 3;
	p->shots_left = 3;
}

static int	handle_action_keys(int keycode, t_game *game)
{
	if (keycode == MLX_KEY_J)
		game->texture.is_joan = !game->texture.is_joan;
	if (keycode == MLX_KEY_SPACE)
	{
		game->p.shots_left--;
		if (game->p.shots_left == 0 && game->p.spikes_left > 0)
		{
			game->p.spikes_left--;
			game->p.shots_left = 3;
		}
		if (!game->p.is_injecting)
		{
			game->p.is_injecting = true;
			game->p.inject_timer = INJECT_DURATION;
		}
		return (1);
	}
	if (keycode == MLX_KEY_R)
	{
		recharge_spikes(&game->p);
		return (1);
	}
	return (0);
}

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

int	handle_key_press(int keycode, t_game *game)
{
	double		speed;
	t_vector2_f	move;
	double		new_x;
	double		new_y;

	if (handle_action_keys(keycode, game))
		return (0);
	speed = speedy_gonzales(game->p);
	move = get_movement(keycode, angle2rad(game->p.pov), speed);
	if (move.x == 0 && move.y == 0)
		return (0);
	new_x = game->p.x_pos + move.x;
	new_y = game->p.y_pos + move.y;
	return (move_player(game, new_x, new_y));
}
