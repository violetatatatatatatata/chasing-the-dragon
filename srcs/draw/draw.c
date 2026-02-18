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

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	game = (t_game *)param;
	handle_key_press(keydata.key, game);
}

void	ft_update_draw(void *g)
{
	t_game		*game;

	game = (t_game *)g;
	render_frame(game);
	update_arms_animation(game);
	update_dragon_visibility(game);
	//draw_min_map(game);
}

static void	ft_init(t_game *g)
{
	load_sprites(g);
	g->texture.ea_i = mlx_texture_to_image(g->mlx, g->texture.ea_t);
	g->texture.we_i = mlx_texture_to_image(g->mlx, g->texture.we_t);
	g->texture.so_i = mlx_texture_to_image(g->mlx, g->texture.so_t);
	g->texture.no_i = mlx_texture_to_image(g->mlx, g->texture.no_t);
	draw_dragon(g);
	draw_player(g);
}

int	draw(t_game game)
{
	game.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!game.mlx)
		ft_error();
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
		ft_error();
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	init_min_map(&game);
	ft_init(&game);
	render_frame(&game);
	draw_min_map(&game);
	mlx_resize_hook(game.mlx, ft_on_resize, &game);
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_loop_hook(game.mlx, ft_update_draw, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
