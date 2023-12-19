/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:18:10 by mjales            #+#    #+#             */
/*   Updated: 2023/12/19 19:48:26 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// #define map_width 8
// #define map_height 8
# define SCREENWIDTH 600
# define SCREENHEIGHT 512
# define SCREEN2HEIGHT 320
# define RAYNBR 60

# define PLAYERSIZE 8
# define CUBESIZE 64

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../mlx_linux/mlx.h"
# include "string.h"

# define PI 3.1415926535
# define P2 1.57079632679
# define P3 4.71238898038
# define DR 0.0174533
# define FOV 60

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
	double	x;
	double	y;
	int		size;
	double	angle;
	double	delta_x;
	double	delta_y;
	int		startx;
	int		starty;
	char	orientation;
}	t_player;

typedef struct s_var
{
	t_win		*win;
	t_img		wall;
	t_img		floor;
	t_img		ceil_img;
	t_img		floor_img;
	t_img		teste;
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	int			fcolor;
	int			ccolor;
	t_player	*player;
	int			map[100][100];
	int			map_width;
	int			map_height;
	t_img		map_img;
	t_img		mini_map;
	t_img		rays;
	int			r;
	int			mx;
	int			my;
	int			mp;
	int			dof;
	double		rx;
	double		ry;
	double		ra;
	double		xo;
	double		yo;
	double		dist;
	double		disth;
	double		atan;
	double		ntan;
	double		distv;
	double		vx;
	double		vy;
	double		hx;
	double		hy;
	int			color_wall;
	float		ca;
	float		line_h;
	float		ty_step;
	float		ty;
	float		tx;
	float		ty_off;
	float		shade;
	int			pix_size;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;

}	t_var;

typedef struct s_position
{
	int	x;
	int	y;
	int	color;
}	t_position;

t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h, t_win window);
void	put_pixel_img(t_img img, int x, int y, int color);
int		key_hook(int keycode);
int		mouse_hook(int keycode);
int		exit_program(void);
t_var	*vars(void);
int		gen_trgb(int opacity, int red, int green, int blue);
t_win	new_program(int w, int h, char *str);

int		map_color(int intensity, int max);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		put_image(void);
void	verLine(int x, int y1, int y2, int color);

// MOVE
void	draw_player(t_img img, int size, int color, double x, double y);
void	draw_square(t_img img, int size, t_position pos);
void	fill_image(t_img img, int color);
void	draw_rectagle(int x, int y, int width, int height, int color);

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

void	draw_map(void);
void	draw_orientation(int size, int color);
void	drawRays2D(t_win window);
double	distance(int ax, int ay, int bx, int by);

int		get_pixel_img(t_img img, int pixel);
void	img_teste(t_img *img, char *path);

void	parser(char *filename);
int		check_format(const char *nome_arquivo);

#endif
