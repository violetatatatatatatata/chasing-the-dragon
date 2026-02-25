#include <ctd.h>

void	print_map(t_map *map)
{
	int	i = 0;

	printf("NO Path: %s\n", map->no_sprite_path ? map->no_sprite_path : "(null)");
	printf("SO Path: %s\n", map->so_sprite_path ? map->so_sprite_path : "(null)");
	printf("WE Path: %s\n", map->we_sprite_path ? map->we_sprite_path : "(null)");
	printf("EA Path: %s\n", map->ea_sprite_path ? map->ea_sprite_path : "(null)");

	if (map->rgb_floor)
		printf("Floor Color (Hex): 0x%08X\n", *map->rgb_floor);
	else
		printf("Floor Color: (null ptr)\n");
	if (map->rgb_celling)
		printf("Ceiling Color (Hex): 0x%08X\n", *map->rgb_celling);
	else
		printf("Ceiling Color: (null ptr)\n");
	if (map->map)
	{
		while (map->map[i])
		{
			printf("[%02d] |%s\n", i, map->map[i]);
			i++;
		}
	}
	else
		printf("  (Map array is NULL)\n");
}
