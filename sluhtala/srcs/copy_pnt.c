/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_pnt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:54:22 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 13:13:56 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_pnt(t_data *data)
{
	int y;

	y = 0;
	while (y < data->leny)
	{
		free(data->pnt[y]);
		y++;
	}
	free(data->pnt);
	data->pnt = NULL;
}

t_vec3	**copy_pnt(t_data *data)
{
	t_vec3 **cpy;
	int i;
	int y;

	if (!(cpy = (t_vec3**)malloc(sizeof(t_vec3*) * data->leny)))
		error_manager("Malloc error.");
	y = 0;
	while (y < data->leny)
	{
		if (!(cpy[y] = (t_vec3*)malloc(sizeof(t_vec3) * data->lenx)))
			error_manager("Malloc error.");
		i = 0;
		while (i < data->lenx)
		{
			cpy[y][i].x = data->pnt[y][i].x;
			cpy[y][i].y = data->pnt[y][i].y;
			cpy[y][i].z = data->pnt[y][i].z;
			cpy[y][i].w = data->pnt[y][i].w;
			cpy[y][i].color = data->pnt[y][i].color;
			i++;
		}
		y++;
	}
	return (cpy);
}
