/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:42:29 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/24 18:43:21 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctd.h>

int	print_msg(char *str, int exit)
{
	if (exit == EXIT_FAILURE)
		printf("%sError\n%s", RED, RESET);
	else if (exit == EXIT_SUCCESS)
		printf("%s%s", GREEN, RESET);
	printf("%s\n", str);
	return (exit);
}
