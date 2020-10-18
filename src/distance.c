/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:21:20 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_distance		*t_distance_new(t_wolf *wolf)
{
	t_distance	*new;

	if (!(new = (t_distance *)malloc(sizeof(t_distance))))
		error(wolf, ERR_MALLOC);
	new->dist = 99999.f;
	new->offsetx = 0;
	new->tex = TEX_INF;
	new->coords.x = -1;
	new->coords.y = -1;
	return (new);
}

void			all_get_distance(t_wolf *wolf)
{
	float		i;
	int			count_distance;
	float		cos_agle;
	float		temp_i;

	i = wolf->player->dir;
	i = wolf->player->dir - (wolf->player->fov / 2);
	count_distance = 0;
	cos_agle = wolf->player->fov / 2;
	while (i < wolf->player->dir + (wolf->player->fov / 2))
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i);
		wolf->player->distance[count_distance]->dist *= cosf(cos_agle);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
		count_distance++;
	}
}

t_distance		*dist_to_wall(t_wolf *wolf, float angle)
{
	return (dist_to_texture(wolf, angle, TEX_BORDER));
}

t_distance		*dist_to_floor(t_wolf *wolf, float angle)
{
	return (dist_to_texture(wolf, angle, TEX_FLOOR));
}

t_distance		*dist_to_texture(t_wolf *wolf, float angle, char texture)
{
	t_distance	*h;
	t_distance	*v;

	v = find_vertical_intersection(wolf, angle, TEX_BORDER);
	h = find_horizontal_intersection(wolf, angle);
	if (v->dist > h->dist)
	{
		free(v);
		h->side = 0;
		return (h);
	}
	else
	{
		free(h);
		v->side = 1;
		return (v);
	}
}
