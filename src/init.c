/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_player(t_player *p, t_map *map)
{
	ft_bzero(p, sizeof(t_player));
	p->size = 10;
	p->x = CUBE * (map->player_start % map->w) + p->size;
	p->y = CUBE * (map->player_start / map->w) + p->size;
	p->speed = 7.0;
	p->fov = RAD_60;
	p->dir = RAD_0;
	p->size = 10;
	p->dist_to_canvas = (W / 2) / tan(p->fov / 2);
	p->step = p->fov / W;
	p->floor_offset = 0;
}

void	init_bonus(t_bonus *bon)
{
	bon->music_flag = 0;
	bon->fps = 1;
	bon->startTime = 0;
	bon->fps_count = 0;
	bon->guns_fire = 0;
	bon->music = NULL;
	/*
	на каждое открытие должна быть проверка с error() в случае неудачи
	*/
	bon->image_1 = IMG_Load("textures/guns-1.bmp");
	bon->image_2 = IMG_Load("textures/guns-2.bmp");
	bon->image_3 = IMG_Load("textures/guns-3.bmp");
	bon->image_4 = IMG_Load("textures/guns-4.bmp");
	bon->image_5 = IMG_Load("textures/guns-5.bmp");
	bon->image_coin = IMG_Load("textures/coin.png");
	bon->my_font = TTF_OpenFont("ttf/19888.ttf", (int)(H / 28));
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	bon->music_guns = Mix_LoadWAV("music/01664_q6IhiXXL.wav");
	bon->music_coin = Mix_LoadWAV("music/coin_m.wav");
	bon->music = Mix_LoadMUS("music/Oto Kapanadze - Mystic Mountain.mp3");
	if (!bon->image_1 || !bon->image_2 || !bon->image_3 || !bon->image_4 || !bon->image_5 ||
		!bon->image_coin || !bon->my_font || !bon->music_guns || !bon->music || !bon->music_coin)
		exit(0);
	bon->imgLocation.w = W / 3;
    bon->imgLocation.h = H / 3;
    bon->imgLocation.x = (W / 2) - (W / 6);
    bon->imgLocation.y = H - H / 3;
	bon->flag_guns = 0;
	bon->start_guns = 0;
	bon->score_coin = 0;
}

void	init_tex_arr(t_wolf *wolf)
{
	int	i;

	i = -1;
	wolf->sdl->tex_arr[TEX_BORDER] = CUBE * 6;
	while (++i < 1 << 8)
		wolf->sdl->tex_arr[i] = wolf->sdl->tex_arr[TEX_BORDER];
	wolf->sdl->tex_arr[TEX_WALL] = CUBE * 7;
	wolf->sdl->tex_arr[TEX_EAST] = CUBE * 2;
	wolf->sdl->tex_arr[TEX_SOUTH] = CUBE * 3;
	wolf->sdl->tex_arr[TEX_NORTH] = CUBE * 4;
	wolf->sdl->tex_arr[TEX_WEST] = CUBE * 5;
	wolf->sdl->tex_arr[TEX_BLOOD] = CUBE * 0;
	wolf->sdl->tex_arr[TEX_PANEL] = CUBE * 1;
	wolf->sdl->tex_arr[TEX_BOULD] = CUBE * 2;
	wolf->sdl->tex_arr[TEX_CORALL] = CUBE * 3;
	wolf->sdl->tex_arr[TEX_EYES] = CUBE * 4;
	wolf->sdl->tex_arr[TEX_ISLE] = CUBE * 5;
}

void	init_mm(t_map *map)
{
	int	map_max_side;

	map_max_side = max(map->w, map->h);
	map->mm_cube = (W / 3) / map_max_side;
	map->mm_start.x = 16;
	map->mm_start.y = 16;
	map->mm_w = map->mm_cube * map->w;
	map->mm_h = map->mm_cube * map->h;
	map->mm_p_size = map->mm_cube / 4;
	map->mm_cube_coef = (float)map->mm_cube / CUBE;
	map->mm_map_coef = (float)map->mm_w / W;
	map->mm_show = 1;
}
