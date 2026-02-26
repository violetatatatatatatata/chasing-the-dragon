/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:33:50 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/26 16:41:58 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	update_dragon_visibility(t_game *g)
{
	g->texture.dragon_i->instances[0].enabled = !g->texture.is_joan;
	g->texture.joan_i->instances[0].enabled = g->texture.is_joan;
}

void	draw_dragon(t_game *g)
{
	int	x;
	int	y;

	g->texture.dragon_i = mlx_texture_to_image(g->mlx, g->texture.dragon_t);
	g->texture.joan_i = mlx_texture_to_image(g->mlx, g->texture.joan_t);
	x = (g->mlx->width - g->texture.dragon_t->width) / 2;
	y = (g->mlx->height - g->texture.dragon_t->height) / 2;
	mlx_image_to_window(g->mlx, g->texture.dragon_i, x, y);
	mlx_image_to_window(g->mlx, g->texture.joan_i, x, y);
	g->texture.joan_i->instances[0].enabled = false;
}
