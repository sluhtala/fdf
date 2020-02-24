/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:19:55 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 19:34:40 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3 **normalize_pnt(t_data data)
{
	int i;
	int y;
	double d;

	y = 0;
	while (y < data.leny)
	{
		i = 0;
		while (i < data.lenx)
		{
			d = sqrt(data.pnt[y][i].x * data.pnt[y][i].x + data.pnt[y][i].y *
				data.pnt[y][i].y);
			if (d != 0)
			{
				data.pnt[y][i].x = data.pnt[y][i].x / d;
				data.pnt[y][i].y = data.pnt[y][i].y / d;
				data.pnt[y][i].z = data.pnt[y][i].z / d;
			}
			i++;
		}
		y++;
	}
	return (data.pnt);
}

static t_vec3 **raster(t_vec3 **pnt, t_data data)
{
	int i;
	int y;
	double w;
	double l;

	w = data.width;
	l = data.length;
	y = 0;
	while (y < data.leny)
	{
		i = 0;
		while (i < data.lenx)
		{
			pnt[y][i].x = pnt[y][i].x * (w / l);
			pnt[y][i].y = pnt[y][i].y * (w / l);
			pnt[y][i].z = pnt[y][i].z * (w / l);
			i++;
		}
		y++;
	}
	return (pnt);
}
