/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:31:11 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/27 18:37:09 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

static int	check_ext(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4))
		return (print_msg("Invalid file extension", 1));
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2 || !argv[1])
		return (EXIT_FAILURE);
	if (check_ext(argv[1]))
		return (EXIT_FAILURE);
	ft_bzero(&g, sizeof(t_game));
	if (open_map(&g, argv[1]))
		return (EXIT_FAILURE);
	// alexalto
	return (EXIT_SUCCESS);
}
