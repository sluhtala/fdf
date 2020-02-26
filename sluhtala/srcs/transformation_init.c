/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:38:51 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 12:57:43 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	**transformation(t_data *data)
{
	data->img_posx = SCREENCENTER_X / 2;
	data->img_posy = SCREENCENTER_Y / 2;
	data->scale = 0;
	data->pnt = set_color(data);
	data->pnt = transform_scale(*data, 20, 20, 5.5);
	data->pnt = transform_rotate_x(*data, 45 * (M_PI / 180));
	data->pnt = transform_rotate_y(*data, 5 * (M_PI / 180));
	data->pnt = transform_rotate_z(*data, 10 * (M_PI / 180));
	return (data->pnt);
}
