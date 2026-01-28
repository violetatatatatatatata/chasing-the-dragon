/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:58:59 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/28 18:45:17 by avelandr         ###   ########.fr       */
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
	char	*f;
	char	*c;

	if (!ft_strncmp(&line[i], "NO", 2))
		game->map.no_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "SO", 2))
		game->map.so_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "WE", 2))
		game->map.we_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "EA", 2))
		game->map.ea_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "F", 1))
	{
		f = get_path(line, i + 1);
		game->map.rgb_floor = malloc(sizeof(uint32_t));
		if (game->map.rgb_floor)
			*game->map.rgb_floor = get_rgba(f);
		free(f);
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		c = get_path(line, i + 1);
		game->map.rgb_celling = malloc(sizeof(uint32_t));
		if (game->map.rgb_celling)
			*game->map.rgb_celling = get_rgba(c);
		free(c);
	}
	else
		return (0);
	return (1);
}

static int	process_info(t_game *game, t_list *file)
{
	t_list	*tmp;
	char	*l;
	int		i;

	tmp = file;
	while (tmp)
	{
		l = (char *)tmp->content;
		i = 0;
		while (l[i] && ft_isspace(l[i]))
			i++;
		if (!l[i])
		{
			tmp = tmp->next;
			continue ;
		}
		if (save_sprites_path(game, l, i))
			tmp = tmp->next;
		else if (l[i] == '1' || l[i] == '0')
			return (EXIT_SUCCESS);
		else
			return (print_msg("Invalid line found!", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

static int	list_to_map(t_game *game, t_list *file)
{
	t_list	*tmp;
	char	*l;
	int		i;
	int		h;

	tmp = file;
	while (tmp)
	{
		l = (char *)tmp->content;
		i = 0;
		while (l[i] && ft_isspace(l[i]))
			i++;
		if (l[i] == '1' || l[i] == '0')
			break ;
		tmp = tmp->next;
	}
	h = ft_lstsize(tmp);
	game->map.map = ft_calloc(h + 1, sizeof(char *));
	if (!game->map.map)
		return (print_msg("Malloc failed", 1));
	i = 0;
	while (tmp)
	{
		l = (char *)tmp->content;
		if (l[ft_strlen(l) - 1] == '\n')
			game->map.map[i] = ft_substr(l, 0, ft_strlen(l) - 1);
		else
			game->map.map[i] = ft_strdup(l);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static void	print_map(t_map *map) {
	int	i = 0;

	printf("NO Path: %s\n", map->no_sprite_path ? map->no_sprite_path : "(null)");
	printf("SO Path: %s\n", map->so_sprite_path ? map->so_sprite_path : "(null)");
	printf("WE Path: %s\n", map->we_sprite_path ? map->we_sprite_path : "(null)");
	printf("EA Path: %s\n", map->ea_sprite_path ? map->ea_sprite_path : "(null)");

	if (map->rgb_floor)
		printf("Floor Color (Hex): 0x%08X\n", *map->rgb_floor);
	else
		printf("Floor Color: (null ptr)\n");
	if (map->rgb_celling)
		printf("Ceiling Color (Hex): 0x%08X\n", *map->rgb_celling);
	else
		printf("Ceiling Color: (null ptr)\n");
	if (map->map)
	{
		while (map->map[i])
		{
			printf("[%02d] |%s\n", i, map->map[i]);
			i++;
		}
	}
	else
		printf("  (Map array is NULL)\n");
}

int	open_map(t_game *game, char *input)
{
	t_list	*file;
	char	*line;
	int		fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (print_msg("Cannot open file!", EXIT_FAILURE));
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
		return (print_msg("Empty file!", EXIT_FAILURE));
	if (process_info(game, file))
		return (EXIT_FAILURE);
	if (list_to_map(game, file))
		return (EXIT_FAILURE);
	if (!is_valid_file(game))
		return (EXIT_FAILURE);
	print_map(&game->map);
	return (print_msg("File loaded!", EXIT_SUCCESS));
}
