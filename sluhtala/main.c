/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:03:00 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 16:54:43 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

int		close_program(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
	return (0);
}

t_vec3 **transformation(t_data *data)
{	
	data->pnt = set_color(data);	
	data->pnt = transform_scale(*data, 20, 20, 1.7);
	data->pnt = transform_rotate_x(*data, 55 * (M_PI / 180));
	data->pnt = transform_rotate_z(*data, 20*(M_PI/180));
	return (data->pnt);
}

static t_vec3	**move(int key, t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	if (key == up_key)
		data->pnt = transform_move(*data, 0, -40, 0);
	if (key == down_key)
		data->pnt = transform_move(*data, 0, 40, 0);
	if (key == right_key)
		data->pnt = transform_move(*data, 40, 0, 0);
	if (key == left_key)
		data->pnt = transform_move(*data, -40, 0, 0);
	draw_grid(data);
	return (data->pnt);
}

void	change_projection(t_data *data, int key)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	if (key == 31 && data->pnt_cpy != NULL)
	{
		free_pnt(data);
		data->pnt = data->pnt_cpy;
		data->pnt_cpy = NULL;
	}
	if (key == 35 && data->pnt_cpy == NULL)
	{
		data->pnt_cpy = copy_pnt(data);
		data->pnt = transform_scale(*data, 1, 1, -1);
		//data->pnt = transform_rotate_y(*data, 90 * (M_PI/180));
		data->pnt = transform_perspective(*data, 100);
	}
	draw_grid(data);
}

/*
**	- esc and q closes the program
**	- 1 scales down and 2 scales up
**	- arrow keys to transform position
**	- o q for orthographic and q for perspective
*/

int		input_manager(int key, t_data *data)
{
	double cent1;
	double cent2;
	double cent3;

	cent1 = ((data->pnt[0][0].x + data->pnt[data->leny - 1][data->lenx - 1].x ) / 2);
	cent2 = ((data->pnt[0][0].y + data->pnt[data->leny - 1][data->lenx - 1].y ) / 2);
	cent3 = ((data->pnt[0][0].z + data->pnt[data->leny - 1][data->lenx - 1].z ) / 2);
	if (key == esc_key || key == 12)
		close_program(data);
	if (key == up_key || key == down_key || key == right_key || key == left_key)
		data->pnt = move(key, data);
	if (key == 18 || key == 19)
	{
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		//data->pnt = transform_move(*data, -cent1, -cent2, -cent3);
		if (key == 18)	
			data->pnt = transform_scale(*data, 0.8, 0.8, 0.8);
		else
			data->pnt = transform_scale(*data, 1.2, 1.2, 1.2);
		//data->pnt = transform_move(*data, cent1, cent2, cent3);
		draw_grid(data);
	}
	if (key == 31 || key == 35)
		change_projection(data, key);
	return (key);
}

/*
**  - Gets points from file
**	- Does transformation
**	- Initialize mlx
**	- Draw lines between the point
*/

int		main(int argc, char **argv)
{
	t_data d;
	t_data *data;
	t_size map_size;
	int fd;

	data = &d;
	if (argc != 2)
		return (0);
	if (!(fd = open(argv[1], O_RDONLY)))
		return (0);
	d.width = 1920 / 2;
	d.length = 1080 /2 ;
	d.pnt = file_manager(fd, &d.lenx, &d.leny);
	d.pnt_cpy = NULL;
	data->pnt = transformation(data);
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->length, "FDF")))
		return (-1);
	draw_grid(data);	
	mlx_hook(data->mlx_win, 2, 0, &input_manager, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
