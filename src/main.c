/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/12/28 17:07:25 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

t_var	*vars(void)
{
	static t_var	va;

	return (&va);
}

void	draw_square(t_img img, int size, t_position pos)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(img, i + pos.x, j + pos.y, pos.color);
			j++;
		}
		i++;
	}
}

//aux do draw_line
void	line_vars(t_position pos, int x1, int y1)
{
	(void)pos.color;
	vars()->dx = abs(x1 - pos.x);
	if (pos.x < x1)
		vars()->sx = 1;
	else
		vars()->sx = -1;
	vars()->dy = -abs(y1 - pos.y);
	if (pos.y < y1)
		vars()->sy = 1;
	else
		vars()->sy = -1;
	vars()->err = vars()->dx + vars()->dy;
}

void	draw_line(t_position pos, int x1, int y1)
{
	line_vars(pos, x1, y1);
	while (1)
	{
		mlx_pixel_put(vars()->win->mlx_ptr, \
vars()->win->win_ptr, pos.x, pos.y, pos.color);
		if (pos.x == x1 && pos.y == y1)
			break ;
		vars()->e2 = 2 * vars()->err;
		if (vars()->e2 >= vars()->dy)
		{
			vars()->err += vars()->dy;
			pos.x += vars()->sx;
		}
		if (vars()->e2 <= vars()->dx)
		{
			vars()->err += vars()->dx;
			pos.y += vars()->sy;
		}
	}
}

void	draw_orientation(int size, int color)
{
	int			x1;
	int			y1;
	t_position	pos;

	(void)size;
	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = color;
	x1 = vars()->player->x + vars()->player->delta_x * 5;
	y1 = vars()->player->y + vars()->player->delta_y * 5;
	draw_line(pos, x1, y1);
}

void	draw_reverse(int size, int color)
{
	int			x1;
	int			y1;
	t_position	pos;

	(void)size;
	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = color;
	x1 = vars()->player->x - vars()->player->delta_x * 5;
	y1 = vars()->player->y - vars()->player->delta_y * 5;
	draw_line(pos, x1, y1);
}

void	draw_player(t_img img, int size, t_position position)
{
	t_position	pos;

	vars()->player->x = position.x;
	vars()->player->y = position.y;
	vars()->player->size = size;
	pos.x = position.x;
	pos.y = position.y;
	pos.color = position.color;
	draw_square(img, size, pos);
	draw_orientation(size, gen_trgb(255, 255, 0, 0));
	draw_reverse(size, gen_trgb(255, 0, 0, 255));
	vars()->player->img = img;
}

void	draw_map(void)
{
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
vars()->map_img.img_ptr, 0, 0);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
vars()->mini_map.img_ptr, 0, 0);
}

void	draw_rectagle(int width, int height, t_position pos)
{
	int	i;
	int	j;

	i = pos.x;
	while (i < pos.x + width)
	{
		j = pos.y;
		while (j < pos.y + height)
		{
			mlx_pixel_put(vars()->win->mlx_ptr, \
vars()->win->win_ptr, i, j, pos.color);
			j++;
		}
		i++;
	}
}

void	create_squares(t_win window)
{
	t_position	pos;
	t_img		tmp;

	pos.x = 0;
	pos.y = 0;
	pos.color = gen_trgb(0, 255, 255, 255);
	tmp = new_img(CUBESIZE, CUBESIZE, window);
	vars()->wall = tmp;
	tmp = new_img(CUBESIZE, CUBESIZE, window);
	vars()->floor = tmp;
	draw_square(vars()->wall, CUBESIZE - 1, pos);
	pos.color = gen_trgb(0, 0, 150, 200);
	draw_square(vars()->floor, CUBESIZE - 1, pos);
}

void	draw_wall(t_position pos, int i, int j, int mini_cube_size)
{
	pos.x = j * mini_cube_size;
	pos.y = i * mini_cube_size;
	pos.color = gen_trgb(0, 255, 255, 255);
	draw_square(vars()->mini_map, mini_cube_size - 1, pos);
	pos.x = j * CUBESIZE;
	pos.y = i * CUBESIZE;
	draw_square(vars()->map_img, CUBESIZE - 1, pos);
}

