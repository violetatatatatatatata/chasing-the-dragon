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
	game->min_map->map_img->instances[0].x = w - WIDTH_MAP - 10;
}

void	ft_update_draw(void *g)
{
	t_game		*game;

	game = (t_game *)g;
	//printf("WIDTH: %d | HEIGHT: %d\n", game->mlx->width, game->mlx->height);
	draw_min_map(game);
}

// Cambiar el NULL de mlx_hook_update
int	draw(void)
{
	t_game		game;

	mlx_set_setting(MLX_MAXIMIZED, true);
	game.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game.mlx)
		ft_error();
	game.max_map_x = 20;
	game.max_map_y = 20;
	game.map = ft_create_map(game.max_map_x, game.max_map_y);
	init_min_map(&game);
	mlx_resize_hook(game.mlx, ft_on_resize, &game);
	mlx_loop_hook(game.mlx, ft_update_draw, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
