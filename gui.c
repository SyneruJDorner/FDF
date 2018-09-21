/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 06:34:24 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/27 10:57:12 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BLACK 0x000000
#define RED 0xFF0000
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define SILVER 0xC0C0C0
#define GRAY 0x808080
#define MAROON 0x800000
#define YELLOW 0xFFFF00
#define OLIVE 0x808000
#define LIME 0x00FF00
#define GREEN 0x008000
#define AQUA 0x00FFFF
#define TEAL 0x008080
#define NAVY 0x000080
#define FUCHSIA 0xFF00FF
#define PURPLE 0x800080
#define GUIMOVE "CMD + LEFT MOUSE CLICK = Move"
#define GUIROTATE "CMD + RIGHT MOUSE CLICK = Rotate"
#define GUISCROLL "MOUSE SCROLL = Zoom in/out"

void	drawguitext(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->window, 5, 0, WHITE, "[MOUSE]");
	mlx_string_put(mlx->mlx, mlx->window, 5, 20, WHITE, "Mouse Clicked:");
	if (mlx->mouse.isleftdown > 0)
		mlx_string_put(mlx->mlx, mlx->window, 225, 20, WHITE, "Left Click");
	if (mlx->mouse.isrightdown > 0)
		mlx_string_put(mlx->mlx, mlx->window, 225, 20, WHITE, "Right Click");
	mlx_string_put(mlx->mlx, mlx->window, 5, 40, WHITE, "Dragging Mouse:");
	if (mlx->mouse.isrightdragging > 0 || mlx->mouse.isleftdragging > 0)
		mlx_string_put(mlx->mlx, mlx->window, 225, 40, WHITE, "True");
	mlx_string_put(mlx->mlx, mlx->window, 5, 80, WHITE, "[CONTROLS]");
	mlx_string_put(mlx->mlx, mlx->window, 5, 100, WHITE, GUIMOVE);
	mlx_string_put(mlx->mlx, mlx->window, 5, 120, WHITE, GUIROTATE);
	mlx_string_put(mlx->mlx, mlx->window, 5, 140, WHITE, GUISCROLL);
}

int		realtimelinerender(t_mlx *mlx)
{
	t_vector3	up;
	t_vector3	down;
	t_vector3	left;
	t_vector3	right;
	int			amount;

	amount = 10;
	if (mlx->image != NULL)
		ft_bzero(mlx->image->ptr, WINWIDTH * WINHEIGHT
				* mlx->image->bitsperpixel);
	up.x = mlx->mouse.position.x + amount;
	up.y = mlx->mouse.position.y;
	down.x = mlx->mouse.position.x - amount;
	down.y = mlx->mouse.position.y;
	left.x = mlx->mouse.position.x;
	left.y = mlx->mouse.position.y - amount;
	right.x = mlx->mouse.position.x;
	right.y = mlx->mouse.position.y + amount;
	drawline(mlx, mlx->mouse.position, up, 0xFFFFFF);
	drawline(mlx, mlx->mouse.position, down, 0xFFFFFF);
	drawline(mlx, mlx->mouse.position, left, 0xFFFFFF);
	drawline(mlx, mlx->mouse.position, right, 0xFFFFFF);
	return (0);
}

void	inputtransform(t_mlx *mlx)
{
	static int			determineddist = 0;
	static t_vector3	distance;

	if (mlx->mouse.isrightdown == TRUE)
	{
		mlx->map->rotationx += (mlx->mouse.lastposition.y -
				mlx->mouse.position.y) / 200.0f;
		mlx->map->rotationy -= (mlx->mouse.lastposition.x -
				mlx->mouse.position.x) / 200.0f;
	}
	else if (mlx->mouse.isleftdown == TRUE)
	{
		if (determineddist == 0)
		{
			distance.x = mlx->mouse.position.x - mlx->map->position.x;
			distance.y = mlx->mouse.position.y - mlx->map->position.y;
			determineddist = 1;
		}
		mlx->map->position.x = mlx->mouse.position.x - distance.x;
		mlx->map->position.y = mlx->mouse.position.y - distance.y;
	}
	else
		determineddist = 0;
}

void	inputs(t_mlx *mlx)
{
	if (mlx->keyboard.keycode == KEYPADPLUS)
		mlx->map->depth = (mlx->map->depth < mlx->map->maxdepth) ?
			(mlx->map->depth + 0.1f) : mlx->map->maxdepth;
	if (mlx->keyboard.keycode == KEYPADMINUS)
		mlx->map->depth = (mlx->map->depth > mlx->map->mindepth) ?
			(mlx->map->depth - 0.1f) : mlx->map->mindepth;
	if (mlx->mouse.scrolldirection == SCROLLINGUP)
		(mlx->map->scale < 500) ? (mlx->map->scale *= 1.1f) : 500;
	if (mlx->mouse.scrolldirection == SCROLLINGDOWN)
		(mlx->map->scale > 1) ? (mlx->map->scale /= 1.1f) : 1;
	mlx->mouse.scrolldirection = -1;
	if (mlx->keyboard.keycode == LEFTCMD)
		inputtransform(mlx);
	if (mlx->mouse.lastposition.x != mlx->mouse.position.x ||
			mlx->mouse.lastposition.y != mlx->mouse.position.y)
		mlx->mouse.ismoving = 1;
	mlx->mouse.ismoving = 0;
	mlx->mouse.lastposition.x = mlx->mouse.position.x;
	mlx->mouse.lastposition.y = mlx->mouse.position.y;
}

void	drawgui(t_mlx *mlx)
{
	inputs(mlx);
	mlx_clear_window(mlx->mlx, mlx->window);
	if (mlx->image != NULL)
		ft_bzero(mlx->image->ptr,
				WINWIDTH * WINHEIGHT * mlx->image->bitsperpixel);
	realtimelinerender(mlx);
	render(mlx);
	drawguitext(mlx);
}
