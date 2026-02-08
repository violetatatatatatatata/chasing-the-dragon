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
	t_vector2	player_pos;

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
	player_pos = get_player_pixel_pos(game);
	game->p.x_pos = player_pos.x;
	game->p.y_pos = player_pos.y;
}

static void	ft_draw_pixel(int x, int y, t_type type, t_game *game)
{
	t_vector2	p_pos;

	if (type == wall)
		mlx_put_pixel(game->map.min_map->map_img, x, y, 0x0000FFFF);
	else if (type == player)
	{
		p_pos.x = CELL_PLAYER_SIZE / 2;
		while (p_pos.x < CELL_PIXEL_SIZE - CELL_PLAYER_SIZE / 2)
		{
			p_pos.y = CELL_PLAYER_SIZE / 2;
			while (p_pos.y < CELL_PIXEL_SIZE - CELL_PLAYER_SIZE / 2)
			{
				mlx_put_pixel(game->map.min_map->map_img, x + p_pos.x,
					y + p_pos.y, 0xFF0000FF);
				p_pos.y++;
			}
			p_pos.x++;
		}
	}
	else
		mlx_put_pixel(game->map.min_map->map_img, x, y, 0x00FF00FF);

}

static void	ft_init_pos(t_game *g)
{
	t_vector2	m_str;
	t_vector2	m_end;
	t_vector2	m_size;
	t_vector2	cell_pos;
	int			x;
	int			y;

	ft_memset(g->map.min_map->map_img->pixels, 255,
		g->map.min_map->map_img->width
		* g->map.min_map->map_img->height * sizeof(int32_t));
	/*printf("CELL: %iX, %iY\n", g->map.min_map->cell_count_x, g->map.min_map->cell_count_y);
	printf("MAP: %iX, %iY\n", g->map.max_map_x, g->map.max_map_y);
	printf("PLAYER POS: %fX, %fY\n", g->p.x_pos, g->p.y_pos);
	printf("PLAYER CELL: %iX, %iY\n", pixel2cell(g->p.x_pos, g->p.y_pos).x, pixel2cell(g->p.x_pos, g->p.y_pos).y);*/
	m_str = cell2pixel(g->map.min_map->cell_count_x / 2,
			g->map.min_map->cell_count_y / 2);
	m_str.x -= g->p.x_pos;
	m_str.y -= g->p.y_pos;
	m_end = cell2pixel(g->map.min_map->cell_count_x / 2,
			g->map.min_map->cell_count_y / 2);
	m_size = cell2pixel(g->map.max_map_x, g->map.max_map_y);
	m_end.x += (m_size.x - g->p.x_pos);
	m_end.y += (m_size.y - g->p.y_pos);
	/*printf("START: %iX, %iY\n", m_str.x, m_str.y);
	printf("END: %iX, %iY\n", m_end.x, m_end.y);
	printf("\n");*/
	y = 0;
	while (m_str.y + y < m_end.y)
	{
		x = 0;
		while (m_str.x + x < m_end.x)
		{
			if (m_str.x + x < 0 || m_str.x + x >= WIDTH_MAP
				|| m_str.y + y < 0 || m_str.y + y >= HEIGHT_MAP)
				break ;
			cell_pos = pixel2cell(m_str.x + x, m_str.y + y);
			//printf("POS: %iX, %iY\n", cell_pos.x, cell_pos.y);
			if (g->map.map[cell_pos.y - pixel2cell(m_str.x, m_str.y).y]
				[cell_pos.x - pixel2cell(m_str.x, m_str.y).x] == '0')
				ft_draw_pixel(m_str.x + x, m_str.y + y, empty, g);
			else if (g->map.map[cell_pos.y - pixel2cell(m_str.x, m_str.y).y]
				[cell_pos.x - pixel2cell(m_str.x, m_str.y).x] == '1')
				ft_draw_pixel(m_str.x + x, m_str.y + y, wall, g);
			else if (g->map.map[cell_pos.y - pixel2cell(m_str.x, m_str.y).y]
				[cell_pos.x - pixel2cell(m_str.x, m_str.y).x] != ' '
				&& g->map.map[cell_pos.y - pixel2cell(m_str.x, m_str.y).y]
				[cell_pos.x - pixel2cell(m_str.x, m_str.y).x] != '\n'
				&& g->map.map[cell_pos.y - pixel2cell(m_str.x, m_str.y).y]
				[cell_pos.x - pixel2cell(m_str.x, m_str.y).x] != '\0')
				ft_draw_pixel(m_str.x + x, m_str.y + y, empty, g);
			x++;
		}
		y++;
	}
	ft_draw_pixel(g->p.x_pos + m_str.x,
		g->p.y_pos + m_str.y, player, g);
}

static void	ft_map_size(t_game *game)
{
	ft_init_pos(game);
}

void	draw_min_map(t_game *game)
{
	ft_map_size(game);
}
