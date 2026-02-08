/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_min_map.c      								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	ft_get_map_size(t_game *g)
{
	int		i;
	int		j;
	int		max_y;
	char	**map;

	map = g->map.map;
	max_y = 0;
	i = 0;
	while (map[i])
		i++;
	g->map.max_map_y = i;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (max_y < j)
			max_y = j;
		i++;
	}
	g->map.max_map_x = max_y;
}

void	init_min_map(t_game *game)
{
	ft_get_map_size(game);
	game->map.min_map = malloc(sizeof(t_min_map));
	game->map.min_map->map_img
		= mlx_new_image(game->mlx, WIDTH_MAP, HEIGHT_MAP);
	if (!game->map.min_map->map_img
		|| (mlx_image_to_window(game->mlx,
				game->map.min_map->map_img, WIDTH - WIDTH_MAP - 10, 10) < 0))
		ft_error();
	ft_memset(game->map.min_map->map_img->pixels, 255,
		game->map.min_map->map_img->width
		* game->map.min_map->map_img->height * sizeof(int32_t));
	game->map.min_map->cell_count_x = WIDTH_MAP / CELL_PIXEL_SIZE;
	game->map.min_map->cell_count_y = HEIGHT_MAP / CELL_PIXEL_SIZE;
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
	y = 0;
	//printf("MAX: %iX, %iY\n", game->map.max_map_x, game->map.max_map_y);
	while (y < game->map.max_map_y)
	{
		x = 0;
		while (x < game->map.max_map_x)
		{
			//printf("START: %iX, %iY\n", x, y);
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
			if (px >= 0 && py >= 0 && px < WIDTH_MAP
				&& py < HEIGHT_MAP)
			{
				if (type == player
					&& (px - x * CELL_PIXEL_SIZE < out
						|| px - x * CELL_PIXEL_SIZE >= out + CELL_PLAYER_SIZE
						|| py - y * CELL_PIXEL_SIZE < out
						|| py - y * CELL_PIXEL_SIZE >= out + CELL_PLAYER_SIZE))
					mlx_put_pixel(game->map.min_map->map_img, px, py, 0x00FF00FF);
				else if (type == wall)
					mlx_put_pixel(game->map.min_map->map_img, px, py, 0x0000FFFF);
				else if (type == player)
					mlx_put_pixel(game->map.min_map->map_img, px, py, 0xFF0000FF);
				else
					mlx_put_pixel(game->map.min_map->map_img, px, py, 0x00FF00FF);
			}
			py++;
		}
		px++;
	}
}

static void	ft_init_pos(t_game *g, t_vector2 p_cell_p)
{
	t_vector2	m_str;
	t_vector2	m_end;
	int			x;
	int			y;

	//printf("CELL: %iX, %iY\n", g->map.min_map->cell_count_x, g->map.min_map->cell_count_y);
	//printf("MAP: %iX, %iY\n", g->map.max_map_x, g->map.max_map_y);
	//printf("PLAYER: %iX, %iY\n", p_cell_p.x, p_cell_p.y);
	m_str.x = g->map.min_map->cell_count_x / 2 - p_cell_p.x;
	m_str.y = g->map.min_map->cell_count_y / 2 - p_cell_p.y;
	m_end.x = g->map.min_map->cell_count_x / 2
		+ (g->map.max_map_x - p_cell_p.x);
	m_end.y = g->map.min_map->cell_count_y / 2
		+ (g->map.max_map_y - p_cell_p.y);
	//printf("START: %iX, %iY\n", m_str.x, m_str.y);
	//printf("END: %iX, %iY\n", m_end.x, m_end.y);
	//printf("\n");
	y = 0;
	while (m_str.y + y < m_end.y)
	{
		x = 0;
		while (m_str.x + x < m_end.x)
		{
			if (g->map.map[y][x] == '0')
				ft_draw_cells(m_str.x + x, m_str.y + y, empty, g);
			else if (g->map.map[y][x] == '1')
				ft_draw_cells(m_str.x + x, m_str.y + y, wall, g);
			else if (g->map.map[y][x] != ' ' && g->map.map[y][x] != '\n')
				ft_draw_cells(m_str.x + x, m_str.y + y, empty, g);
			x++;
		}
		y++;
	}
	ft_draw_cells(g->map.min_map->cell_count_x / 2,
		g->map.min_map->cell_count_y / 2, player, g);
}

static void	ft_map_size(t_game *game)
{
	t_vector2	player_cell_pos;

	player_cell_pos = ft_player_pos(game);
	ft_init_pos(game, player_cell_pos);
}

void	draw_min_map(t_game *game)
{
	ft_map_size(game);
}
