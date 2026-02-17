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

void	update_dragon_visibility(t_game *game)
{
	t_raycast_result	res;

	res = raycast(game->p.pov, 0, game);
	if (res.distance < DRAGON_DIST)
		game->texture.dragon_i->enabled = false;
	else
		game->texture.dragon_i->enabled = true;
}

void	update_arms_animation(t_game *game)
{
	if (game->p.is_injecting)
	{
		game->texture.arms_inject_i->enabled = true;
		game->texture.arms_idle_i->enabled = false;
		game->p.inject_timer--;
		if (game->p.inject_timer <= 0)
			game->p.is_injecting = false;
	}
	else
	{
		game->texture.arms_idle_i->enabled = true;
		game->texture.arms_inject_i->enabled = false;
	}
}

void	ft_update_draw(void *g)
{
	t_game		*game;

	game = (t_game *)g;
	render_frame(game);
	update_dragon_visibility(game);
	update_arms_animation(game);
	draw_min_map(game);
}

static void	ft_init(t_game *g)
{
	t_vector2_i	player_pos;
	int			arms_x;
	int			arms_y;
	int			drag_x;
	int			drag_y;

	load_sprites(g);
	g->texture.ea_i = mlx_texture_to_image(g->mlx, g->texture.ea_t);
	g->texture.we_i = mlx_texture_to_image(g->mlx, g->texture.we_t);
	g->texture.so_i = mlx_texture_to_image(g->mlx, g->texture.so_t);
	g->texture.no_i = mlx_texture_to_image(g->mlx, g->texture.no_t);
	g->texture.dragon_i = mlx_texture_to_image(g->mlx, g->texture.dragon_t);
	drag_x = (WIDTH - g->texture.dragon_t->width) / 2;
	drag_y = (HEIGHT - g->texture.dragon_t->height) / 2;
	mlx_image_to_window(g->mlx, g->texture.dragon_i, drag_x, drag_y);
	g->p.is_injecting = true;
	g->p.inject_timer = 0;
	g->texture.arms_idle_i = mlx_texture_to_image(g->mlx, g->texture.arms_idle_t);
	g->texture.arms_inject_i = mlx_texture_to_image(g->mlx, g->texture.arms_inject_t);
	arms_x = (WIDTH - g->texture.arms_idle_t->width) / 2;
	arms_y = HEIGHT - g->texture.arms_idle_t->height;
	mlx_image_to_window(g->mlx, g->texture.arms_idle_i, arms_x, arms_y);
	mlx_image_to_window(g->mlx, g->texture.arms_inject_i, arms_x, arms_y);
	g->texture.arms_idle_i->enabled = true;
	g->texture.arms_inject_i->enabled = false;
	player_pos = get_player_pixel_pos(g);
	g->p.x_pos = player_pos.x + CELL_PIXEL_SIZE / 2;
	g->p.y_pos = player_pos.y + CELL_PIXEL_SIZE / 2;
}

int	draw(t_game game)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	game.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
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
