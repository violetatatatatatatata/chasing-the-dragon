/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:27:25 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/26 19:02:38 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static void parse_line(t_game *game, char *line)
{
    int i = 0;

    while (ft_isspace(line[i]))
		i++;
    if (ft_strncmp(&line[i], "NO", 2) == 0)
        parse_texture(&game->no_sprite_path, &line[i + 2]);
    else if (ft_strncmp(&line[i], "SO", 2) == 0)
        parse_texture(&game->so_sprite_path, &line[i + 2]);
    else if (line[i] == 'F')
        parse_color(&game->rgb_floor, &line[i + 1]);
    else if (line[i] == 'C')
        parse_color(&game->rgb_celling, &line[i + 1]);
    else if (line[i] == '1' || line[i] == '0')
    else if (line[i] != '\0')
        print_msg("Error!", EXIT_FAILURE);
}

static void	process_info(t_game game, char **file)
{
	char	**map;
	int		i;

	game->no_sprite_path = ft_substr(file[0], 2, ft_strlen(file[0]));
	game->so_sprite_path = ft_substr(file[1], 2, ft_strlen(file[1]));
	game->we_sprite_path = ft_substr(file[2], 2, ft_strlen(file[2]));
	game->ea_sprite_path = ft_substr(file[3], 2, ft_strlen(file[3]));
	game->rgb_celling = ft_substr(file[5], 1, ft_strlen(file[5]));
	game->rgb_floor = ft_substr(file[6], 1, ft_strlen(file[6]));
	i = 8;
	while (file[i])
	{
		map[i - 8] = file[i];
		i++;
	}
}

int	open_map(t_game *game, char *input)
{
	char	**file;
	char	*line;
	int		fd;
	char	*path;
	
	fd = open(input, O_RDONLY);
	if (fd < 0 || !is_valid_format(input))
		return(print_msg("Cannot load file!", EXIT_FAILURE));
	while (line = get_next_line(fd))
	{
		file = ft_strjoin(file, line);
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
