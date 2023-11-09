/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:18:10 by mjales            #+#    #+#             */
/*   Updated: 2023/10/04 12:14:36 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3D_H
# define cub3D_H

#define mapWidth 8
#define mapHeight 8
#define screenWidth 1024
#define screenHeight 512
#define screen2height 320

#define playerSize 8
#define cubeSize 64

# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# include<stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../mlx_linux/mlx.h"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533
#define FOV 60

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}	t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_player
{
	t_img	img;
	double		x;
	double		y;
	int 	size;
	double	angle;
	double 	deltaX;
	double 	deltaY;
}	t_player;

typedef struct s_var
{
	t_win		*win;
	t_img		wall;
	t_img		floor;
	t_img 		teste;
	t_player	*player;
	int			map[mapWidth][mapHeight];
	t_img 		rays;
}	t_var;

t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h, t_win window);
void	put_pixel_img(t_img img, int x, int y, int color);
int		key_hook(int keycode, t_var *vars);
int		mouse_hook(int keycode);
int		exit_program(t_var *vars);
t_var	*vars(void);
int		gen_trgb(int opacity, int red, int green, int blue);
t_win	new_program(int w, int h, char *str);

int		map_color(int intensity, int max);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		put_image(void);
void	verLine(int x, int y1, int y2, int color);

// MOVE
void 	draw_player(t_img img,int size, int color, double x, double y);
void 	draw_square(t_img img,int size, int color);

// CUB3D

// # define KEY_UP 		126
// # define KEY_DOWN		125
// # define KEY_LEFT		123
// # define KEY_RIGHT		124
// # define ESC_KEY		53
// # define BACKSPACE		51
// # define W_KEY			13
// # define A_KEY			0
// # define S_KEY			1
// # define D_KEY			2

# define ESC_KEY_M 65307
# define CROSS -16778144
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define KEY_LEFT_M 65361
# define KEY_UP_M 65362
# define KEY_DOWN_M 65364
# define KEY_RIGHT_M 65363

void draw_map(void);
void draw_orientation(int size, int color);
void drawRays2D(t_win window);
double distance(int ax, int ay, int bx, int by);

int get_pixel_img(t_img img, int pixel);
void img_teste(void);

#endif
