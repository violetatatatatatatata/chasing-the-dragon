/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:12:15 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/18 15:14:54 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	init_hud_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		g->texture.hud_heroin_i[i] = mlx_texture_to_image(g->mlx, g->texture.hud_heroin_t[i]);
		mlx_image_to_window(g->mlx, g->texture.hud_heroin_i[i], 20, HEIGHT - 150);
		g->texture.hud_heroin_i[i]->enabled = false;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		g->texture.hud_smack_i[i] = mlx_texture_to_image(g->mlx, g->texture.hud_smack_t[i]);
		mlx_image_to_window(g->mlx, g->texture.hud_smack_i[i], WIDTH - 300, HEIGHT - 150);
		g->texture.hud_smack_i[i]->enabled = false;
		i++;
	}
}

void	update_hud(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i == (int)game->p.shots_left)
			game->texture.hud_heroin_i[i]->enabled = true;
		else
			game->texture.hud_heroin_i[i]->enabled = false;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (i == (int)game->p.spikes_left)
			game->texture.hud_smack_i[i]->enabled = true;
		else
			game->texture.hud_smack_i[i]->enabled = false;
		i++;
	}
}
