/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:32:24 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/28 15:35:35 by avelandr         ###   ########.fr       */
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
		game->no_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "SO", 2))
		game->so_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "WE", 2))
		game->we_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "EA", 2))
		game->ea_sprite_path = get_path(line, i + 2);
	else if (!ft_strncmp(&line[i], "F", 1))
	{
		f = get_path(line, i + 1);
		game->rgb_floor = get_rgb(f);
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		c = get_path(line, i + 1);
		game->rgb_celling = get_rgb(c);
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
	game->map = ft_calloc(h + 1, sizeof(char *));
	if (!game->map)
		return (print_msg("Malloc failed", 1));
	i = 0;
	while (tmp)
	{
		l = (char *)tmp->content;
		if (l[ft_strlen(l) - 1] == '\n')
			game->map[i] = ft_substr(l, 0, ft_strlen(l) - 1);
		else
			game->map[i] = ft_strdup(l);
		tmp = tmp->next;
		i++;
	}
	return (0);
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
	// ft_lstclear(&file, free);
	return (print_msg("File loaded!", EXIT_SUCCESS));
}
