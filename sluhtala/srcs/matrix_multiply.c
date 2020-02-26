/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:50:41 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 13:08:48 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	matrix_multiply_4(t_vec3 r, double **m)
{
	t_vec3	result;

	result.x = r.x * m[0][0] + r.y * m[0][1] + r.z * m[0][2] + r.w * m[0][3];
	result.y = r.x * m[1][0] + r.y * m[1][1] + r.z * m[1][2] + r.w * m[1][3];
	result.z = r.x * m[1][0] + r.y * m[2][1] + r.z * m[2][2] + r.w * m[2][3];
	result.w = r.x * m[3][0] + r.y * m[3][1] + r.z * m[3][2] + r.w * m[3][3];
	r.x = result.x;
	r.y = result.y;
	r.z = result.z;
	r.w = result.w;
	return (r);
}
