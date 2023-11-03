/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/11/02 12:01:27 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

t_var	*vars(void)
{
	static t_var	va;

	return (&va);
}

void draw_square(t_img img,int size, int color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel_img(img, i, j, color);
		}
	}
}

void draw_line(int x, int y, int x1, int y1, int color)
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
            break;
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

void draw_orientation(int size, int color)
{
	(void)size;
	int x1 = vars()->player->x + vars()->player->deltaX * 5;
	int y1 = vars()->player->y + vars()->player->deltaY * 5;
	draw_line(vars()->player->x, vars()->player->y, x1, y1, color);
}

void draw_reverse(int size, int color)
{
	(void)size;
	int x1 = vars()->player->x - vars()->player->deltaX * 5;
	int y1 = vars()->player->y - vars()->player->deltaY * 5;
	draw_line(vars()->player->x, vars()->player->y, x1, y1, color);
}

void draw_player(t_img img,int size, int color, double x, double y)
{
	vars()->player->x = x;
	vars()->player->y = y;
	vars()->player->size = size;
	draw_square(img, size, color);
	draw_orientation(size, gen_trgb(255, 255, 0, 0));
	draw_reverse(size, gen_trgb(255, 0, 0, 255));
	vars()->player->img = img;
}

void draw_map()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (vars()->map[i][j] == 1)
				mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->wall.img_ptr, j * (cubeSize) , i * (cubeSize));
			else
				mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->floor.img_ptr, j * (cubeSize), i * (cubeSize));
		}
	}

}

void draw_rectagle(int x, int y, int width, int height, int color)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
			mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, i, j, color);
	}
}

void create_squares(t_win window)
{
	vars()->wall = new_img(cubeSize, cubeSize, window);
	vars()->floor = new_img(cubeSize, cubeSize, window);
	draw_square(vars()->wall, cubeSize-1, gen_trgb(0, 255, 255, 255));
	draw_square(vars()->floor, cubeSize-1, gen_trgb(0, 0, 150, 200));
}

void create_map()
{
	int mapa[mapWidth][mapHeight] = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	for (int i = 0; i < mapHeight; i++){
		for (int j = 0; j < mapWidth; j++)
			vars()->map[i][j] = mapa[i][j];
	}
}

double degToRad(double degrees) {
    return degrees * (PI / 180.0);
}

int FixAng(int a)
{
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return a;
}

double distance(int ax, int ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

double rad_to_deegree(double rad)
{
	return (rad * 180 / PI);
}

void drawRays2D(t_win window)
{
	int r,mx,my,mp,dof;
	double rx = 0,ry = 0,ra,xo = 0,yo = 0, disT = 0;
	ra = vars()->player->angle - DR*FOV/2;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	printf("angle: %f\n", rad_to_deegree(ra));
	for(r=0;r<60;r++)
	{
		//---horizontal---
		dof=0;
		double distH = 1000000, hx = vars()->player->x, hy = vars()->player->y;
		double epsilon = 1e-6; // Uma pequena margem para evitar erros de precisão
		if (fabs(tan(ra)) > epsilon) {
			double aTan=-1/tan(ra);
		// Looking UP
		if (ra>PI)
		{
			ry = (((int)vars()->player->y>>6)<<6) - 0.0001;
			rx = (vars()->player->y-ry)*aTan + vars()->player->x;
			yo = -64;
			xo = -yo*aTan;
		}
		// Looking DOWN
		if (ra < PI)
		{
			ry = (((int)vars()->player->y>>6)<<6) + 64;
			rx = (vars()->player->y - ry) * aTan + vars()->player->x;
			yo = 64;
			xo = -yo * aTan;
		}
		// Looking LEFT or RIGHT
		if (ra == 0 || ra == PI)
		{
			rx = vars()->player->x;
			ry = vars()->player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapWidth + mx;
			// printf("mx: %d, my: %d\n", mx, my);
			if (mx < 0 || my < 0 || mx > mapWidth || my > mapHeight)
				mp = mapWidth * mapHeight;
			if (mp > 0 && mp < mapWidth * mapHeight && vars()->map[my][mx] == 1)
			{
				hx = rx;
				hy = ry;
				distH = distance(vars()->player->x, vars()->player->y, hx, hy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		//vertical check
		dof=0;
		double distV = 1000000, vx = vars()->player->x, vy = vars()->player->y;
		double nTan=-tan(ra);
		// Looking left
		if (ra>P2 && ra<P3)
		{
			rx = (((int)vars()->player->x>>6)<<6) - 0.0001;
			ry = (vars()->player->x - rx) * nTan + vars()->player->y;
			xo = -64;
			yo = -xo * nTan;
		}
		// Looking right
		if (ra < P2 || ra > P3)
		{
			rx = (((int)vars()->player->x>>6)<<6) + 64;
			ry = (vars()->player->x - rx) * nTan + vars()->player->y;
			xo = 64;
			yo = -xo * nTan;
		}
		// Looking up or down
		if (ra == 0 || ra == PI)
		{
			rx = vars()->player->x;
			ry = vars()->player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapWidth + mx;
			// printf("mx: %d, my: %d\n", mx, my);
			if (mx < 0 || my < 0 || mx > mapWidth || my > mapHeight)
				mp = mapWidth * mapHeight;
			if (mp > 0 && mp < mapWidth * mapHeight && vars()->map[my][mx] == 1)
			{
				dof = 8;
				vx = rx;
				vy = ry;
				distV = distance(vars()->player->x, vars()->player->y, vx, vy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		int color_wall = gen_trgb(255, 0, 0, 0);
		if (distV < distH)
		{
			rx = vx;
			ry = vy;
			disT=distV;
			color_wall = gen_trgb(0, 255, 0, 0);
		}
		if (distV > distH)
		{
			rx = hx;
			ry = hy;
			disT=distH;
			color_wall = gen_trgb(0, 100, 0, 0);
		}
		// printf("rx: %f, ry: %f\n", rx, ry);
		// printf("player x: %d, player y: %d\n", vars()->player->x, vars()->player->y);
		//draw 3d walls
		float ca = vars()->player->angle - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca);
		float lineH = (cubeSize * screen2height / disT);
		if (lineH > screen2height)
			lineH = screen2height;

		draw_line(vars()->player->x, vars()->player->y, rx, ry, gen_trgb(255, 0, 255, 0));
		ra+=DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		// t_img teste = new_img(80, lineH, window);
		// teste.img_ptr =	mlx_xpm_file_to_image(vars()->win->mlx_ptr, "pics/eagle.xpm", &teste.w, &teste.h);
		// mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, teste.img_ptr, r * 8 + 530, screen2height / 2 - lineH / 2);
		draw_rectagle(r * 8 + 530, screen2height / 2 - lineH / 2, 8, lineH, color_wall);
		(void)color_wall;
	}
	(void)window;
}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
    t_win window;
	t_player player;

	vars()->player = &player;
    window = new_program(screenWidth, screenHeight, "cub3d");
	vars()->win = &window;
	create_squares(window);
	create_map();
	draw_map();
	vars()->player->img = new_img(playerSize, playerSize, window);
	draw_player(vars()->player->img, playerSize, gen_trgb(0, 255, 255, 0), mapWidth/2*cubeSize, mapHeight/2*cubeSize);
	vars()->player->deltaX = 5;
	vars()->player->deltaY = 0;
	drawRays2D(window);
	mlx_hook(window.win_ptr, 2, 1L<<0, key_hook, vars());
	mlx_hook(window.win_ptr, 17, 1L << 0, exit_program, vars());
    mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	mlx_loop(window.mlx_ptr);
    return (0);
}
