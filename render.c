/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 08:08:37 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/27 11:15:30 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	rotate(t_vector3 point, t_mlx *mlx)
{
	t_vector3	vector;
	double		x;
	double		y;
	double		z;

	x = point.x;
	z = point.z;
	vector.x = cos(mlx->map->rotationy) * x + sin(mlx->map->rotationy) * z;
	vector.z = -sin(mlx->map->rotationy) * x + cos(mlx->map->rotationy) * z;
	y = point.y;
	z = vector.z;
	vector.y = cos(mlx->map->rotationx) * y - sin(mlx->map->rotationx) * z;
	return (vector);
}

void		setpivot(t_vector3 *vector, t_mlx *mlx)
{
	vector->x -= (double)(mlx->map->width - 1) / 2.0f;
	vector->y -= (double)(mlx->map->height - 1) / 2.0f;
}

t_vector3	apply_transform(t_vector3 vector, t_mlx *mlx)
{
	vector.z *= mlx->map->depth;
	setpivot(&vector, mlx);
	vector = rotate(vector, mlx);
	vector.x *= mlx->map->scale;
	vector.y *= mlx->map->scale;
	vector.x += mlx->map->position.x;
	vector.y += mlx->map->position.y;
	return (vector);
}

void		drawlineforvectors(t_mlx *mlx, t_map *map, int x, int y)
{
	t_vector3	vector;
	t_vector3	fromvector;

	fromvector = apply_transform(*map->vectors[y * map->width + x], mlx);
	if (x < map->width - 1)
	{
		vector = apply_transform(
				*map->vectors[y * map->width + (x + 1)], mlx);
		drawline(mlx, fromvector, vector, 0xFFFFFF);
	}
	if (y < map->height - 1)
	{
		vector = apply_transform(
				*map->vectors[(y + 1) * map->width + x], mlx);
		drawline(mlx, fromvector, vector, 0xFFFFFF);
	}
}

void		render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector3	vector;
	t_map		*map;

	map = mlx->map;
	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
			drawlineforvectors(mlx, map, x, y);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}
