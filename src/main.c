/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/12/18 13:27:53 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

t_var	*vars(void)
{
	static t_var	va;

	return (&va);
}

void draw_square(t_img img, int size, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(img, i + x, j + y, color);
			j++;
		}
		i++;
	}
}



void	draw_line(int x, int y, int x1, int y1, int color)
{
	(void)color;
	int dx = abs(x1 - x);
	int sx = x < x1 ? 1 : -1;
	int dy = -abs(y1 - y);
	int sy = y < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, x, y, color);
		if (x == x1 && y == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void	draw_orientation(int size, int color)
{
	int	x1;
	int	y1;

	(void)size;
	x1 = vars()->player->x + vars()->player->delta_x * 5;
	y1 = vars()->player->y + vars()->player->delta_y * 5;
	draw_line(vars()->player->x, vars()->player->y, x1, y1, color);
}

void	draw_reverse(int size, int color)
{
	int	x1;
	int	y1;

	(void)size;
	x1 = vars()->player->x - vars()->player->delta_x * 5;
	y1 = vars()->player->y - vars()->player->delta_y * 5;
	draw_line(vars()->player->x, vars()->player->y, x1, y1, color);
}

void draw_player(t_img img,int size, int color, double x, double y)
{
	vars()->player->x = x;
	vars()->player->y = y;
	vars()->player->size = size;
	draw_square(img, size, color, 0, 0);
	draw_orientation(size, gen_trgb(255, 255, 0, 0));
	draw_reverse(size, gen_trgb(255, 0, 0, 255));
	vars()->player->img = img;
}

void draw_map(void)
{
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
vars()->map_img.img_ptr, 0, 0);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr,\
vars()->mini_map.img_ptr, 0, 0);
}

void	draw_rectagle(int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + width)
	{
		j = y;
		while (j < y + height)
		{
			mlx_pixel_put(vars()->win->mlx_ptr, \
vars()->win->win_ptr, i, j, color);
			j++;
		}
		i++;
	}
}


void create_squares(t_win window)
{
	vars()->wall = new_img(CUBESIZE, CUBESIZE, window);
	vars()->floor = new_img(CUBESIZE, CUBESIZE, window);
	draw_square(vars()->wall, CUBESIZE - 1, gen_trgb(0, 255, 255, 255), 0, 0);
	draw_square(vars()->floor, CUBESIZE - 1, gen_trgb(0, 0, 150, 200), 0, 0);
}

void create_map(t_win window)
{
	int	mini_cube_size;
	int	i;
	int	j;

	mini_cube_size = 16;
	vars()->map_img = new_img(vars()->map_width * CUBESIZE, \
vars()->map_height * CUBESIZE, (t_win)window);
	vars()->mini_map = new_img(vars()->map_width * mini_cube_size, \
vars()->map_height * mini_cube_size, (t_win)window);
	printf("vars()->map_width: %d, vars()->map_height: %d\n", \
vars()->map_width, vars()->map_height);

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 1)
			{
				draw_square(vars()->mini_map, mini_cube_size - 1, gen_trgb(0, 255, 255, 255), j * mini_cube_size, i * mini_cube_size);
				draw_square(vars()->map_img, CUBESIZE - 1, gen_trgb(0, 255, 255, 255), j * CUBESIZE, i * CUBESIZE);
			}
			else
			{
				draw_square(vars()->mini_map, mini_cube_size - 1, gen_trgb(0, 0, 150, 200), j * mini_cube_size, i * mini_cube_size);
				draw_square(vars()->map_img, CUBESIZE - 1, gen_trgb(0, 0, 150, 200), j * CUBESIZE, i * CUBESIZE);
			}
			printf("%d", vars()->map[i][j]);
			j++;
		}
		i++;
	}
}


