/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	matrix_rotate_x(t_matrix4f m, float angle)
{
	t_matrix4f	rotate_mat;
	float		cos_a;
	float		sin_a;

	matrix_identity(rotate_mat);
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	rotate_mat[1][1] = cos_a;
	rotate_mat[1][2] = -sin_a;
	rotate_mat[2][1] = sin_a;
	rotate_mat[2][2] = cos_a;
	matrix_multiply(m, m, rotate_mat);
}

void	matrix_rotate_y(t_matrix4f m, float angle)
{
	t_matrix4f	rotate_mat;
	float		cos_a;
	float		sin_a;

	matrix_identity(rotate_mat);
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	rotate_mat[0][0] = cos_a;
	rotate_mat[0][2] = sin_a;
	rotate_mat[2][0] = -sin_a;
	rotate_mat[2][2] = cos_a;
	matrix_multiply(m, m, rotate_mat);
}

void	matrix_rotate_z(t_matrix4f m, float angle)
{
	t_matrix4f	rotate_mat;
	float		cos_a;
	float		sin_a;

	matrix_identity(rotate_mat);
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	rotate_mat[0][0] = cos_a;
	rotate_mat[0][1] = -sin_a;
	rotate_mat[1][0] = sin_a;
	rotate_mat[1][1] = cos_a;
	matrix_multiply(m, m, rotate_mat);
}
