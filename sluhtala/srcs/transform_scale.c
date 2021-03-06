/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:41:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 12:35:52 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	**make_smatrix(double x, double y, double z)
{
	double	**tmat;

	tmat = matrix_alloc();
	tmat[0][0] = x;
	tmat[0][1] = 0.0;
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = 0.0;
	tmat[1][1] = y;
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = z;
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return (tmat);
}

static void		free_matrix(double ***m)
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

t_vec3			**transform_scale(t_data data, double x, double y, double z)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_smatrix(x, y, z);
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
