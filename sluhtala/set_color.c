

#include "fdf.h"
#include <stdio.h>
t_vec3	**set_color(t_data *data)
{
	int lenx;
	int leny;
	int col;
	int i;
	int j;

	j = 0;
	lenx = data->lenx;	
	leny = data->leny;
	while (j < leny)
	{
		i = 0;
		while (i < lenx)
		{
			data->pnt[j][i].color = 0xff - 0xff * (data->pnt[j][i].z / 100);
			//printf("i:%d j:%d col: %#x\n", i, j, data->pnt[j][i].color);
			i++;
		}
		j++;
	}
	printf("col.: %#x\n", data->pnt[0][0].color);
	return (data->pnt);
}
