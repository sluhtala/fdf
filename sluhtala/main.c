/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:03:00 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 19:32:18 by sluhtala         ###   ########.fr       */
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
	data->pnt = transform_scale(*data, 30, 30, 46);
	data->pnt = set_color(data);	
	data->pnt = transform_rotate_z(*data, -30*(M_PI/180));
	data->pnt = transform_rotate_x(*data, 30*(M_PI/180));
	data->pnt = transform_move(*data, 20, 20, 0);
	return (data->pnt);
}

#include <stdio.h>
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
	draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	return (data->pnt);
}
int		input_manager(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == esc_key || key == 12)
		close_program(data);
	if (key == up_key || key == down_key || key == right_key || key == left_key)
	{
		data->pnt = move(key, data);
	}
	if (key == 18)
	{
		printf("parallel\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		data->pnt = proj_parallel(data->pnt, 50 * (M_PI/180), data->lenx, data->leny);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	if (key == 19)
	{
		printf("perspective\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		data->pnt = proj_perspective(data->pnt, 80, data->lenx, data->leny);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	if (key == 20)
	{
		printf("perspective\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		data->pnt = proj_perspective(data->pnt, 110, data->lenx, data->leny);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	return (key);
}

int		main(int argc, char **argv)
{
	t_data d;
	t_data *data;
	t_size map_size;
	t_vec3 **points;
	int fd;

	data = &d;
	if (argc != 2)
		return (0);
	if (!(fd = open(argv[1], O_RDONLY)))
		return (0);
	d.width = 1920 / 2;
	d.length = 1080 /2 ;
	d.pnt = file_manager(fd, &d.lenx, &d.leny);
	data->pnt = set_color(data);
	data->pnt = transformation(data);	
	//print_map(d.pnt, d.lenx, d.leny);
	printf("col...: %#x\n", data->pnt[0][0].color);
	//print_map(d.pnt, d.lenx, d.leny);
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->length, "FDF")))
		return (-1);
	draw_3d_grid(data, data->pnt, d.lenx, d.leny);
	mlx_hook(data->mlx_win, 2, 0, &input_manager, data);
	mlx_loop(data->mlx_ptr);
	
	return (0);
}
