/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:26:05 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 14:33:44 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		get_minmax(t_data *data, int *min, int *max)
{
	int i;
	int j;

	*min = 100000000;
	*max = -100000000;
	j = 0;
	while (j < data->leny)
	{
		i = 0;
		while (i < data->lenx)
		{
			if (data->pnt[j][i].z > (double)*max)
				*max = (int)data->pnt[j][i].z;
			if (data->pnt[j][i].z < (double)*min)
				*min = (int)data->pnt[j][i].z;
			i++;
		}
		j++;
	}
	if (*max == 0)
		*max = 1;
}

/*
** Finds the right color value for each point.
** First find the minimum and maximum z value.
** Even if we have negative values it always starts from white
** relation of z and maxmin distance can be multiplied with 255
** now we can minus that from 255.
*/

t_vec3			**set_color(t_data *data)
{
	int max;
	int min;
	int col;
	int i;
	int j;

	get_minmax(data, &min, &max);
	j = 0;
	while (j < data->leny)
	{
		i = 0;
		while (i < data->lenx)
		{
			data->pnt[j][i].color = 0xff - 0xff * ((data->pnt[j][i].z - min) /
			(max - min));
			if (data->pnt[j][i].color > 255)
				data->pnt[j][i].color = 255;
			i++;
		}
		j++;
	}
	return (data->pnt);
}
