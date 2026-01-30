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

	speed = 0.1;
	if (p.shots_left == 0)
	{
		speed = 0.8;
		if (p.spikes_left == 0)
			return (0.1);
	}
	else if (p.shots_left == 1)
		speed = 0.67;
	else if (p.shots_left == 2)
		speed = 0.569;
	else if (p.shots_left == 3)
		speed = 0.42;
	speed += (3 - p.spikes_left) * 0.05;
	return (speed);
}
