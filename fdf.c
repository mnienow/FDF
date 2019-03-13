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

static	void	paint_line(t_map *map, int dx, int dy)
{
	int fault;
	int fault2;

	fault = dx - dy;
	image_set_pixel(map->img, map->x1, map->y1, 0xFFFFFF);
	while (map->x0 != map->x1 || map->y0 != map->y1)
	{
		image_set_pixel(map->img, map->x0, map->y0, 0xFFFFFF);
		fault2 = fault * 2;
		if (fault2 > -dy)
		{
			fault -= dy;
			map->x0 += map->sign_x;
		}
		if (fault2 < dx)
		{
			fault += dx;
			map->y0 += map->sign_y;
		}
	}
}

void			paint_map(t_map *map)
{
	int dx;
	int dy;

	dx = abs(map->x1 - map->x0);
	dy = abs(map->y1 - map->y0);
	map->sign_x = map->x0 < map->x1 ? 1 : -1;
	map->sign_y = map->y0 < map->y1 ? 1 : -1;
	paint_line(map, dx, dy);
}

static void iso(int *x, int *y, t_point	*point)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    point->x = (previous_x - previous_y) * cos(0.523599);
    point->y = (point->z * -1) + (previous_x + previous_y) * sin(0.523599);
}

static	void	draw_line(t_map *map, int y, int x, int x_or_y)
{
	iso(&y, &x, map->point[x + (y * map->wid)]);
	map->x0 = map->x_s + (x * map->step);
	map->y0 = map->y_s + (y * map->step) - map->point[x + (y * map->wid - 1)]->z * map->z_s;
	if (x_or_y)
	{
		map->x1 = map->x_s + ((map->point[x + (y * map->wid)]->x + 1) * map->step);
		map->y1 = map->y_s + (y * map->step) - map->point[x + 1 + (y * map->wid - 1)]->z * map->z_s;

	}
	else
	{
		map->x1 = map->x_s + (x * map->step);
		map->y1 = map->y_s + ((y + 1) * map->step) - map->point[x + ((y + 1) * map->wid - 1)]->z * map->z_s;
	}
	paint_map(map);
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
