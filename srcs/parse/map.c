/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:27:25 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/24 18:21:04 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

int	open_map(t_game *game, char *input)
{
	char	**file;
	char	*line;
	int		fd;

	fd = open(maps/input, O_RDONLY);
	if (fd < 0 || !is_valid_format(input))
		return(print_msg("Cannot load file!", EXIT_FAILURE));
	while (line = get_next_line(fd))
	{
		file = append_line(line);
		if (!file)
			return(print_msg("Invalid file!", EXIT_FAILURE));
		free(line);
	}
	if (!is_valid_file(file))
		return(print_msg("Invalid file!", EXIT_FAILURE));
	process_info(game, file);
	close(fd);
	return(print_msg("File loaded!", EXIT_SUCCESS));
}

void	process_info(t_game game, char **file)
{
	char	**map;
	int		i;

	game->no_sprite_path = ft_substr(file[0], 2, ft_strlen(file[0]));
	game->so_sprite_path = ft_substr(file[1], 2, ft_strlen(file[1]));
	game->we_sprite_path = ft_substr(file[2], 2, ft_strlen(file[2]));
	game->ea_sprite_path = ft_substr(file[3], 2, ft_strlen(file[3]));
	game->rgb_celling = ft_substr(file[5], 1, ft_strlen(file[5]));
	game->rgb_floor = ft_substr(file[6], 1, ft_strlen(file[6]));
	i = 7;
	while (file[i])
	{
		map[i - 7] = file[i];
		i++;
	}
}
