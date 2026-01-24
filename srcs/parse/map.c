/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:27:25 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/24 14:37:25 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	open_map(t_game *game, char *map_path)
{
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0 || !is_valid_format(map_path))
	{
		exit_game();
		close(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		process_line = (game, line);
	}
	close(fd);
}

/*	N = start position
 *	1 = wall
 *	0 = empty 
 * */
void	process_cell()
{
	
}
