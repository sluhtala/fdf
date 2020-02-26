/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:23:43 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 13:04:52 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	point_on_image(t_data *data, int p[2])
{
	int w;
	int h;

	w = data->width;
	h = data->length;
	if (p[0] <= w && p[0] >= 0 && p[1] <= h && p[1] >= 0)
	{
		return (1);
	}
	return (0);
}

static void	draw_vertical(t_data *data, t_vec3 **point, int lenx, int leny)
{
	int		i;
	int		y;
	int		p1[2];
	int		p2[2];
	double	col[2];

	y = 1;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			p1[0] = (int)point[y - 1][i].x + data->img_posx;
			p1[1] = (int)point[y - 1][i].y + data->img_posy;
			p2[0] = (int)point[y][i].x + data->img_posx;
			p2[1] = (int)point[y][i].y + data->img_posy;
			col[0] = (double)data->pnt[y - 1][i].color;
			col[1] = (double)data->pnt[y][i].color;
			if (point_on_image(data, p1) || point_on_image(data, p2))
				draw_line(data, p1, p2, col);
			i++;
		}
		y++;
	}
}

static void	draw_horizontal(t_data *data, t_vec3 **point, int lenx, int leny)
{
	int		i;
	int		y;
	int		p1[2];
	int		p2[2];
	double	col[2];

	y = 0;
	while (y < leny)
	{
		i = 1;
		while (i < lenx)
		{
			p1[0] = (int)point[y][i - 1].x + data->img_posx;
			p1[1] = (int)point[y][i - 1].y + data->img_posy;
			p2[0] = (int)point[y][i].x + data->img_posx;
			p2[1] = (int)point[y][i].y + data->img_posy;
			col[0] = (double)data->pnt[y][i - 1].color;
			col[1] = (double)data->pnt[y][i].color;
			if (point_on_image(data, p1) || point_on_image(data, p2))
				draw_line(data, p1, p2, col);
			i++;
		}
		y++;
	}
}

void		draw_grid(t_data *data)
{
	int		lenx;
	int		leny;
	t_vec3	**point;

	point = data->pnt;
	lenx = data->lenx;
	leny = data->leny;
	if (lenx == 1 && leny == 1)
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, data->pnt[0][0].x +
		data->img_posx, data->pnt[0][0].y + data->img_posy, 0xff0000);
		return ;
	}
	draw_horizontal(data, point, lenx, leny);
	draw_vertical(data, point, lenx, leny);
}
