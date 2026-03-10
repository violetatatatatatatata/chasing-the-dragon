/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:49:23 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/28 16:02:18 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static int	has_textures(t_game *game)
{
	if (!game->map.no_sprite_path || !game->map.so_sprite_path
		|| !game->map.we_sprite_path || !game->map.ea_sprite_path)
		return (print_msg("Missing texture path", EXIT_FAILURE));
	return (0);
}

static int	has_colors(t_game *game)
{
	if (!game->map.rgb_floor || !game->map.rgb_celling)
		return (print_msg("Missing color configuration", EXIT_FAILURE));
	return (0);
}

static int	has_map(t_game *game)
{
	int	x;
	int	y;

	if (!game->map.map || !game->map.map[0])
		return (print_msg("Map is empty or missing", EXIT_FAILURE));
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (!ft_strchr("01NSEW", game->map.map[y][x])
				&& !ft_isspace(game->map.map[y][x]))
				return (print_msg("Invalid character in map", EXIT_FAILURE));
			x++;
		}
		y++;
	}
	return (0);
}

static int	has_walls(t_game *game)
{
	if (check_map_closed(game))
		return (print_msg("Map is not closed by walls", EXIT_FAILURE));
	return (0);
}

int	is_valid_file(t_game *game)
{
	return (!has_textures(game) && !has_colors(game) && !has_map(game)
		&& !has_walls(game));
}
