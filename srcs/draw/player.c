/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:36:47 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/26 16:22:41 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	draw_player(t_game *g)
{
	int			arms_x;
	int			arms_y;

	g->p.is_injecting = true;
	g->p.inject_timer = 0;
	g->texture.arms_idle_i = mlx_texture_to_image(g->mlx,
			g->texture.arms_idle_t);
	g->texture.arms_inject_i = mlx_texture_to_image(g->mlx,
			g->texture.arms_inject_t);
	arms_x = (g->mlx->width - g->texture.arms_idle_t->width) / 2;
	arms_y = g->mlx->height - g->texture.arms_idle_t->height;
	mlx_image_to_window(g->mlx, g->texture.arms_idle_i, arms_x, arms_y);
	mlx_image_to_window(g->mlx, g->texture.arms_inject_i, arms_x, arms_y);
	g->texture.arms_idle_i->enabled = true;
	g->texture.arms_inject_i->enabled = false;
}

void	update_arms_animation(t_game *game)
{
	int			arms_x;
	int			arms_y;

	arms_x = (game->mlx->width - game->texture.arms_idle_t->width) / 2;
	arms_y = game->mlx->height - game->texture.arms_idle_t->height;
	game->texture.arms_idle_i->instances[0].x = arms_x;
	game->texture.arms_idle_i->instances[0].y = arms_y;
	game->texture.arms_inject_i->instances[0].x = arms_x;
	game->texture.arms_inject_i->instances[0].y = arms_y;
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

void init_ui_images(t_game *game)
{
    int i;
    int sw = 255;
    int sh = 255;

    i = -1;
    while (++i < 5)
    {
        game->texture.shots_i[i] = mlx_texture_to_image(game->mlx, game->texture.shots_t[i]);
        mlx_image_to_window(game->mlx, game->texture.shots_i[i], WIDTH - sw, HEIGHT - sh);
        game->texture.shots_i[i]->instances[0].enabled = false;
    }
    i = -1;
    while (++i < 4)
    {
        game->texture.spikes_i[i] = mlx_texture_to_image(game->mlx, game->texture.spikes_t[i]);
        mlx_image_to_window(game->mlx, game->texture.spikes_i[i], WIDTH - sw, 0);
        game->texture.spikes_i[i]->instances[0].enabled = false;
    }
}
