/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstannis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 07:24:29 by sstannis          #+#    #+#             */
/*   Updated: 2019/02/24 07:24:31 by sstannis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	*new_point(int j, int k, int *i, t_map *map)
{
	t_point		*new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = k;
	new->y = j;
	new->z = ft_atoi(&map->lmap[i[0]]);
	while (map->lmap[i[0]] >= '0' && map->lmap[i[0]] <= '9')
		i[0]++;
	if (map->lmap[i[0]] == ',')
	{
		i[0]++;
		// new->color = ft_atoi_base(&map->lmap[i[0]], 16);
		new->color = 0x008000 + new->z * 10;
		while (map->lmap[i[0]] != ' ')
			i[0]++;
	}
	else
		new->color = 0x008000 + new->z * 20;
	return (new);
}

static int		writer(t_map *map, int i, int j, int k)
{
	if (!(map->point = (t_point ***)malloc(sizeof(t_point **) * map->hgt)))
		return (-1);
	while (i <= map->hgt)
		if (!(map->point[i++] = (t_point **)malloc(8 * map->wid)))
			return (-1);
	i = 0;
	while (map->lmap[i])
	{
		if (map->lmap[i] >= '0' && map->lmap[i] <= '9')
		{
			map->point[j][k] = new_point(j, k, &i, map);
			k++;
		}
		if (map->lmap[i] == '\n')
		{
			j++;
			k = 0;
		}
		i++;
	}
	return (0);
}

static int		valider(t_map *map, int i, int j)
{
	if (map->lmap[i] == ' ' || map->lmap[i] >= '0' || map->lmap[i] <= '9'
	|| map->lmap[i] == ',' || map->lmap[i] <= 'F' || map->lmap[i] >= 'A'
	|| map->lmap[i] == 'x')
	{
		while (map->lmap[i])
		{
			map->wid += map->lmap[i] == ' ' && !map->hgt ? 1 : 0;
			j += map->lmap[i] == ' ' ? 1 : 0;
			i += map->lmap[i] == ' ' ? 1 : 0;
			if (map->lmap[i] == '\n')
			{
				if (j + 1 != map->wid)
					return (-1);
				j = 0;
				map->hgt++;
			}
			i++;
		}
	}
	else
		return (-1);
	writer(map, 0, 0, 0);
	return (0);
}

int				reader(int fd, t_map *map)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		map->lmap = ft_strjoin(map->lmap, buf);
	}
	return (0);
}

void			*newmap(t_map *map)
{
	map->lmap = ft_strnew(1);
	map->wid = 1;
	map->hgt = 0;
	map->step = 50;
	map->x_s = 800;
	map->y_s = 300;
	map->z_s = 4;
	return (map);
}

void			image_set_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	*(int *)(img->ptr + ((x + y * WIDTH) * img->bits)) = color;
}

static t_img	*new_image(t_map *map)
{
	t_img		*img;

	if ((img = ft_memalloc(sizeof(t_img))) == NULL)
		return (NULL);
	img->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	img->ptr = mlx_get_data_addr(img->image, &img->bits, &img->size_line,
			&img->endian);
	img->bits /= 8;
	return (img);
}

void			clear_image(t_map *map)
{
	ft_bzero(map->img->ptr, WIDTH * HEIGHT * map->img->bits);
}

int				key_press(int keycode, t_map *map)
{
	clear_image(map);
	if (keycode == 69)
		map->step += 1;
	if (keycode == 78)
		map->step -= 1;
	if (keycode == 13)
		map->z_s += 1;
	if (keycode == 1)
		map->z_s -= 1;
	if (keycode == 53)
		exit(0);
	printer(map);
	return (0);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
		return (0);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	newmap(map);
	fd = open(argv[1], O_RDONLY);
	if (reader(fd, map))
	{
		write(1, "read error\n", 12);
		return (0);
	}
	if (valider(map, 0, 0))
	{
		write(1, "invalid map\n", 13);
		return (0);
	}
	if ((map->mlx = mlx_init()) == NULL)
	{
		write(1, "mlx init fail\n", 21);
		return (0);
	}
	if (!(map->wdw = mlx_new_window(map->mlx, WIDTH, HEIGHT, "my awesome fdf")))
	{
		write(1, "mlx window fail\n", 17);
		return (0);
	}
	map->img = new_image(map);
	printer(map);
	mlx_key_hook(map->wdw, key_press, map);
	mlx_loop(map->mlx);
	return (0);
}
