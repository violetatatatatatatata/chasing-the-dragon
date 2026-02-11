/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	matrix_scale(t_matrix4f m, float x, float y, float z)
{
	t_matrix4f	scale_mat;

	matrix_identity(scale_mat);
	scale_mat[0][0] = x;
	scale_mat[1][1] = y;
	scale_mat[2][2] = z;
	matrix_multiply(m, m, scale_mat);
}
