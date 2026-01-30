/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:58:41 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/30 11:36:31 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	draw_colors(t_game *game)
{
//	uint32_t	x;
	uint32_t	y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	if (game->map.rgb_celling)
		ceiling_color = *game->map.rgb_celling;
	else
		ceiling_color = 0x183F23FF;
	if (game->map.rgb_floor)
		floor_color = *game->map.rgb_floor;
	else
		floor_color = 0x183F23FF;
	y = 0;
	(void)floor_color;
	(void)ceiling_color;
	(void)y;
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
/*
static void	clean_sprites(t_game *game)
{
	if (game->texture.no)
		mlx_delete_(game->texture.no);
	if (game->texture.so)
		mlx_delete_(game->texture.so);
	if (game->texture.we)
		mlx_delete_(game->texture.we);
	if (game->texture.ea)
		mlx_delete_(game->texture.ea);
}
*/
int	load_sprites(t_game *game)
{
	game->texture.no = mlx_load_png(game->map.no_sprite_path);
	game->texture.so = mlx_load_png(game->map.so_sprite_path);
	game->texture.we = mlx_load_png(game->map.we_sprite_path);
	game->texture.ea = mlx_load_png(game->map.ea_sprite_path);
	if (!game->texture.no || !game->texture.so || !game->texture.we || !game->texture.ea)
	{
	//	clean_sprites(game);
		return (print_msg("Failed to load sprites", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
