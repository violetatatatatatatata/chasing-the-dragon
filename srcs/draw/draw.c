/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw.c      										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	ft_on_resize(int32_t w, int32_t h, void *param)
{
	t_game	*game;

	(void)h;
	game = param;
	if (game->map.min_map && game->map.min_map->map_img)
		game->map.min_map->map_img->instances[0].x = w - WIDTH_MAP - 10;
}

void	ft_update_draw(void *g)
{
	t_game		*game;

	game = (t_game *)g;
	draw_min_map(game);
}

int	draw(t_game game)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	game.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game.mlx)
		ft_error();
	init_min_map(&game);
	mlx_resize_hook(game.mlx, ft_on_resize, &game);
	mlx_loop_hook(game.mlx, ft_update_draw, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
