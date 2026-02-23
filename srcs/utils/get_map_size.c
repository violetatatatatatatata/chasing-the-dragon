/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_map_size.c		    							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	get_map_size(t_game *g)
{
	int		i;
	int		j;
	int		max_y;
	char	**map;

	map = g->map.map;
	max_y = 0;
	i = 0;
	while (map[i])
		i++;
	g->map.max_map_y = i;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (max_y < j)
			max_y = j;
		i++;
	}
	g->map.max_map_x = max_y;
}