//aux create_map
void	draw_empty(t_position pos, int i, int j, int mini_cube_size)
{
	pos.x = j * mini_cube_size;
	pos.y = i * mini_cube_size;
	pos.color = gen_trgb(0, 0, 150, 200);
	draw_square(vars()->mini_map, mini_cube_size - 1, pos);
	pos.x = j * CUBESIZE;
	pos.y = i * CUBESIZE;
	draw_square(vars()->map_img, CUBESIZE - 1, pos);
}

//aux do create_map
void	map_loop(t_position pos, int mini_cube_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 1)
				draw_wall(pos, i, j, mini_cube_size);
			else
				draw_empty(pos, i, j, mini_cube_size);
			j++;
		}
		i++;
	}
}

void	create_map(t_win window)
{
	int			mini_cube_size;
	t_position	pos;
	t_img		tmp;

	mini_cube_size = 16;
	tmp = new_img(vars()->map_width * CUBESIZE, \
vars()->map_height * CUBESIZE, (t_win)window);
	vars()->map_img = tmp;
	tmp = new_img(vars()->map_width * mini_cube_size, \
vars()->map_height * mini_cube_size, (t_win)window);
	vars()->mini_map = tmp;
	map_loop(pos, mini_cube_size);
}

double	distance(int ax, int ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
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

void	horizontal_vars(double ra)
{
	vars()->dof = 0;
	vars()->disth = 1000000;
	vars()->hx = vars()->player->x,
	vars()->hy = vars()->player->y;
	vars()->atan = -1 / tan(ra);
}

void	look_up_or_down(double ra)
{
	if (ra > PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) - 0.0001;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = -64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
	if (ra < PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) + 64;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = 64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
}

void	look_left_or_right(double ra)
{
	if (ra == 0 || ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
}

void	horizontal_loop(void)
{
	double	disth;

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
		disth = distance(vars()->player->x, \
vars()->player->y, vars()->hx, vars()->hy);
		vars()->disth = disth;
		vars()->dof = 8;
	}
	else
	{
		vars()->rx += vars()->xo;
		vars()->ry += vars()->yo;
		vars()->dof += 1;
	}
}

void	horizontal_check(double ra)
{
	horizontal_vars(ra);
	look_up_or_down(ra);
	look_left_or_right(ra);
	while (vars()->dof < 8)
		horizontal_loop();
}

void	vertical_vars(double ra)
{
	vars()->dof = 0;
	vars()->distv = 1000000;
	vars()->vx = vars()->player->x;
	vars()->vy = vars()->player->y;
	vars()->ntan = -tan(ra);
}

void	left_or_right(double ra)
{
	if (ra > P2 && ra < P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) - 0.0001;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = -64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
	if (ra < P2 || ra > P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) + 64;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = 64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
}

//aux do vertical_check
void	up_or_down(double ra)
{
	if (ra == 0 || ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
}

//aux do vertical_check
void	vertical_loop(void)
{
	double	distv;

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
		distv = distance(vars()->player->x, \
vars()->player->y, vars()->vx, vars()->vy);
		vars()->distv = distv;
	}
	else
	{
		vars()->rx += vars()->xo;
		vars()->ry += vars()->yo;
		vars()->dof += 1;
	}
}

void	vertical_check(double ra)
{
	vertical_vars(ra);
	left_or_right(ra);
	up_or_down(ra);
	while (vars()->dof < 8)
		vertical_loop();
}

void	wall_color(void)
{
	int	color;

	color = gen_trgb(255, (int)0, 0, 0);
	if (vars()->distv < vars()->disth)
	{
		vars()->rx = vars()->vx;
		vars()->ry = vars()->vy;
		vars()->dist = vars()->distv;
		color = gen_trgb(0, (int)255, 0, 0);
	}
	if (vars()->distv > vars()->disth)
	{
		vars()->rx = vars()->hx;
		vars()->ry = vars()->hy;
		vars()->dist = vars()->disth;
		color = gen_trgb(0, (int)100, 0, 0);
	}
	vars()->color_wall = color;
}

//aux do draw_3d_walls
void	draw_3d_aux1(t_position pos)
{
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
	draw_line(pos, vars()->rx, vars()->ry);
	vars()->ra += DR;
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
	vars()->ty = vars()->ty_off * vars()->ty_step;
	vars()->shade = 1;
}

void	draw_3d_aux2(void)
{
	if (vars()->disth >= vars()->distv)
	{
		vars()->tx = (int)(vars()->ry) % 64;
		vars()->shade = 0.5;
	}
	else
		vars()->tx = (int)(vars()->rx) % 64;
	vars()->disth *= cos(vars()->ca);
	vars()->pix_size = SCREENWIDTH / RAYNBR;
}

void	draw_3d_walls(void)
{
	int			y;
	t_position	pos;
	int			color;

	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = gen_trgb(255, 0, 255, 0);
	draw_3d_aux1(pos);
	draw_3d_aux2();
	y = 0;
	while (y < vars()->line_h)
	{
		color = \
get_pixel_img(vars()->teste, (int)(vars()->tx) + (int)(vars()->ty) * 64);
		pos.x = vars()->r * vars()->pix_size;
		pos.y = SCREEN2HEIGHT / 2 - vars()->line_h / 2 + y;
		pos.color = color * vars()->shade;
		draw_rectagle(vars()->pix_size, vars()->pix_size, pos);
		vars()->ty += vars()->ty_step;
		y++;
	}
}

void	draw_rays_2d(t_win window)
{
	double	ra;

	init_vars();
	mlx_put_image_to_window(vars()->win->mlx_ptr, \
vars()->win->win_ptr, vars()->ceil_img.img_ptr, 0, 0);
	mlx_put_image_to_window(vars()->win->mlx_ptr, \
vars()->win->win_ptr, vars()->floor_img.img_ptr, 0, SCREENHEIGHT / 3);
	vars()->r = 0;
	ra = vars()->ra;
	while (vars()->r < RAYNBR)
	{
		ra = vars()->ra;
		horizontal_check(ra);
		vertical_check(ra);
		wall_color();
		draw_3d_walls();
		vars()->r++;
	}
	(void)window;
}

t_img	initialize_player_image(void)
{
	t_img	tmp;

	img_teste(&vars()->teste, "pics/colorstone.xpm");
	tmp = new_img(PLAYERSIZE, PLAYERSIZE, *vars()->win);
	return (tmp);
}

t_position	initialize_player_position(void)
{
	t_position	pos;

	pos.x = vars()->player->startx * CUBESIZE;
	pos.y = vars()->player->starty * CUBESIZE;
	pos.color = gen_trgb(0, 255, 255, 0);
	return (pos);
}

void	setup_player(void)
{
	vars()->player->delta_x = 5;
	vars()->player->delta_y = 0;
}

void	draw_player_and_rays(t_win window, t_img player_img)
{
	draw_player(player_img, PLAYERSIZE, initialize_player_position());
	draw_rays_2d(window);
}

void	handle_hooks_and_put_image(t_win window, t_img player_img)
{
	mlx_hook(window.win_ptr, 2, 1L << 0, key_hook, vars());
	mlx_hook(window.win_ptr, 17, 1L << 0, exit_program, vars());
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
player_img.img_ptr, vars()->player->x, vars()->player->y);
	mlx_loop(window.mlx_ptr);
}

void	initialize_game(char *file_path)
{
	t_win		window;
	t_player	player;
	t_img		player_img;

	vars()->player = &player;
	window = new_program(SCREENWIDTH, SCREENHEIGHT, "cub3d");
	vars()->win = &window;
	if (!check_format(file_path))
	{
		printf("Error: extensão do arquivo não é .cub\n");
		exit(1);
	}
	parser(file_path);
	create_squares(window);
	create_map(window);
	player_img = initialize_player_image();
	setup_player();
	draw_player_and_rays(window, player_img);
	handle_hooks_and_put_image(window, player_img);
}

int	main(int argc, char **argv)
{
	(void)argc;
	initialize_game(argv[1]);
	return (0);
}
