/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 convertor.c   										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

t_vector2	cell2pixel(int x, int y)
{
	t_vector2	pixel_pos;

	pixel_pos.x = x * CELL_PIXEL_SIZE;
	pixel_pos.y = y * CELL_PIXEL_SIZE;
	return (pixel_pos);
}

t_vector2	pixel2cell(int x, int y)
{
	t_vector2	cell_pos;

	cell_pos.x = x / CELL_PIXEL_SIZE;
	cell_pos.y = y / CELL_PIXEL_SIZE;
	return (cell_pos);
}

/*t_vector2	pos2pixel(double x, double y)
{

}*/
