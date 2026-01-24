/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chasing_the_dragon.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:07:53 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/24 18:19:44 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CTD_H
# define CTD_H

// keys
# define ESC	53
# define W		13
# define A		0
# define S		1
# define D		2
# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define SPA

// map
# define WALL	1
# define EMPTY	0
# define START	'N'

// colors
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define RESET	"\x1b[m"

enum type
{
	wall,
	empty,
	...
};

typedef struct	s_cell
{
	t_vector2d pos;
	enum type;
	t_cell *no;
	t_cell *so;
	t_cell *we;
	t_cell *ea;
	
}	t_cell;

typedef struct s_vector2d
{
	int	x;
	int	y;
	t_cell;
}

// contains all the cells
typedef struct
{
	void	*content;
	t_list	*next;
}	t_list;

typedef struct	t_game
{
	char	*no_sprite_path;
	char	*so_sprite_path;
	char	*we_sprite_path;
	char	*ea_sprite_path;
	...
}

#endif
