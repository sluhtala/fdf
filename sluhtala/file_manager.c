/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:23 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 14:25:37 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static void		free_splitted(char ***split)
{
	int i;

	if (!(*split))
		return ;
	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
}

static int		split_len(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

/*
** I combined len and i to get ilen[2] to save 1 line
** This reads rows from the map using ft_split and
** stores the data to pnt
*/

static t_vec3	*make_points(t_vec3 **pnt, char **map,
		int *lenx, int y)
{
	char	**temp;
	int		ilen[2];

	ilen[0] = 0;
	while ((*map)[ilen[0]] != '\n' && (*map)[ilen[0]])
		ilen[0]++;
	(*map)[ilen[0]] = '\0';
	temp = ft_split(*map);
	*map = *map + ilen[0] + 1;
	if ((ilen[1] = split_len(temp)) != *lenx && *lenx != 0)
		error_manager("Not valid map.");
	*lenx = ilen[1];
	if (!(pnt[y] = (t_vec3*)malloc(sizeof(t_vec3) * *lenx)))
		error_manager("Malloc error.");
	ilen[0] = 0;
	while (ilen[0] < *lenx)
	{
		pnt[y][ilen[0]].x = (double)ilen[0];
		pnt[y][ilen[0]].y = (double)y;
		pnt[y][ilen[0]].z = (double)ft_atoi(temp[ilen[0]]);
		pnt[y][ilen[0]].w = 1;
		ilen[0]++;
	}
	free_splitted(&temp);
	return (pnt[y]);
}

static t_vec3	**get_coords(char *map, int *xlen, int *ylen)
{
	t_vec3	**points;
	int		y;

	y = 0;
	*ylen = 0;
	*xlen = 0;
	while (map[y])
	{
		if (map[y] == '\n')
			*ylen = *ylen + 1;
		y++;
	}
	if (!(points = (t_vec3**)malloc(sizeof(t_vec3*) * *ylen)))
		error_manager("Malloc error.");
	y = 0;
	while (y < *ylen)
	{
		points[y] = make_points(points, &map, xlen, y);
		y++;
	}
	return (points);
}

t_vec3			**file_manager(int fd, int *lenx, int *leny)
{
	char		*map;
	char		*temp;
	char		buf[42 + 1];
	int			ret;
	t_vec3		**points;

	map = ft_strnew(1);
	while ((ret = read(fd, buf, 42)) > 0)
	{
		temp = map;
		buf[ret] = '\0';
		map = ft_strjoin(map, buf);
		free(temp);
	}
	points = get_coords(map, lenx, leny);
	free(map);
	map = NULL;
	return (points);
}
