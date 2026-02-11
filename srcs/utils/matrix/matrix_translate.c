/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	matrix_translate(t_matrix4f m, float x, float y, float z)
{
	t_matrix4f		translate_mat;

	matrix_identity(translate_mat);
	translate_mat[0][3] = x;
	translate_mat[1][3] = y;
	translate_mat[2][3] = z;
	matrix_multiply(m, m, translate_mat);
}
