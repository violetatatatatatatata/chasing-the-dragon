/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_min_map.c      								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	init_min_map(t_game *game)
{
	game->min_map = malloc(sizeof(t_min_map));
	game->min_map->map_img
		= mlx_new_image(game->mlx, WIDTH_MAP, HEIGHT_MAP);
	if (!game->min_map->map_img
		|| (mlx_image_to_window(game->mlx,
				game->min_map->map_img, WIDTH - WIDTH_MAP - 10, 10) < 0))
		ft_error();
	ft_memset(game->min_map->map_img->pixels, 255,
		game->min_map->map_img->width
		* game->min_map->map_img->height * sizeof(int32_t));
	game->min_map->cell_count_x = WIDTH_MAP / CELL_PIXEL_SIZE;
	game->min_map->cell_count_y = HEIGHT_MAP / CELL_PIXEL_SIZE;
}


/// @brief Gets player pos in the cell
/// @param game 
/// @return Returns player pos cell
t_vector2	ft_player_pos(t_game *game)
{
	int			x;
	int			y;
	t_vector2	pos;

	pos.x = 0;
	pos.y = 0;
	x = 0;
	while (x < game->max_map_x)
	{
		y = 0;
		while (y < game->max_map_y)
		{
			if (game->map[x][y] == 'N' || game->map[x][y] == 'E'
				|| game->map[x][y] == 'O' || game->map[x][y] == 'S')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
			y++;
		}
		x++;
	}
	return (pos);
}

static void	ft_draw_cells(int x, int y, t_type type, t_game *game)
{
	int	px;
	int	py;
	int	ex;
	int	ey;
	int	out;

	out = (CELL_PIXEL_SIZE - CELL_PLAYER_SIZE) / 2;
	px = x * CELL_PIXEL_SIZE;
	py = y * CELL_PIXEL_SIZE;
	ex = px + CELL_PIXEL_SIZE;
	ey = py + CELL_PIXEL_SIZE;
	while (px < ex)
	{
		py = y * CELL_PIXEL_SIZE;
		while (py < ey)
		{
			if (px >= 0 && py >= 0 && px < game->mlx->width
				&& py < game->mlx->height)
			{
				if (type == player
					&& (px - x * CELL_PIXEL_SIZE < out
						|| px - x * CELL_PIXEL_SIZE >= out + CELL_PLAYER_SIZE
						|| py - y * CELL_PIXEL_SIZE < out
						|| py - y * CELL_PIXEL_SIZE >= out + CELL_PLAYER_SIZE))
					mlx_put_pixel(game->min_map->map_img, px, py, 0x00FF00FF);
				else if (type == wall)
					mlx_put_pixel(game->min_map->map_img, px, py, 0x0000FFFF);
				else if (type == player)
					mlx_put_pixel(game->min_map->map_img, px, py, 0xFF0000FF);
				else
					mlx_put_pixel(game->min_map->map_img, px, py, 0x00FF00FF);
			}
			py++;
		}
		px++;
	}
}

static void	ft_map_size(t_game *game)
{
	t_vector2	player_cell_pos;
	t_vector2	cell_start;
	t_vector2	map_start;
	int			x;
	int			y;

	player_cell_pos = ft_player_pos(game);
	cell_start.x = player_cell_pos.x - game->max_map_x / 2;
	cell_start.y = player_cell_pos.y - game->max_map_y / 2;
	if (cell_start.x < 0)
		cell_start.x = 0;
	if (cell_start.y < 0)
		cell_start.y = 0;
	printf("MAP MAX %i CELL COUNT %i MAP START %i PLAYER POS %i\n", game->max_map_x, game->min_map->cell_count_x, cell_start.x, player_cell_pos.x);
	if (cell_start.x > game->max_map_x - game->min_map->cell_count_x)
		cell_start.x = game->max_map_x - game->min_map->cell_count_x;
	if (cell_start.y > game->max_map_y - game->min_map->cell_count_y)
		cell_start.y = game->max_map_y - game->min_map->cell_count_y;
	x = 0;
	if (game->min_map->cell_count_x > game->max_map_x)
		x = (game->min_map->cell_count_x - game->max_map_x) / 2;
	while (x < game->min_map->cell_count_x)
	{
		y = 0;
		if (game->min_map->cell_count_y > game->max_map_y)
			y = (game->min_map->cell_count_y - game->max_map_y) / 2;
		while (y < game->min_map->cell_count_y)
		{
			printf("CELL START: %i, X: %i\n", cell_start.x, x);
			map_start.x = cell_start.x + x;
			map_start.y = cell_start.y + y;
			printf("SIZE: %iX, %iY\n", map_start.x, map_start.y);
			if (game->map[map_start.x][map_start.y] == '0')
				ft_draw_cells(x, y, empty, game);
			else if (game->map[map_start.x][map_start.y] == '1')
				ft_draw_cells(x, y, wall, game);
			y++;
		}
		x++;
	}
	ft_draw_cells(player_cell_pos.x - cell_start.x, player_cell_pos.y - cell_start.y,
		player, game);
}

void	draw_min_map(t_game *game)
{
	ft_map_size(game);
}
