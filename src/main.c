#include "../includes/wolf3d.h"

t_point	dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_wolf		*t_wolf_new(void)
{
	t_wolf	*new;

	if (!(new = (t_wolf *)malloc(sizeof(t_wolf))))
		exit(1);
	if (!(new->map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	if (!(new->player = (t_player *)malloc(sizeof(t_player))))
		exit(1);
	if (!(new->surface = (SDL_Surface *)malloc(sizeof(SDL_Surface))))
		exit(1);
	if (!(new->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		exit(1);
	return new;
}

int	main(int a, char **b)
{
	t_wolf *wolf;

	if (a != 2)
	{
		printf("usage : ./wolf3d [map]\n");
        exit(1);
	}
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf("error\n");
        exit(1);
    }
	if (TTF_Init() != 0)
	{
        printf("error\n");
        exit(1);
	}
	wolf = t_wolf_new();
	init_map(wolf->map, b[1]);
	load_textures(wolf, wolf->sdl);
	init_player(wolf->player, wolf->map);
	music(wolf->player);
	init_sdl(wolf, wolf->map, wolf->player);
	return (0);
}