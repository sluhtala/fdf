/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:52:50 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 16:57:05 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			**matrix_alloc(void)
{
	double	**mat;

	if (!(mat = (double**)malloc(sizeof(double*) * 4)))
		error_manager("Malloc error.");
	if (!(mat[0] = (double*)malloc(sizeof(double) * 4)))
		error_manager("Malloc error.");
	if (!(mat[1] = (double*)malloc(sizeof(double) * 4)))
		error_manager("Malloc error.");
	if (!(mat[2] = (double*)malloc(sizeof(double) * 4)))
		error_manager("Malloc error.");
	if (!(mat[3] = (double*)malloc(sizeof(double) * 4)))
		error_manager("Malloc error.");
	return (mat);
}

static double	**make_persmatrix(double s, double near, double far, double ar)
{
	double	**tmat;

	tmat = matrix_alloc();
	tmat[0][0] = s * ar;
	tmat[0][1] = 0;
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = 0.0;
	tmat[1][1] = s;
	tmat[1][2] = 0;
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = -far / (far - near);
	tmat[2][3] = -1;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = -(far * near) / (far - near);
	tmat[3][3] = 0;
	return(tmat);
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

static	t_vec3	get_multiply(double **m, t_data data, int y, int i)
{
	data.pnt[y][i] = matrix_multiply_4(data.pnt[y][i], m);
	if (data.pnt[y][i].w != 1 && data.pnt[y][i].w != 0)
	{
		data.pnt[y][i].x /= data.pnt[y][i].w;
		data.pnt[y][i].y /= data.pnt[y][i].w;
		data.pnt[y][i].z /= data.pnt[y][i].w;
	}
	return (data.pnt[y][i]);
}
t_vec3			**transform_perspective(t_data data, double fov)
{
	int		i;
	int		y;
	double	near;
	double	far;
	double	**m;

	near = 1;
	far = 100;
	fov = (tan((fov / 2) * (M_PI / 180)));
	y = 0;
	data.pnt = normalize_pnt(data);
	m = make_persmatrix(fov, near, far, data.width / data.length);
	while (y < data.leny)
	{
		i = 0;
		while (i < data.lenx)
		{
			data.pnt[y][i] = get_multiply(m, data, y, i);
			i++;
		}
		y++;
	}
	free_matrix(&m);
	return (data.pnt);
}
