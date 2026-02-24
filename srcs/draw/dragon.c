/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:34:26 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/18 12:38:33 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	update_dragon_visibility(t_game *game)
{
	t_ray	ray;
	int		drag_x;
	int		drag_y;

	drag_x = (game->mlx->width - game->texture.dragon_t->width) / 2;
	drag_y = (game->mlx->height - game->texture.dragon_t->height) / 2;
	game->texture.dragon_i->instances[0].x = drag_x;
	game->texture.dragon_i->instances[0].y = drag_y;
	ray = cast_ray(game->p.pov, game);
	if (ray.real_dist < DRAGON_DIST)
		game->texture.dragon_i->enabled = false;
	else
		game->texture.dragon_i->enabled = true;
}

void	draw_dragon(t_game *g)
{
	int	drag_x;
	int	drag_y;

	g->texture.dragon_i = mlx_texture_to_image(g->mlx, g->texture.dragon_t);
	drag_x = (g->mlx->width - g->texture.dragon_t->width) / 2;
	drag_y = (g->mlx->height - g->texture.dragon_t->height) / 2;
	mlx_image_to_window(g->mlx, g->texture.dragon_i, drag_x, drag_y);
}
