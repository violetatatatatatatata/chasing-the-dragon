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

void	init_min_map(t_game *game)
{
	get_map_size(game);
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
	game->map.min_map->player_cell = get_player_cell_pos(game);
}

static void	ft_draw_pixel(int x, int y, t_type type, t_game *game)
{
	t_vector2_i	p_pos;

	if (type == wall)
		mlx_put_pixel(game->map.min_map->map_img, x, y, 0x0000FFFF);
	else if (type == player)
	{
		p_pos.x = -CELL_PLAYER_SIZE / 2;
		while (p_pos.x <= CELL_PLAYER_SIZE / 2)
		{
			p_pos.y = -CELL_PLAYER_SIZE / 2;
			while (p_pos.y <= CELL_PLAYER_SIZE / 2)
			{
				mlx_put_pixel(game->map.min_map->map_img,
					WIDTH_MAP / 2 + p_pos.x,
					HEIGHT_MAP / 2 + p_pos.y, 0xFF0000FF);
				p_pos.y++;
			}
			//printf("PRINT: %iN, %iX, %iY\n", p_pos.x, x + p_pos.x, y + p_pos.y);
			p_pos.x++;
		}
		//printf("PRINT PLAYER: %fX, %fY\n", game->p.x_pos, game->p.y_pos);
		//printf("\n");
	}
	else
		mlx_put_pixel(game->map.min_map->map_img, x, y, 0x00FF00FF);

}

static void	ft_process_pixel(t_game *g, int abs_x, int abs_y,
				t_vector2_i origin_cell)
{
	t_vector2_i	cell_pos;
	int			map_row;
	int			map_col;
	char		cell;

	cell_pos = pixel2cell(abs_x + g->map.min_map->player_offset.x, abs_y + g->map.min_map->player_offset.y);
//	if (abs_x >= 213.0f && abs_y >= 213.0f && abs_x < 219.0f && abs_y < 219.0f)
//	{
//		printf("CELL POS: %iX, %iY\n\n", cell_pos.x, cell_pos.y);
//	}
	map_row = cell_pos.y - origin_cell.y;
	map_col = cell_pos.x - origin_cell.x;
	if (map_row < 0 || map_row >= g->map.max_map_y
		|| map_col < 0 || map_col >= g->map.max_map_x)
		return ;
	cell = g->map.map[map_row][map_col];
	if (cell == '0')
		ft_draw_pixel(abs_x, abs_y, empty, g);
	else if (cell == '1')
		ft_draw_pixel(abs_x, abs_y, wall, g);
	else if (cell != ' ' && cell != '\n' && cell != '\0')
		ft_draw_pixel(abs_x, abs_y, empty, g);
}

void	ft_draw_player(t_game *g, t_vector2_i m_str)
{
	int	px;
	int	py;

	px = g->p.x_pos + m_str.x;
	py = g->p.y_pos + m_str.y;
	if (px >= 0 && px < WIDTH_MAP && py >= 0 && py < HEIGHT_MAP)
		ft_draw_pixel(px, py, player, g);
}

void	ft_draw_minimap_area(t_game *g, t_vector2_i m_str,
				t_vector2_i m_end, t_vector2_i origin_cell)
{
	int	offset_y;
	int	offset_x;
	int	abs_x;
	int	abs_y;

	offset_y = 0;
	while (m_str.y + offset_y < m_end.y)
	{
		offset_x = 0;
		while (m_str.x + offset_x < m_end.x)
		{
			abs_x = m_str.x + offset_x;
			abs_y = m_str.y + offset_y;
			if (abs_x >= 0 && abs_x < WIDTH_MAP
				&& abs_y >= 0 && abs_y < HEIGHT_MAP)
				ft_process_pixel(g, abs_x, abs_y, origin_cell);
			offset_x++;
		}
		//printf("CELL POS: %iX, %iY\n\n", pixel2cell(abs_x, abs_y).x - origin_cell.x, pixel2cell(abs_x, abs_y).y - origin_cell.y);
		offset_y++;
	}
}

