/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pad_map.c  		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

int	pad_map_body(int i, int max_x, t_game *game)
{
	int		len;
	char	*new_row;

	len = ft_strlen(game->map.map[i]);
	if (len < max_x)
	{
		new_row = malloc(max_x + 1);
		if (!new_row)
		{
			print_msg("Malloc error in pad_map", EXIT_FAILURE);
			clean_map(game);
			return (EXIT_FAILURE);
		}
		ft_memcpy(new_row, game->map.map[i], len);
		ft_memset(new_row + len, ' ', max_x - len);
		new_row[max_x] = '\0';
		free(game->map.map[i]);
		game->map.map[i] = new_row;
	}
	return (EXIT_SUCCESS);
}

int	pad_map(t_game *game)
{
	int		i;
	int		max_x;

	max_x = game->map.max_map_x;
	i = 0;
	while (i < game->map.max_map_y)
	{
		if (pad_map_body(i, max_x, game))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
