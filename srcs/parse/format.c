/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:49:23 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/27 18:39:22 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static int	has_textures(t_game *game)
{
	if (!game->no_sprite_path || !game->so_sprite_path || \
		!game->we_sprite_path || !game->ea_sprite_path)
		return (print_msg("Missing texture path", 0));
	return (1);
}

static int	has_colors(t_game *game)
{
	if (!game->rgb_floor || !game->rgb_celling)
		return (print_msg("Missing color configuration", 0));
	return (1);
}

static int	has_map(t_game *game)
{
	int	x;
	int	y;

	if (!game->map || !game->map[0])
		return (print_msg("Map is empty or missing", 0));
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!ft_strchr("01NSEW ", game->map[y][x]))
				return (print_msg("Invalid character in map", 0));
			x++;
		}
		y++;
	}
	return (1);
}

static int	has_walls(t_game *game)
{
	if (check_map_closed(game))
		return (print_msg("Map is not closed by walls", 0));
	return (1);
}

int	is_valid_file(t_game *game)
{
	return (has_textures(game) && has_colors(game) && has_map(game) \
			&& has_walls(game));
}
