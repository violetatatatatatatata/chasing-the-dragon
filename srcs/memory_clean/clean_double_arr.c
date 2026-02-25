/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 clean_double_arr.c  								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

void	clean_double_arr(char **arr, int x_max)
{
	int	x;

	x = 0;
	while (x < x_max)
		free(arr[x++]);
	free(arr);
}
