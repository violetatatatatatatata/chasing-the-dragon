/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 clean_game.c  										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	clean_paths(t_game *g)
{
	free(g->map.no_sprite_path);
	free(g->map.so_sprite_path);
	free(g->map.we_sprite_path);
	free(g->map.ea_sprite_path);
	free(g->map.rgb_floor);
	free(g->map.rgb_celling);
}

void	clean_map(t_game *g)
{
	clean_paths(g);
	clean_double_arr(g->map.map, g->map.max_map_y);
}

static void	ft_dont_do_drugs(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_delete_image(g->mlx, g->texture.spikes_i[i]);
		mlx_delete_texture(g->texture.spikes_t[i]);
	}
	i = -1;
	while (++i < 5)
	{
		mlx_delete_image(g->mlx, g->texture.shots_i[i]);
		mlx_delete_texture(g->texture.shots_t[i]);
	}

}

static void	ft_clean_draw(t_game *g)
{
	ft_dont_do_drugs(g);
	mlx_delete_image(g->mlx, g->texture.no_i);
	mlx_delete_texture(g->texture.no_t);
	mlx_delete_image(g->mlx, g->texture.so_i);
	mlx_delete_texture(g->texture.so_t);
	mlx_delete_image(g->mlx, g->texture.ea_i);
	mlx_delete_texture(g->texture.ea_t);
	mlx_delete_image(g->mlx, g->texture.we_i);
	mlx_delete_texture(g->texture.we_t);
	mlx_delete_image(g->mlx, g->texture.dragon_i);
	mlx_delete_texture(g->texture.dragon_t);
	mlx_delete_image(g->mlx, g->texture.arms_idle_i);
	mlx_delete_texture(g->texture.arms_idle_t);
	mlx_delete_image(g->mlx, g->texture.arms_inject_i);
	mlx_delete_texture(g->texture.arms_inject_t);
}

void	clean_game(void *g)
{
	t_game	*game;

	game = (t_game *)g;
	clean_map(game);
	ft_clean_draw(game);
	mlx_delete_image(game->mlx, game->img);
	mlx_delete_image(game->mlx, game->img_cube_map);
}
