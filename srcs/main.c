/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:31:11 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/26 19:02:49 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2 || !argv[1])
		return (EXIT_FAILURE);
	g = ft_memset(&g, 0, sizeof(g));
	if (!open_map(g, argv[1])i)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
