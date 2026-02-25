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

int	copy_map_lines(t_game *game, t_list *start, int height)
{
	int		i;
	char	*l;
	size_t	len;

	game->map.map = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.map)
		return (print_msg("Malloc failed", 1));
	i = 0;
	while (start)
	{
		l = (char *)start->content;
		len = ft_strlen(l);
		if (len > 0 && l[len - 1] == '\n')
			game->map.map[i] = ft_substr(l, 0, len - 1);
		else
			game->map.map[i] = ft_strdup(l);
		start = start->next;
		i++;
	}
	return (0);
}

t_list	*read_map_file(char *input)
{
	t_list	*file;
	char	*line;
	int		fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (print_msg("Cannot open file!", EXIT_FAILURE), NULL);
	file = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_lstadd_back(&file, ft_lstnew(line));
	}
	close(fd);
	if (!file)
		return (print_msg("Empty file!", EXIT_FAILURE), NULL);
	return (file);
}

int	save_texture_path(t_game *game, char *line, int i)
{
	if (!ft_strncmp(&line[i], "NO", 2))
		game->map.no_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "SO", 2))
		game->map.so_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "WE", 2))
		game->map.we_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "EA", 2))
		game->map.ea_sprite_path = get_path(line, i + 2);
	else
		return (0);
	return (1);
}

int	save_color_path(t_game *game, char *line, int i)
{
	char	*color_str;

	if (!ft_strncmp(&line[i], "F", 1))
	{
		color_str = get_path(line, i + 1);
		game->map.rgb_floor = malloc(sizeof(uint32_t));
		if (game->map.rgb_floor)
			*game->map.rgb_floor = get_rgba(color_str);
		free(color_str);
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		color_str = get_path(line, i + 1);
		game->map.rgb_celling = malloc(sizeof(uint32_t));
		if (game->map.rgb_celling)
			*game->map.rgb_celling = get_rgba(color_str);
		free(color_str);
	}
	else
		return (0);
	return (1);
}
