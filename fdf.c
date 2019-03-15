/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnienow <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:31:25 by mnienow           #+#    #+#             */
/*   Updated: 2019/03/09 18:31:29 by mnienow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	paint_line(t_map *map, int *d, int y, int x)
{
	int fault;
	int fault2;

	fault = d[1] - d[0];
	image_set_pixel(map->img, map->x1, map->y1, map->point[0][0]->color);
	while (map->x0 != map->x1 || map->y0 != map->y1)
	{
		image_set_pixel(map->img, map->x0, map->y0, map->point[y][x]->color);
		fault2 = fault * 2;
		if (fault2 > -d[1])
		{
			fault -= d[0];
			map->x0 += map->sign_x;
		}
		if (fault2 < d[1])
		{
			fault += d[1];
			map->y0 += map->sign_y;
		}
	}
}

void			paint_map(t_map *map, int y, int x)
{
	int	d[2];

	d[0] = abs(map->y1 - map->y0);
	d[1] = abs(map->x1 - map->x0);
	map->sign_x = map->x0 < map->x1 ? 1 : -1;
	map->sign_y = map->y0 < map->y1 ? 1 : -1;
	paint_line(map, d, y, x);
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.46373398);
    *y = -z + (previous_x + previous_y) * sin(0.46373398);
}

static void		draw_line(t_map *map, int y, int x, int y_or_x)
{
	map->x0 = map->x_s + (map->point[y][x]->x * map->step);
	map->y0 = map->y_s + (map->point[y][x]->y * map->step);
	iso(&map->x0, &map->y0, map->point[y][x]->z * map->z_s);
	if (y_or_x)
	{
		map->x1 = map->x_s + ((map->point[y][x]->x + 1) * map->step);
		map->y1 = map->y_s + (map->point[y][x]->y * map->step);
		iso(&map->x1, &map->y1, map->point[y][x + 1]->z * map->z_s);
	}
	else
	{
		map->x1 = map->x_s + (map->point[y][x]->x * map->step);
		map->y1 = map->y_s + ((map->point[y][x]->y + 1) * map->step);
		iso(&map->x1, &map->y1, map->point[y + 1][x]->z * map->z_s);
	}
	paint_map(map, y, x);
}

void	printer(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->hgt)
	{
		x = 0;
		while (x < map->wid)
		{
			if (x < map->wid - 1)
				draw_line(map, y, x, 1);
			if (y < map->hgt - 1)
				draw_line(map, y, x, 0);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->wdw, map->img->image, 0, 0);
}
