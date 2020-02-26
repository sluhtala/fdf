/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:19:55 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 13:07:15 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	**normalize_pnt(t_data data)
{
	int		i;
	int		y;
	double	d;

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
