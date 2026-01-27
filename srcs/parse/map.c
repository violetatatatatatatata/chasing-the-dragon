/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:32:24 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/27 17:55:11 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static char	*get_path(char *line, int i)
{
	int		len;

	while (line[i] && ft_isspace(line[i]))
		i++;
	len = 0;
	while (line[i + len] && line[i + len] != '\n')
		len++;
	return (ft_substr(line, i, len));
}

static int	save_sprites_path(t_game *game, char *line, int i)
{
	if (!ft_strncmp(&line[i], "NO", 2))
		game->no_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "SO", 2))
		game->so_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "WE", 2))
		game->we_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "EA", 2))
		game->ea_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "F", 1))
		game->rgb_floor = get_path(line, i + 1);
	else if (!ft_strncmp(&line[i], "C", 1))
		game->rgb_celling = get_path(line, i + 1);
	else
		return (0);
	return (1);
}

static int	process_info(t_game *game, t_list *file)
{
	t_list	*tmp;
	char	*line;
	int		i;

	tmp = file;
	while (tmp)
	{
		line = (char *)tmp->content;
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
		{
			tmp = tmp->next;
			continue ;
		}
		if (save_sprites_path(game, line, i))
		{
			tmp = tmp->next;
			continue ;
		}
		else if (line[i] == '1' || line[i] == '0')
			return (EXIT_SUCCESS);
		else
			return (print_msg("Invalid line found!", EXIT_FAILURE));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	open_map(t_game *game, char *input)
{
	t_list	*file;
	char	*line;
	char	*path;
	int		fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (print_msg("Cannot open file!", EXIT_FAILURE));
	while ((line = get_next_line(fd)))
		ft_lstadd_back(&file, ft_lstnew(line)); 
	close(fd);
	if (!file)
		return (print_msg("Empty file!", EXIT_FAILURE));
	if (!process_info(game, file)) 
		return (print_msg("Incorrect format on the sprites path!", EXIT_FAILURE));
	if (!parse_map_content(game, file)) 
		return (print_msg("Incorrect map!", EXIT_FAILURE));
	return (print_msg("File loaded!", EXIT_SUCCESS));
}
