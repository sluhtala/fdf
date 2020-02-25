/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_rotate_matrices.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:50:44 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 14:51:43 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double **make_xmatrix(double a)
{
	double	**tmat;

	tmat = matrix_alloc();
	tmat[0][0] = 1;
	tmat[0][1] = 0;
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = 0;
	tmat[1][1] = cos(a);
	tmat[1][2] = -sin(a);
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = sin(a);
	tmat[2][2] = cos(a);
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return(tmat);
}

double **make_ymatrix(double a)
{
	double	**tmat;

	tmat = matrix_alloc();
	tmat[0][0] = cos(a);
	tmat[0][1] = 0;
	tmat[0][2] = sin(a);
	tmat[0][3] = 0;
	tmat[1][0] = 0;
	tmat[1][1] = 1;
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = -sin(a);
	tmat[2][1] = 0.0;
	tmat[2][2] = cos(a);
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return(tmat);
}

double **make_zmatrix(double a)
{
	double	**tmat;

	tmat = matrix_alloc();
	tmat[0][0] = cos(a);
	tmat[0][1] = -sin(a);
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = sin(a);
	tmat[1][1] = cos(a);
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = 1;
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return(tmat);
}