void create_map2(t_win window)
{
	int	mini_cube_size;
	int	i;
	int	j;

	mini_cube_size = 16;
	vars()->map_img = \
new_img(vars()->map_width * CUBESIZE, \
	vars()->map_height * CUBESIZE, (t_win)window);
	vars()->mini_map = \
new_img(vars()->map_width * mini_cube_size, \
vars()->map_height * mini_cube_size, (t_win)window);
	printf("vars()->map_width: %d, vars()->map_height: %d\n", \
vars()->map_width, vars()->map_height);

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 1)
			{
				draw_square(vars()->mini_map, mini_cube_size - 1, \
gen_trgb(0, 255, 255, 255), i * mini_cube_size, j * mini_cube_size);
			}
			else
			{
				draw_square(vars()->mini_map, mini_cube_size - 1, \
gen_trgb(0, 0, 150, 200), i * mini_cube_size, j * mini_cube_size);
			}
			printf("%d", vars()->map[i][j]);
			j++;
		}
		i++;
	}
}

double degToRad(double degrees)
{
	return (degrees * (PI / 180.0));
}

int FixAng(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

double distance(int ax, int ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

double rad_to_deegree(double rad)
{
	return (rad * 180 / PI);
}

void	init_vars(void)
{
	vars()->rx = 0;
	vars()->ry = 0;
	vars()->xo = 0;
	vars()->yo = 0;
	vars()->dist = 0;
	vars()->ra = vars()->player->angle - DR * FOV / 2;
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
}


void horizontal_check(void)
{
	vars()->dof = 0;
	vars()->disth = 1000000;
	vars()->hx = vars()->player->x,
	vars()->hy = vars()->player->y;
	vars()->atan = -1 / tan(vars()->ra);
	// Looking UP
	if (vars()->ra > PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) - 0.0001;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = -64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
	// Looking DOWN
	if (vars()->ra < PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) + 64;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = 64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
	// Looking LEFT or RIGHT
	if (vars()->ra == 0 || vars()->ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
	while (vars()->dof < 8)
	{
		vars()->mx = (int)(vars()->rx) >> 6;
		vars()->my = (int)(vars()->ry) >> 6;
		vars()->mp = vars()->my * vars()->map_width + vars()->mx;
		if (vars()->mx < 0 || vars()->my < 0 || vars()->mx > \
vars()->map_width || vars()->my > vars()->map_height)
			vars()->mp = vars()->map_width * vars()->map_height;
		if (vars()->mp > 0 && vars()->mp < vars()->map_width * \
vars()->map_height && vars()->map[vars()->my][vars()->mx] == 1)
		{
			vars()->hx = vars()->rx;
			vars()->hy = vars()->ry;
			vars()->disth = distance(vars()->player->x, \
vars()->player->y, vars()->hx, vars()->hy);
			vars()->dof = 8;
		}
		else
		{
			vars()->rx += vars()->xo;
			vars()->ry += vars()->yo;
			vars()->dof += 1;
		}
	}
}

void vertical_check(void)
{
	vars()->dof = 0;
	vars()->distv = 1000000;
	vars()->vx = vars()->player->x;
	vars()->vy = vars()->player->y;
	vars()->ntan = -tan(vars()->ra);
	// Looking left
	if (vars()->ra > P2 && vars()->ra < P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) - 0.0001;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = -64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
	// Looking right
	if (vars()->ra < P2 || vars()->ra > P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) + 64;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = 64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
	// Looking up or down
	if (vars()->ra == 0 || vars()->ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
	while (vars()->dof < 8)
	{
		vars()->mx = (int)(vars()->rx) >> 6;
		vars()->my = (int)(vars()->ry) >> 6;
		vars()->mp = vars()->my * vars()->map_width + vars()->mx;
		if (vars()->mx < 0 || vars()->my < 0 || \
vars()->mx > vars()->map_width || vars()->my > vars()->map_height)
			vars()->mp = vars()->map_width * vars()->map_height;
		if (vars()->mp > 0 && vars()->mp < vars()->map_width * \
vars()->map_height && vars()->map[vars()->my][vars()->mx] == 1)
		{
			vars()->dof = 8;
			vars()->vx = vars()->rx;
			vars()->vy = vars()->ry;
			vars()->distv = distance(vars()->player->x, \
vars()->player->y, vars()->vx, vars()->vy);
		}
		else
		{
			vars()->rx += vars()->xo;
			vars()->ry += vars()->yo;
			vars()->dof += 1;
		}
	}
}

void	wall_color(void)
{
	vars()->color_wall = gen_trgb(255, (int)0, 0, 0);
	if (vars()->distv < vars()->disth)
	{
		vars()->rx = vars()->vx;
		vars()->ry = vars()->vy;
		vars()->dist = vars()->distv;
		vars()->color_wall = gen_trgb(0, (int)255, 0, 0);
	}
	if (vars()->distv > vars()->disth)
	{
		vars()->rx = vars()->hx;
		vars()->ry = vars()->hy;
		vars()->dist = vars()->disth;
		vars()->color_wall = gen_trgb(0, (int)100, 0, 0);
	}
}


void draw_3d_walls(void)
{
	int	y;

	vars()->ca = vars()->player->angle - vars()->ra;
	if (vars()->ca < 0)
		vars()->ca += 2 * PI;
	if (vars()->ca > 2 * PI)
		vars()->ca -= 2 * PI;
	vars()->dist = vars()->dist * cos(vars()->ca);
	vars()->line_h = (CUBESIZE * SCREEN2HEIGHT / vars()->dist);
	vars()->ty_step = 64.0 / vars()->line_h;
	vars()->ty_off = 0;
	if (vars()->line_h > SCREEN2HEIGHT)
	{
		vars()->ty_off = (vars()->line_h - SCREEN2HEIGHT) / 2;
		vars()->line_h = SCREEN2HEIGHT;
	}
	draw_line(vars()->player->x, vars()->player->y, \
vars()->rx, vars()->ry, gen_trgb(255, 0, 255, 0));
	vars()->ra += DR;
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
	vars()->ty = vars()->ty_off * vars()->ty_step;
	vars()->shade = 1;
	if (vars()->disth >= vars()->distv)
	{
		vars()->tx = (int)(vars()->ry) % 64;
		vars()->shade = 0.5;
	}
	else
		vars()->tx = (int)(vars()->rx) % 64;
	vars()->disth *= cos(vars()->ca);
	vars()->pix_size = SCREENWIDTH / RAYNBR;
	y = 0;
	while (y < vars()->line_h)
	{
		vars()->color_wall = get_pixel_img(vars()->teste, \
(int)(vars()->tx) + (int)(vars()->ty) * 64);
		draw_rectagle(vars()->r * vars()->pix_size, \
SCREEN2HEIGHT / 2 - vars()->line_h / 2 + y, vars()->pix_size, \
vars()->pix_size, vars()->color_wall * vars()->shade);
		vars()->ty += vars()->ty_step;
		y++;
	}
	(void)(vars()->color_wall);
}


void drawRays2D(t_win window)
{
	init_vars();
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->ceil_img.img_ptr, 0, 0);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->floor_img.img_ptr, 0, SCREENHEIGHT / 3);
	for(vars()->r=0;vars()->r<RAYNBR;vars()->r++)
	{
		horizontal_check();
		vertical_check();
		wall_color();
		draw_3d_walls();
	}
	(void)window;
}

int main(int argc, char **argv)
{
	t_win		window;
	t_player	player;

	(void)argc;
	if (!check_format(argv[1]))
	{
		printf("Error: extensão do arquivo não é .cub\n");
		return (1);
	}

	vars()->player = &player;
	window =	new_program(SCREENWIDTH, SCREENHEIGHT, "cub3d");
	vars()->win = &window;

	parser(argv[1]);


	create_squares(window);
	create_map(window);
	draw_map();
	img_teste(&vars()->teste, "pics/colorstone.xpm");
	vars()->player->img = new_img(\
	(int)PLAYERSIZE, (int)PLAYERSIZE, (t_win)window);
	draw_player(vars()->player->img, PLAYERSIZE, \
	gen_trgb(0, 255, 255, 0), vars()->player->startx * CUBESIZE, \
	vars()->player->starty * CUBESIZE);
	vars()->player->delta_x = 5;
	vars()->player->delta_y = 0;
	drawRays2D(window);
	mlx_hook(window.win_ptr, 2, 1L << 0, key_hook, vars());
	mlx_hook(window.win_ptr, 17, 1L << 0, exit_program, vars());
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	mlx_loop(window.mlx_ptr);
	return (0);
}
