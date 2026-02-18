/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:36:47 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/18 15:22:29 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	draw_player(t_game *g)
{
	t_vector2_i	player_pos;
	int	arms_x;
	int	arms_y;
	
	g->p.is_injecting = true;
	g->p.inject_timer = 0;
	g->texture.arms_idle_i = mlx_texture_to_image(g->mlx, g->texture.arms_idle_t);
	g->texture.arms_inject_i = mlx_texture_to_image(g->mlx, g->texture.arms_inject_t);
	arms_x = (WIDTH - g->texture.arms_idle_t->width) / 2;
	arms_y = HEIGHT - g->texture.arms_idle_t->height;
	mlx_image_to_window(g->mlx, g->texture.arms_idle_i, arms_x, arms_y);
	mlx_image_to_window(g->mlx, g->texture.arms_inject_i, arms_x, arms_y);
	g->texture.arms_idle_i->enabled = true;
	g->texture.arms_inject_i->enabled = false;
	player_pos = get_player_pixel_pos(g);
	g->p.x_pos = player_pos.x + CELL_PIXEL_SIZE / 2;
	g->p.y_pos = player_pos.y + CELL_PIXEL_SIZE / 2;
}

void	update_arms_animation(t_game *game)
{
	if (game->p.is_injecting)
	{
		game->texture.arms_inject_i->enabled = true;
		game->texture.arms_idle_i->enabled = false;
		game->p.inject_timer--;
		if (game->p.inject_timer <= 0)
			game->p.is_injecting = false;
	}
	else
	{
		game->texture.arms_idle_i->enabled = true;
		game->texture.arms_inject_i->enabled = false;
	}
}

