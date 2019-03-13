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

t_point		*new_point(void)
{
	t_point		*new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = 0;
	new->y = 0;
	new->z = 0;
	new->color = 0xFFFFFF;
	return (new);
}

void	writer(t_map *map, int i, int j, int k)
{
	while (map->lmap[i])
	{
		if (map->lmap[i] >= '0' && map->lmap[i] <= '9')
		{
			map->point[j][k++]->z = ft_atoi(&map->lmap[i]);
			while (map->lmap[i] >= '0' && map->lmap[i] <= '9')
				i++;
		}
		if (map->lmap[i] == '\n')
		{
			j++;
			k = 0;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < map->hgt)
	{
		while (j < map->wid)
		{
			printf("%3.0f ", map->point[i][j]->z);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	exit (0);
}

void	valider(t_map *map, int i, int j)
{
	while (map->lmap[i])
	{
		if (map->lmap[i] == ' ' && map->hgt == 0)
			map->wid++;
		if (map->lmap[i] == ' ')
			i++; 
		if (map->lmap[i] == '\n')
			map->hgt++;
		i++;
	}
	printf("WID = %d\nHGT = %d\n", map->wid, map->hgt);
	i = 0;
	map->point = (t_point ***)malloc(sizeof(t_point **) * (map->hgt));
	while (i <= map->hgt)
	{
		map->point[i] = (t_point **)malloc(sizeof(t_point *) * (map->wid));
		while (j <= map->wid)
		{
			map->point[i][j] = new_point();
			j++;
		}
		j = 0;
		i++;
	}
	writer(map, 0, 0, 0);
}

int		reader(int fd, t_map *map)
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

void	*newmap(t_map *map)
{
	map->lmap = ft_strnew(1);
	map->wid = 1;
	map->hgt = 0;
	map->step = 10;
	map->x_s = 0;
	map->y_s = 0;
	map->z_s = 2;
	return (map);
}

void	image_set_pixel(t_img *img, int x, int y, int color)
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

int		main(int argc, char **argv)
{
	int		fd;
	t_map	map;

	if (argc != 2)
		return (0);
	newmap(&map);
	fd = open(argv[1], O_RDONLY);
	if(reader(fd, &map))
	{
		write(1, "read error\n", 12);
		return (0);
	}
	valider(&map, 0, 0);
	if ((map.mlx = mlx_init()) == NULL)
	{
		write(1, "mlx init fail\n", 21);
		return (0);
	}
	map.wdw = mlx_new_window(map.mlx, WIDTH, HEIGHT, "my awesome fdf");
	map.img = new_image(&map);
	printer(&map);
	mlx_loop(map.mlx);
	return (0);
}
