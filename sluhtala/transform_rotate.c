/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:45:52 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 14:53:16 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_matrix(double ***m)
{
	int i;

	if (!*m)
		return ;
	i = 0;
	while (i < 4)
	{
		free((*m)[i]);
		i++;
	}
	free(*m);
}

t_vec3 **transform_rotate_x(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_xmatrix(a);
	while (ynx < data.leny)
	{
		inx = 0;
		while (inx < data.lenx)
		{
			data.pnt[ynx][inx] = matrix_multiply_4(data.pnt[ynx][inx], m);
			inx++;
		}
		ynx++;
	}
	free_matrix(&m);
	return (data.pnt);
}

t_vec3 **transform_rotate_y(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_ymatrix(a);
	while (ynx < data.leny)
	{
		inx = 0;
		while (inx < data.lenx)
		{
			data.pnt[ynx][inx] = matrix_multiply_4(data.pnt[ynx][inx], m);
			inx++;
		}
		ynx++;
	}
	free_matrix(&m);
	return (data.pnt);
}

t_vec3 **transform_rotate_z(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_zmatrix(a);
	while (ynx < data.leny)
	{
		inx = 0;
		while (inx < data.lenx)
		{
			data.pnt[ynx][inx] = matrix_multiply_4(data.pnt[ynx][inx], m);
			inx++;
		}
		ynx++;
	}
	free_matrix(&m);
	return (data.pnt);
}