static void	ft_init_pos(t_game *g)
{
	t_vector2_i	m_str;
	t_vector2_i	m_end;
	t_vector2_i	origin_cell;

	ft_memset(g->map.min_map->map_img->pixels, 255,
		g->map.min_map->map_img->width
		* g->map.min_map->map_img->height * sizeof(int32_t));
	g->map.min_map->player_cell = pixel2cell(g->p.x_pos, g->p.y_pos);
//	printf("CELL: %iX, %iY\n", g->map.min_map->cell_count_x,
	//	g->map.min_map->cell_count_y);
//	printf("MAP: %iX, %iY\n", g->map.max_map_x, g->map.max_map_y);
//	printf("PLAYER POS: %fX, %fY\n", g->p.x_pos, g->p.y_pos);
//	printf("PLAYER CELL: %iX, %iY\n",
	//	g->map.min_map->player_cell.x, g->map.min_map->player_cell.y);
	g->map.min_map->player_offset = cell2pixel(g->map.min_map->player_cell.x,
			g->map.min_map->player_cell.y);
	g->map.min_map->player_offset = (t_vector2_i){g->p.x_pos - g->map.min_map->player_offset.x,
		g->p.y_pos - g->map.min_map->player_offset.y};
	m_str = (t_vector2_i){g->map.min_map->player_cell.x * CELL_PIXEL_SIZE,
		g->map.min_map->player_cell.y * CELL_PIXEL_SIZE};
//	printf("PLAYER CELL 2: %iX, %iY\n", g->map.min_map->player_cell.x, g->map.min_map->player_cell.y);
//	printf("START 1: %iX, %iY\n", m_str.x, m_str.y);
	m_str.x = WIDTH_MAP / 2 - g->map.min_map->player_offset.x - m_str.x;
	m_str.y = HEIGHT_MAP / 2 - g->map.min_map->player_offset.y - m_str.y;
	m_end = (t_vector2_i){(g->map.max_map_x
			- g->map.min_map->player_cell.x - 1) * CELL_PIXEL_SIZE,
		(g->map.max_map_y
			- g->map.min_map->player_cell.y - 1) * CELL_PIXEL_SIZE};
//	printf("END 1: %iX, %iY\n", m_end.x, m_end.y);
	m_end.x += WIDTH_MAP / 2 + CELL_PIXEL_SIZE - g->map.min_map->player_offset.x;
	m_end.y += HEIGHT_MAP / 2 + CELL_PIXEL_SIZE - g->map.min_map->player_offset.y;
//	printf("START 2: %iX, %iY\n", m_str.x, m_str.y);
//	printf("END 2: %iX, %iY\n", m_end.x, m_end.y);
//	printf("\n");
	origin_cell = pixel2cell(m_str.x + g->map.min_map->player_offset.x,
			m_str.y + g->map.min_map->player_offset.y);
//	printf("ORIGIN CELL 2: %iX, %iY\n", origin_cell.x, origin_cell.y);
	ft_draw_minimap_area(g, m_str, m_end, origin_cell);
	ft_draw_player(g, m_str);
	mlx_put_pixel(g->map.min_map->map_img, m_str.x, m_str.y, 0xFF0000FF);
//	printf("START PIXEL: %iX, %iY\n", m_str.x + g->map.min_map->player_cell.x, m_str.y + g->map.min_map->player_cell.y);
//	printf("START 3: %iX, %iY\n", pixel2cell(m_str.x, m_str.y).x, pixel2cell(m_str.x, m_str.y).y);
	mlx_put_pixel(g->map.min_map->map_img, m_str.x + CELL_PIXEL_SIZE, m_str.y + CELL_PIXEL_SIZE, 0xFF0000FF);
//	printf("START 4: %iX, %iY\n", pixel2cell(m_str.x + CELL_PIXEL_SIZE - 1, m_str.y + CELL_PIXEL_SIZE - 1).x, pixel2cell(m_str.x, m_str.y).y);
//	printf("START 5: %iX, %iY\n", pixel2cell(m_str.x + CELL_PIXEL_SIZE, m_str.y + CELL_PIXEL_SIZE).x, pixel2cell(m_str.x, m_str.y).y);
	mlx_put_pixel(g->map.min_map->map_img, m_end.x - CELL_PIXEL_SIZE, m_end.y - CELL_PIXEL_SIZE, 0xFF0000FF);
}

static void	ft_map_size(t_game *game)
{
	ft_init_pos(game);
}

void	draw_min_map(t_game *game)
{
	ft_map_size(game);
}
