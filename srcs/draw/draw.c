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

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	game = (t_game *)param;
	handle_key_press(keydata.key, game);
	handle_key_press_rot(keydata.key, game);
}

void	ft_update_draw(void *g)
{
	t_game		*game;

	game = (t_game *)g;
	draw_roof_floor(game);
	render_frame(game);
	update_arms_animation(game);
	update_dragon_visibility(game);
}

static void	ft_init(t_game *g)
{
	t_vector2_i	player_pos;

	load_sprites(g);
	g->texture.ea_i = mlx_texture_to_image(g->mlx, g->texture.ea_t);
	g->texture.we_i = mlx_texture_to_image(g->mlx, g->texture.we_t);
	g->texture.so_i = mlx_texture_to_image(g->mlx, g->texture.so_t);
	g->texture.no_i = mlx_texture_to_image(g->mlx, g->texture.no_t);
	get_map_size(g);
	player_pos = get_player_pixel_pos(g);
	g->p.x_pos = player_pos.x + CELL_PIXEL_SIZE / 2;
	g->p.y_pos = player_pos.y + CELL_PIXEL_SIZE / 2;
}

int	draw(t_game game)
{
	game.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!game.mlx)
		ft_error();
	init_roof_floor(&game);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
		ft_error();
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	ft_init(&game);
	render_frame(&game);
	draw_dragon(&game);
	draw_player(&game);
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_close_hook(game.mlx, clean_game, &game);
	mlx_loop_hook(game.mlx, ft_update_draw, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
