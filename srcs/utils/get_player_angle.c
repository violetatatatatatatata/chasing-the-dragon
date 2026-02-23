/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_player_angle.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by aalcaide		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

double	get_player_angle(char c)
{
	if (c == 'E')
		return (0.0f);
	if (c == 'W')
		return (180.0f);
	if (c == 'N')
		return (90.0f);
	if (c == 'S')
		return (270.0f);
	return (0.0f);
}
