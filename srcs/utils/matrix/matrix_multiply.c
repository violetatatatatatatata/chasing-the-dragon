/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:31 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

void	ft_matrix_copy(t_matrix4f dst, t_matrix4f src)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

static void	ft_matrix_multiply_calc(t_matrix4f tmp, t_matrix4f a, t_matrix4f b)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp[i][j] = 0.0f;
			k = 0;
			while (k < 4)
			{
				tmp[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void	matrix_multiply(t_matrix4f res, t_matrix4f a, t_matrix4f b)
{
	t_matrix4f	tmp;

	ft_matrix_multiply_calc(tmp, a, b);
	ft_matrix_copy(res, tmp);
}
