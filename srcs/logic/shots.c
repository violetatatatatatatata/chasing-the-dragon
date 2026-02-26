/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 shots.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/30 11:52:19 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2026/01/30 11:52:19 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

double	speedy_gonzales(t_player p)
{
	double	speed;

	speed = 0.8;
	if (p.shots_left == 0)
	{
		speed = 5;
		if (p.spikes_left == 0)
			return (0.5);
	}
	else if (p.shots_left == 1)
		speed = 1.2;
	else if (p.shots_left == 2)
		speed = 2.5;
	else if (p.shots_left == 3)
		speed = 3.5;
	speed += (3 - p.spikes_left) * 0.05;
	return (speed);
}
