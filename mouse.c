/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 09:04:09 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/24 12:21:33 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define SCROLLDOWN 4
#define SCROLLUP 5
#define SCROLLRIGHT 6
#define SCROLLLEFT 7
#define MOUSE_BEGIN 4
#define MOUSE_END 5
#define MOUSE_MOVE 6

void	mouse_scroll(int button, int x, int y, t_mlx *mlx)
{
	if (mlx->mouse.scrolldirection != -1)
	{
		mlx->mouse.scrolldirection = -1;
		return ;
	}
	if (button == SCROLLDOWN)
		mlx->mouse.scrolldirection = SCROLLINGDOWN;
	else if (button == SCROLLUP)
		mlx->mouse.scrolldirection = SCROLLINGUP;
	else if (button == SCROLLRIGHT)
		mlx->mouse.scrolldirection = SCROLLINGRIGHT;
	else if (button == SCROLLLEFT)
		mlx->mouse.scrolldirection = SCROLLINGLEFT;
}

int		mouse_begin(int button, int x, int y, t_mlx *mlx)
{
	mouse_scroll(button, x, y, mlx);
	if (button == LEFT_CLICK)
		mlx->mouse.isleftdown = TRUE;
	if (button == RIGHT_CLICK)
		mlx->mouse.isrightdown = TRUE;
	drawgui(mlx);
	return (0);
}

int		mouse_end(int button, int x, int y, t_mlx *mlx)
{
	if (button == LEFT_CLICK)
		mlx->mouse.isleftdown = FALSE;
	if (button == RIGHT_CLICK)
		mlx->mouse.isrightdown = FALSE;
	if (mlx->mouse.isleftdown == FALSE)
		mlx->mouse.isleftdragging = FALSE;
	if (mlx->mouse.isrightdown == FALSE)
		mlx->mouse.isrightdown = FALSE;
	drawgui(mlx);
	return (0);
}

int		mouse_move(int x, int y, t_mlx *mlx)
{
	if (((x >= 0 && x <= WINWIDTH) && (y >= 0 && y <= WINHEIGHT)))
	{
		mlx->mouse.position.x = x;
		mlx->mouse.position.y = y;
		if (mlx->mouse.isleftdown == TRUE)
		{
			mlx->mouse.isleftdragging = TRUE;
			drawgui(mlx);
			return (0);
		}
		else if (mlx->mouse.isrightdown == TRUE)
		{
			mlx->mouse.isrightdragging = TRUE;
			drawgui(mlx);
			return (0);
		}
	}
	mlx->mouse.isleftdragging = FALSE;
	mlx->mouse.isrightdragging = FALSE;
	drawgui(mlx);
	return (1);
}

void	initmouse(t_mlx *mlx)
{
	mlx_hook(mlx->window, MOUSE_BEGIN, 0, &mouse_begin, mlx);
	mlx_hook(mlx->window, MOUSE_MOVE, 0, &mouse_move, mlx);
	mlx_hook(mlx->window, MOUSE_END, 0, &mouse_end, mlx);
}
