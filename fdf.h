/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstannis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 08:09:55 by sstannis          #+#    #+#             */
/*   Updated: 2019/02/24 08:09:57 by sstannis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "./miniLibX/mlx.h"
# include "stdio.h"
# define WIDTH 1600
# define HEIGHT 1200
# define CHN(y) if ((y) == 0) return (-1)
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_img
{
	void		*image;
	void		*ptr;
	int			bits;
	int			size_line;
	int			endian;
}					t_img;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_point;

typedef struct s_map
{
    char    	*lmap;
    int     	wid;
    int     	hgt;
	int			**imap;
	void		*mlx;
	void		*wdw;
    int			x0;
	int			y0;
	int			x1;
	int			y1;
    int			x_s;
	int			y_s;
	int			z_s;
    int			step;
    int         sign_x;
    int         sign_y;
	t_img		*img;
	t_point		***point;
}   t_map;

int     main(int argc, char **argv);
void	printer(t_map *map);
void	image_set_pixel(t_img *img, int x, int y, int color);
int 	ft_atoi_base(const char *str, int str_base);

#endif
