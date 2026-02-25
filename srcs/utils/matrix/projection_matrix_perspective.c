/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix_perspective.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	projection_matrix_perspective(t_matrix4f projection_matrix,
	t_game *g)
{
	matrix_identity(projection_matrix);
	projection_matrix[0][0] = 2 * 0.01f / g->mlx->width;
	projection_matrix[1][1] = 2 * 0.01f / g->mlx->height;
	projection_matrix[0][2] = 1.0f;
	projection_matrix[1][2] = 1.0f;
	projection_matrix[2][2] = -(1000.0f + 0.01f) / (1000.0f + 0.01f);
	projection_matrix[2][3] = -2 * 1000.0f * 0.01f / (1000.0f - 0.01f);
	projection_matrix[3][2] = -1;
	projection_matrix[3][3] = 0;
}
