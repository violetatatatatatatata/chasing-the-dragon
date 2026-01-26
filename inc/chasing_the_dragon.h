/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chasing_the_dragon.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:07:53 by avelandr          #+#    #+#             */
/*   Updated: 2026/01/26 19:02:40 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CTD_H
# define CTD_H

// keys
# define ESC    53
# define W      13
# define A      0
# define S      1
# define D      2
# define UP     126
# define DOWN   125
# define LEFT   123
# define RIGHT  124
# define SPACE  49

# define WALL   '1'
# define EMPTY  '0'
# define NORTH  'N'
# define SOUTH  'S'
# define EAST   'E'
# define WEST   'W'
# define IS_PLAYER(c) (c == NORTH || c == SOUTH || c == EAST || c == WEST)

# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define RESET	"\x1b[m"

typedef struct	s_cell
{
	t_vector2d pos;
	enum type;
	t_cell *no;
	t_cell *so;
	t_cell *we;
	t_cell *ea;
	
}	t_cell;

typedef struct s_cell
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
	char	**map;
	char	*no_sprite_path;
	char	*so_sprite_path;
	char	*we_sprite_path;
	char	*ea_sprite_path;
	char	*rgb_floor;
	char	*rgb_celling;
}

#endif
