/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_player_pixel_pos.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

/// @brief Gets player pos in the cell
/// @param game 
/// @return Returns player pos cell
static t_vector2	ft_player_pos(t_game *game)
{
	int			x;
	int			y;
	t_vector2	pos;

	pos.x = 0;
	pos.y = 0;
	y = 0;
	printf("SIZE: %iX, %iY\n", game->map.max_map_x, game->map.max_map_y);
	while (y < game->map.max_map_y)
	{
		x = 0;
		while (x < game->map.max_map_x)
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E'
				|| game->map.map[y][x] == 'W' || game->map.map[y][x] == 'S')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
	return (pos);
}

t_vector2	get_player_pixel_pos(t_game *game)
{
	t_vector2	player_cell;

	player_cell = ft_player_pos(game);
	return (cell2pixel(player_cell.x, player_cell.y));
}
