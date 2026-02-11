/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vec4_multiply.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	matrix_vec4_multiply(t_vector4f *res, t_matrix4f m, t_vector4f v)
{
	int		i;
	float	tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = m[i][0] * v.x
			+ m[i][1] * v.y
			+ m[i][2] * v.z
			+ m[i][3] * v.w;
		i++;
	}
	res->x = tmp[0];
	res->y = tmp[1];
	res->z = tmp[2];
	res->w = tmp[3];
}
