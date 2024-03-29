/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:18:10 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 19:04:12 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREENWIDTH 600
# define SCREENHEIGHT 512
# define SCREEN2HEIGHT 320
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
# define FOV 60
# define MAXSIZE 100

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
	int			red;
	int			green;
	int			blue;
	int			segment_count;
	const char	*segment_start;
	const char	*segment_end;
	t_img		canvas;
	double		dr;
	int			tes[6];
}	t_var;

typedef struct s_position
{
	int	x;
	int	y;
	int	color;
}	t_pos;

t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h, t_win window);
void	put_pixel_img(t_img img, int x, int y, int color);
int		key_hook(int keycode);
int		mouse_hook(int keycode);
int		exit_program(int exit_status);
t_var	*vars(void);
int		gen_trgb(int opacity, int red, int green, int blue);
t_win	new_program(int w, int h, char *str);
int		map_color(int intensity, int max);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		put_image(void);
void	verLine(int x, int y1, int y2, int color);
void	draw_wall(t_pos pos, int i, int j, int mini_cube_size);
void	draw_empty(t_pos pos, int i, int j, int mini_cube_size);
void	draw_square(t_img img, int size, t_pos pos);
void	fill_image(t_img img, int color);
void	draw_rectagle(int width, int height, t_pos pos);
void	init_vars(void);
void	horizontal_check(double ra);
void	wall_color(void);
void	vertical_check(double ra);
void	initialize_game(char *file_path);
void	setup_player(void);
t_pos	initialize_player_position(void);
void	create_squares(t_win window);
void	draw_player_and_rays(t_win window);
void	handle_hooks_and_put_image(t_win window, t_img player_img);
void	line_vars(t_pos pos, int x1, int y1);
void	look_up_or_down(double ra);
void	look_left_or_right(double ra);
void	left_or_right(double ra);
void	up_or_down(double ra);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	init_colors(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrchr(const char *str, int c);
void	print_map(void);
int		check_grid(void);
int		validate_string(char *input_str);
int		get_width(char *input_str);
int		convert_to_int(const char *start, const char *end);
int		p_string_aux(const char *current_char);
int		process_string(char *str);
int		is_valid_character(char current_char);
void	validate_aux(char current_char, int index);
int		char_to_int(char chr);
int		render_hook(void);
int		check_string(char *input_str);
void	create_images(void);
void	draw_3d_walls(void);
void	handle_exit(int keycode);
int		check_images(void);

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
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

void	draw_map(void);
void	draw_orientation(int size, int color);
void	draw_rays_2d(t_win window);
double	distance(int ax, int ay, int bx, int by);

int		get_pixel_img(t_img img, int pixel);
void	img_teste(t_img *img, char *path, char *line);

void	parser(char *filename);
int		check_format(const char *nome_arquivo);

#endif
