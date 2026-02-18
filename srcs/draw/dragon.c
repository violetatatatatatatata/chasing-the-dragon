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
	t_raycast_result	res;

	res = raycast(game->p.pov, 0, game);
	if (res.distance < DRAGON_DIST)
		game->texture.dragon_i->enabled = false;
	else
		game->texture.dragon_i->enabled = true;
}

void	draw_dragon(t_game *g)
{
	g->texture.dragon_i = mlx_texture_to_image(g->mlx, g->texture.dragon_t);
	drag_x = (WIDTH - g->texture.dragon_t->width) / 2;
	drag_y = (HEIGHT - g->texture.dragon_t->height) / 2;
	mlx_image_to_window(g->mlx, g->texture.dragon_i, drag_x, drag_y);
}
