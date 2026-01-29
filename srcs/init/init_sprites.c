/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:58:41 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/29 16:28:16 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	draw_colors(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	if (game->map->rgb_celling)
		ceiling_color = *game->map->rgb_celling;
	else
		ceiling_color = 000000;
	if (game->map->rgb_floor)
		floor_color = *game->map->rgb_floor;
	else
		floor_color = 183F23;
	y = 0;
	/*
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
	*/
}

static void	clean_sprites(t_game *game)
{
	if (game->no)
		mlx_delete_(game->no);
	if (game->so)
		mlx_delete_(game->so);
	if (game->we)
		mlx_delete_(game->we);
	if (game->ea)
		mlx_delete_(game->ea);
}

int	load_sprites(t_game *game)
{
	game->no = mlx_load_png(game->map->no_sprite_path);
	game->so = mlx_load_png(game->map->so_sprite_path);
	game->we = mlx_load_png(game->map->we_sprite_path);
	game->ea = mlx_load_png(game->map->ea_sprite_path);
	if (!game->no || !game->so || !game->we || !game->ea)
	{
		clean_s(game);
		return (print_msg("Failed to load sprites", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
