#include <ctd.h>

char	**ft_create_map(int width, int height)
{
	char	**map;
	int		x;
	int		y;

	map = malloc(sizeof(char *) * width);
	x = 0;
	while (x < width)
	{
		map[x] = malloc(sizeof(char) * height);
		y = 0;
		while (y < height)
		{
			map[x][y] = '0';
			if ((x == 0 || x == width - 1) || (y == 0 || y == height - 1))
				map[x][y] = '1';
			else if (x == width / 2 && y == height / 2)
				map[x][y] = 'N';
			y++;
		}
		x++;
	}
	return (map);
}
