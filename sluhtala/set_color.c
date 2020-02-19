

#include "fdf.h"
#include <stdio.h>

static void get_minmax(t_data *data, int *min, int *max)
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

t_vec3	**set_color(t_data *data)
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
