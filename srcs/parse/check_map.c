/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:46:48 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/30 12:46:36 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static void	free_m(char **m)
{
	int	i;

	i = 0;
	if (!m)
		return ;
	while (m[i])
		free(m[i++]);
	free(m);
}

static char	**duplicate_m(char **map)
{
	char	**cpy;
	int		h;
	int		i;

	h = 0;
	while (map[h])
		h++;
	cpy = ft_calloc(h + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = -1;
	while (++i < h)
	{
		cpy[i] = ft_strdup(map[i]);
		if (!cpy[i])
		{
			free_m(cpy);
			return (NULL);
		}
	}
	return (cpy);
}

static void	flood_fill(char **map, int x, int y, int *err)
{
	if (*err)
		return ;
	if (y < 0 || !map[y] || x < 0 || (size_t)x >= ft_strlen(map[y]))
	{
		*err = 1;
		return ;
	}
	if (ft_isspace(map[y][x]) || map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, err);
	flood_fill(map, x - 1, y, err);
	flood_fill(map, x, y + 1, err);
	flood_fill(map, x, y - 1, err);
}

static void	get_player_pos(char **map, int *x, int *y, double *pov)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				player++;
				*x = j;
				*y = i;
				*pov = get_player_angle(map[i][j]);
			}
		}
	}
	if (player != 1)
		exit(print_msg("No more than one player!", 1));
}

int	check_map_closed(t_game *game)
{
	char	**temp;
	int		x;
	int		y;
	int		err;

	if (!game->map.map)
		return (0);
	temp = duplicate_m(game->map.map);
	if (!temp)
		return (0);
	get_player_pos(temp, &x, &y, &game->p.pov);
	err = 0;
	if (!temp[y])
		err = 1;
	else
		flood_fill(temp, x, y, &err);
	free_m(temp);
	return (err);
}
