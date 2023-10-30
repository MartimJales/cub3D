/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/10/30 16:58:17 by mjales           ###   ########.fr       */
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

void draw_line(t_img img, int x, int y, int x1, int y1, int color)
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
        put_pixel_img(img, x, y, gen_trgb(0, 255, 0, 0));
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

void draw_orientation(t_img img,int size, int color)
{
	int x = size/2;
	int y = size/2;
	int x1 = x + cos(vars()->player->angle) * size/2;
	int y1 = y + sin(vars()->player->angle) * size/2;
	draw_line(img, x, y, x1, y1, color);
}

void draw_player(t_img img,int size, int color, int x, int y)
{
	vars()->player->x = x;
	vars()->player->y = y;
	vars()->player->size = size;
	draw_square(img, size, color);
	draw_orientation(img, size, color);
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
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	for (int i = 0; i < mapHeight; i++){
		for (int j = 0; j < mapWidth; j++)
			vars()->map[i][j] = mapa[i][j];
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
	mlx_hook(window.win_ptr, 2, 1L<<0, key_hook, vars());
	mlx_hook(window.win_ptr, 17, 1L << 0, exit_program, vars());
    mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	mlx_loop(window.mlx_ptr);
    return (0);
}
