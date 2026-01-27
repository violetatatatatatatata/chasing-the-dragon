#include <ctd.h>

t_list	*ft_create_map(int width, int height)
{
	t_list	*list;
	t_cell	*cell;
	int		x;
	int		y;

	list = malloc(sizeof(t_list));
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			cell = malloc(sizeof(t_cell));
			cell->pos.x = x;
			cell->pos.y = y;
			cell->cell_type = empty;
			if ((x == 0 || x == width - 1) || (y == 0 || y == height - 1))
				cell->cell_type = wall;
			ft_lstadd_back(&list, ft_lstnew(cell));
			y++;
		}
		x++;
	}
	return (list);
}
