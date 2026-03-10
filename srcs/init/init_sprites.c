/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:58:41 by avelandr          #+#    #+#             */
/*   Updated: 2026/02/26 16:48:16 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static uint32_t	get_col(uint32_t *rgb)
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

void	draw_colors(t_game *game)
{
	int			x;
	int			y;
	uint32_t	c_ceil;
	uint32_t	c_floor;

	c_ceil = get_col(game->map.rgb_celling);
	c_floor = get_col(game->map.rgb_floor);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, c_ceil);
			else
				mlx_put_pixel(game->img, x, y, c_floor);
			y++;
		}
		x++;
	}
}

static int	load_ui_sprites(t_game *g)
{
	if (ft_access("sprites/heroinx0.png")
		|| ft_access("sprites/heroinx1.png")
		|| ft_access("sprites/heroinx2.png")
		|| ft_access("sprites/heroinx3.png")
		|| ft_access("sprites/heroinx4.png")
		|| ft_access("sprites/smack00.png")
		|| ft_access("sprites/smack01.png")
		|| ft_access("sprites/smack02.png")
		|| ft_access("sprites/smack03.png"))
		return (print_msg("No me borres las texturas!! >:(", EXIT_FAILURE));
	g->texture.shots_t[0] = mlx_load_png("sprites/heroinx0.png");
	g->texture.shots_t[1] = mlx_load_png("sprites/heroinx1.png");
	g->texture.shots_t[2] = mlx_load_png("sprites/heroinx2.png");
	g->texture.shots_t[3] = mlx_load_png("sprites/heroinx3.png");
	g->texture.shots_t[4] = mlx_load_png("sprites/heroinx4.png");
	g->texture.spikes_t[0] = mlx_load_png("sprites/smack00.png");
	g->texture.spikes_t[1] = mlx_load_png("sprites/smack01.png");
	g->texture.spikes_t[2] = mlx_load_png("sprites/smack02.png");
	g->texture.spikes_t[3] = mlx_load_png("sprites/smack03.png");
	return (EXIT_SUCCESS);
}

static int	ft_nasty(t_game *game)
{
	if (ft_access(game->map.no_sprite_path)
		|| ft_access(game->map.so_sprite_path)
		|| ft_access(game->map.we_sprite_path)
		|| ft_access(game->map.ea_sprite_path)
		|| ft_access("sprites/joan_caganer.png")
		|| ft_access("sprites/Dragon.png")
		|| ft_access("sprites/arms_idle.png")
		|| ft_access("sprites/arms_inject.png"))
		return (print_msg("Chic@ mal@!! >:(", EXIT_FAILURE));
	game->texture.no_t = mlx_load_png(game->map.no_sprite_path);
	game->texture.so_t = mlx_load_png(game->map.so_sprite_path);
	game->texture.we_t = mlx_load_png(game->map.we_sprite_path);
	game->texture.ea_t = mlx_load_png(game->map.ea_sprite_path);
	game->texture.joan_t = mlx_load_png("sprites/joan_caganer.png");
	game->texture.dragon_t = mlx_load_png("sprites/Dragon.png");
	game->texture.arms_idle_t = mlx_load_png("sprites/arms_idle.png");
	game->texture.arms_inject_t = mlx_load_png("sprites/arms_inject.png");
	return (EXIT_SUCCESS);
}

int	load_sprites(t_game *game)
{
	if (load_ui_sprites(game) || ft_nasty(game))
	{
		clean_map(game);
		exit (EXIT_FAILURE);
	}
	game->texture.is_joan = false;
	if (!game->texture.no_t || !game->texture.so_t || !game->texture.we_t
		|| !game->texture.ea_t || !game->texture.dragon_t
		|| !game->texture.arms_idle_t || !game->texture.arms_inject_t
		|| !game->texture.shots_t[0] || !game->texture.spikes_t[0])
	{
		clean_map(game);
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
