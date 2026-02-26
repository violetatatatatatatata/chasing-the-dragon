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

static t_list	*find_map_start(t_list *file, int *height)
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
		if (l[i] == '1' || l[i] == '0')
			break ;
		tmp = tmp->next;
	}
	*height = ft_lstsize(tmp);
	return (tmp);
}

static int	save_sprites_path(t_game *game, char *line, int i)
{
	if (save_texture_path(game, line, i))
		return (1);
	if (save_color_path(game, line, i))
		return (1);
	return (0);
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
			return (clean_paths(game), print_msg("Invalid line found!", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

static int	list_to_map(t_game *game, t_list *file)
{
	t_list	*start;
	int		height;

	start = find_map_start(file, &height);
	if (!start)
		return (print_msg("No map data found", 1));
	return (copy_map_lines(game, start, height));
}

int	open_map(t_game *game, char *input)
{
	t_list	*file;

	file = read_map_file(input);
	if (!file)
		return (EXIT_FAILURE);
	if (process_info(game, file))
		return (ft_lstclear(&file, clean_file), EXIT_FAILURE);
	if (list_to_map(game, file))
		return (ft_lstclear(&file, clean_file), EXIT_FAILURE);
	get_map_size(game);
	if (!is_valid_file(game))
		return (ft_lstclear(&file, clean_file),
			clean_map(game), EXIT_FAILURE);
	print_map(&game->map);
	print_msg("File loaded!", EXIT_SUCCESS);
	ft_lstclear(&file, clean_file);
	return (EXIT_SUCCESS);
}
