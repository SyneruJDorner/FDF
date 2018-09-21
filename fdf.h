/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 07:19:14 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/27 13:08:10 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WINNAME    "FDF (Fils De Fer)"
# define WINWIDTH 	800
# define WINHEIGHT 	800
# define BUFF_SIZE 8

# define FAILED -1
# define RESET 	0
# define PASS 	1

# define SCROLLINGUP 0
# define SCROLLINGDOWN 1
# define SCROLLINGLEFT 2
# define SCROLLINGRIGHT 3

# include <mlx.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef enum			e_keycode
{
	A = 0,
	B = 11,
	C = 8,
	D = 2,
	E = 14,
	F = 3,
	G = 5,
	H = 4,
	I = 34,
	J = 38,
	K = 40,
	L = 37,
	M = 46,
	N = 45,
	O = 31,
	P = 35,
	Q = 12,
	R = 15,
	S = 1,
	T = 17,
	U = 32,
	V = 9,
	W = 13,
	X = 7,
	Y = 16,
	Z = 6,

	ALPHA1 = 18,
	ALPHA2 = 19,
	ALPHA3 = 20,
	ALPHA4 = 21,
	ALPHA5 = 23,
	ALPHA6 = 22,
	ALPHA7 = 26,
	ALPHA8 = 28,
	ALPHA9 = 25,
	ALPHA0 = 29,

	KEYPAD1 = 83,
	KEYPAD2 = 84,
	KEYPAD3 = 85,
	KEYPAD4 = 86,
	KEYPAD5 = 87,
	KEYPAD6 = 88,
	KEYPAD7 = 89,
	KEYPAD8 = 91,
	KEYPAD9 = 92,
	KEYPAD0 = 82,

	KEYPADPERIOD = 65,
	KEYPADMULTIPLY = 67,
	KEYPADMINUS = 78,
	KEYPADPLUS = 69,
	KEYPADDIVIDE = 75,
	KEYPADENTER = 76,
	KEYPADEQUALS = 81,

	LEFTARROW = 123,
	UPARROW = 126,
	DOWNARROW = 125,
	RIGHTARROW = 124,

	NUMLOCK = 71,
	CAPSLOCK = 272,

	ESCAPE = 53,
	RIGHTSHIFT = 258,
	LEFTSHIFT = 257,
	RIGHTALT = 262,
	LEFTALT = 261,
	RIGHTCTRL = 269,
	LEFTCTRL = 256,
	RIGHTCMD = 260,
	LEFTCMD = 259,
	TAB = 48,
	CALL = 10,
	SPACE = 49,
	ENTER = 36,
	BACKSPACE = 51,
	EQUALS = 24,
	MINUS = 27,

	LEFTBRACKET = 33,
	RIGHTBRACKET = 30,
	SEMICOLON = 41,
	DOUBLEQUOTES = 39,
	BACKSLASH = 42,
	LESSTHAN = 43,
	GREATERTHAN = 47,
	QUESTION = 44,
	DELETE = 117,

	PAGEUP = 116,
	PAGEDOWN = 121,
	PAGETOP = 115,
	PAGEBOTTOM = 119,

	FN = 279,
}						t_keycode;

typedef struct			s_vector3
{
	double				x;
	double				y;
	double				z;
}						t_vector3;

typedef struct			s_mouse
{
	t_vector3			position;
	t_vector3			lastposition;
	int					ismoving;
	int					isleftdown;
	int					isrightdown;
	int					isleftdragging;
	int					isrightdragging;
	int					scrolldirection;
}						t_mouse;

typedef struct			s_keyboard
{
	int					keycode;
	int					lastkeycode;
	int					extendedinputkey;
}						t_keyboard;

typedef struct			s_image
{
	void				*image;
	char				*ptr;
	int					bitsperpixel;
	int					line_size;
	int					endian;
}						t_image;

typedef struct			s_map
{
	int					width;
	int					height;
	t_vector3			position;
	double				depth;
	double				rotationx;
	double				rotationy;
	double				scale;
	int					mindepth;
	int					maxdepth;
	t_vector3			**vectors;
}						t_map;

typedef struct			s_mlx
{
	void				*mlx;
	void				*window;
	t_image				*image;
	t_mouse				mouse;
	t_keyboard			keyboard;
	t_map				*map;
}						t_mlx;

typedef struct			s_linevariables
{
	int					distancex;
	int					distancey;
	int					signx;
	int					signy;
	int					maxdist;
	double				r;
	int					x;
	int					y;
	int					colour;
}						t_linevariables;

int						get_next_line(int const fd, char **line);
int						readmap(int argc, char **argv, t_mlx *mlx);
int						setmap(t_mlx *mlx, t_list *lst, int width, int height);
int						hook_keydown(int key, t_mlx *mlx);
void					initmouse(t_mlx *mlx);
void					initkeyboard(t_mlx *mlx);
void					drawimage(t_mlx *mlx);
void					drawgui(t_mlx *mlx);
void					initimage(t_mlx *mlx);
void					drawline(t_mlx *mlx, t_vector3 from,
		t_vector3 to, int colour);
void					render(t_mlx *mlx);
void					update(t_mlx *mlx);
t_vector3				rotate(t_vector3 point, t_mlx *mlx);
int						cleansplit(char ***split);
#endif
