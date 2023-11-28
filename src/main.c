/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/11/28 12:57:17 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"


t_var	*vars(void)
{
	static t_var	va;

	return (&va);
}

void draw_square(t_img img,int size, int color, int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel_img(img, i + x, j + y, color);
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
	draw_square(img, size, color, 0, 0);
	draw_orientation(size, gen_trgb(255, 255, 0, 0));
	draw_reverse(size, gen_trgb(255, 0, 0, 255));
	vars()->player->img = img;
}

void draw_map()
{
	for (int i = 0; i < miniMapH; i++)
	{
		for (int j = 0; j < miniMapW; j++)
		{
			if (vars()->map[i + (int)(vars()->player->x/cubeSize) - 4][j + (int)(vars()->player->y/cubeSize) - 4] == 1)
				mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->wall.img_ptr, j * (cubeSize) , i * (cubeSize));
			else
				mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->floor.img_ptr, j * (cubeSize), i * (cubeSize));
		}
	}

}

void  draw_rectagle(int x, int y, int width, int height, int color)
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
	draw_square(vars()->wall, cubeSize-1, gen_trgb(0, 255, 255, 255), 0, 0);
	draw_square(vars()->floor, cubeSize-1, gen_trgb(0, 0, 150, 200), 0, 0);
}

void create_map(t_win window)
{
	int mapa[miniMapW][miniMapH] = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	for (int i = 0; i < miniMapH; i++){
		for (int j = 0; j < miniMapW; j++)
			vars()->map[i][j] = mapa[i][j];
	}

	vars()->map_img = new_img(vars()->mapWidth * cubeSize, vars()->mapHeight * cubeSize, window);
	// Create the main map
	printf("mapWidth: %d, mapHeight: %d\n", vars()->mapWidth, vars()->mapHeight);
	for (int i = 0; i < vars()->mapHeight; i++)
	{
		for (int j = 0; j < vars()->mapWidth; j++)
		{
			if (vars()->map[i][j] == 1)
				draw_square(vars()->map_img, cubeSize-1, gen_trgb(0, 255, 255, 255), i * cubeSize, j * cubeSize);
			else
				draw_square(vars()->map_img, cubeSize-1, gen_trgb(0, 0, 150, 200), i * cubeSize, j * cubeSize);
			printf("%d", vars()->map[i][j]);
		}
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
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	for(r=0;r<60;r++)
	{
		//---horizontal---
		dof=0;
		double distH = 1000000, hx = vars()->player->x, hy = vars()->player->y;
		double aTan=-1/tan(ra);
		// Looking UP
		if (ra>PI)
		{
			ry = (((int)vars()->player->y>>6)<<6)- 0.0001;
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
			mp = my * miniMapW + mx;
			// printf("mx: %d, my: %d\n", mx, my);
			if (mx < 0 || my < 0 || mx > miniMapW || my > miniMapH)
				mp = miniMapW * miniMapH;
			if (mp > 0 && mp < miniMapW * miniMapH && vars()->map[my][mx] == 1)
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
			mp = my * miniMapW + mx;
			// printf("mx: %d, my: %d\n", mx, my);
			if (mx < 0 || my < 0 || mx > miniMapW || my > miniMapH)
				mp = miniMapW * miniMapH;
			if (mp > 0 && mp < miniMapW * miniMapH && vars()->map[my][mx] == 1)
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
		// printf("px: %f, py: %f\n", vars()->player->x, vars()->player->y);
		// printf("distH: %f, distV: %f\n", distH, distV);
		// printf("player x: %d, player y: %d\n", vars()->player->x, vars()->player->y);
		//draw 3d walls
		float ca = vars()->player->angle - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca);
		float lineH = (cubeSize * screen2height / disT);
		float ty_step = 64.0 / lineH;
		float ty_off = 0;
		if (lineH > screen2height)
		{
			ty_off = (lineH - screen2height)/2;
			lineH = screen2height;
		}
		draw_line(vars()->player->x, vars()->player->y, rx, ry, gen_trgb(255, 0, 255, 0));
		ra+=DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra >= 2 * PI)
			ra -= 2 * PI;

		//lineH = cubeSize * screen2height / distH;

		float tx;
		float ty = ty_off*ty_step;
		float shade = 1;
		//printf("distV: %f, distH: %f\n", distV, distH);
		if (distH>= distV)
		{
			tx = (int)(ry) % 64;
			shade = 0.5;
		}
		else
			tx = (int)(rx) % 64;
		distH *= cos(ca);
		// Draw Ceil
		draw_rectagle(r * 8 + 530, 0, 8, screen2height / 2 - lineH / 2, vars()->ccolor);
		int y;
		for (y = 0; y < lineH; y++){
			// printf("ty step: %f\n", ty_step);
			// printf("pixel location = %d\n", (int)ty *64);
			color_wall = get_pixel_img(vars()->teste, (int)tx +  (int)(ty) * 64);
			// color_wall = gen_trgb(0, 0, (r*3)%255, 0);
			draw_rectagle(r * 8 + 530, screen2height / 2 - lineH / 2 + y, 8, 8, color_wall * shade);
			// mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, r * 8 + 530, screen2height / 2 - lineH / 2 + y, color_wall);
			ty += ty_step;
			//printf("ty: %d\n", (int)ty);
		}
		// Draw Floor
		draw_rectagle(r * 8 + 530, screen2height / 2 - lineH / 2 + y, 8, screen2height - (screen2height / 2 - lineH / 2 + y), vars()->fcolor);
		//printf("lineH: %f\n", lineH);
		//printf("rx: %f\n", rx);
		(void)color_wall;

	(void)window;
	//printf("rx:%f, ry:%f, r:%d\n", rx, ry, r);
}

}

int main(int argc, char **argv)
{

	if (argc != 2) {
        printf("Error: bad arguments\n");
        return 1;
    }
    if (!check_format(argv[1])) {
        printf("Error: extensão do arquivo não é .cub\n");
		return 1;
    }

    t_win window;
	t_player player;

	vars()->player = &player;
    window = new_program(screenWidth, screenHeight, "cub3d");
	vars()->win = &window;

	parser(argv[1]);

	// Show SO NO WE EA in window


	vars()->player->img = new_img(playerSize, playerSize, window);
	// draw_player(vars()->player->img, playerSize, gen_trgb(0, 255, 255, 0), miniMapW/2*cubeSize, miniMapH/2*cubeSize);
	vars()->player->deltaX = 5;
	vars()->player->deltaY = 0;
	create_squares(window);
	create_map(window);
	draw_map();
	// Draw ceil_img
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->ceil_img.img_ptr, screenWidth/2, 0);
	// Draw floor_img
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->floor_img.img_ptr, screenWidth/2, screenHeight/3);

	img_teste(&vars()->teste, "pics/colorstone.xpm");
	drawRays2D(window);
	mlx_hook(window.win_ptr, 2, 1L<<0, key_hook, vars());
	mlx_hook(window.win_ptr, 17, 1L << 0, exit_program, vars());
    mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	// mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->NO.img_ptr, 0, 0);
	// mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->SO.img_ptr, 0, 64);
	// mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->WE.img_ptr, 0, 128);
	// mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->EA.img_ptr, 0, 192);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->map_img.img_ptr, 50, 50);
	mlx_loop(window.mlx_ptr);
    return (0);
}
