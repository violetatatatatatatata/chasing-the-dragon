/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utils.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/28 15:21:30 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2026/01/28 15:21:36 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

static int	advance_to_next(char *str, int i)
{
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	return (i);
}

/*	r << 24: Mueve el rojo a los bits 24-31.
 *	g << 16: Mueve el verde a los bits 16-23.
 *	b << 8: Mueve el azul a los bits 8-15.
 * */
uint32_t	get_rgba(char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = ft_atoi(str);
	i = advance_to_next(str, i);
	g = ft_atoi(str + i);
	i = advance_to_next(str, i);
	b = ft_atoi(str + i);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
