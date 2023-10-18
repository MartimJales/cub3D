/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:34:54 by mjales            #+#    #+#             */
/*   Updated: 2023/10/18 17:53:15 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

t_var	*vars(void)
{
	static t_var	va;

	return (&va);
}

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void paint_cub3D()
{


	// cub3D();
	// while(1)
	// {
		for(int x = 0; x < screenWidth; x++)
		{
			static int teste;
			teste++;
			// printf("Inside loop %d\n", teste++);
			vars()->cameraX = 2 * x / (double)screenWidth - 1;
			vars()->rayDirX = vars()->dirX + vars()->planeX * vars()->cameraX;
			vars()->rayDirY = vars()->dirY + vars()->planeY * vars()->cameraX;
			vars()->mapX = (int)vars()->posX;
			vars()->mapY = (int)vars()->posY;

			vars()->deltaDistX = (vars()->rayDirX == 0) ? 1e30 : abs((int)(1 / vars()->rayDirX));
			vars()->deltaDistY = (vars()->rayDirY == 0) ? 1e30 : abs((int)(1 / vars()->rayDirY));

			vars()->hit = 0;
			if(vars()->rayDirX < 0)
			{
				vars()->stepX = -1;
				vars()->sideDistX = (vars()->posX - vars()->mapX) * vars()->deltaDistX;
			}
			else
			{
				vars()->stepX = 1;
				vars()->sideDistX = (vars()->mapX + 1.0 - vars()->posX) * vars()->deltaDistX;
			}
			if(vars()->rayDirY < 0)
			{
				vars()->stepY = -1;
				vars()->sideDistY = (vars()->posY - vars()->mapY) * vars()->deltaDistY;
			}
			else
			{
				vars()->stepY = 1;
				vars()->sideDistY = (vars()->mapY + 1.0 - vars()->posY) * vars()->deltaDistY;
			}
			while(vars()->hit == 0)
			{
				if(vars()->sideDistX < vars()->sideDistY)
				{
				vars()->sideDistX += vars()->deltaDistX;
				vars()->mapX += vars()->stepX;
				vars()->side = 0;
				}
				else
				{
				vars()->sideDistY += vars()->deltaDistY;
				vars()->mapY += vars()->stepY;
				vars()->side = 1;
				}
				if(worldMap[vars()->mapX][vars()->mapY] > 0) vars()->hit = 1;
			}
			if(vars()->side == 0) vars()->perpWallDist = (vars()->sideDistX - vars()->deltaDistX);
			else          vars()->perpWallDist = (vars()->sideDistY - vars()->deltaDistY);

			int lineHeight = (int)(screenHeight / vars()->perpWallDist);

			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

			int color;
			switch(worldMap[vars()->mapX][vars()->mapY])
			{
				//red
				case 1:  color = gen_trgb(255,255,0,0);    break;
				//green
				case 2:  color = gen_trgb(255,0,255,0);    break;
				//blue
				case 3:  color = gen_trgb(255,0,0,255);    break;
				// white
				case 4:  color = gen_trgb(255,255,255,255); break;
				//yellow
				default: color = gen_trgb(255,255,255,0);  break;
			}

			//give x and y sides different brightness
			if(vars()->side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color);
		}
		vars()->moveSpeed = 2;	//frameTime * 5.0; //the constant value is in squares/second
		vars()->rotSpeed = 	1;	//frameTime * 3.0; //the constant value is in radians/second
	// }
}


int	cub3D(void)
{
	t_win	tutorial;
	t_img	img;

	tutorial = new_program(screenWidth, screenHeight, "cub3D");
	if (!tutorial.win_ptr)
		return (2);
	img = new_img(screenWidth, screenHeight, tutorial);
	vars()->win = &tutorial;
	vars()->img_ptr = &img;
	paint_cub3D(/*img, 0, 0*/);
	mlx_put_image_to_window(img.win.mlx_ptr, img.win.win_ptr, \
	img.img_ptr, 0, 0);
	mlx_hook(tutorial.win_ptr, 2, 1L << 0, key_hook, vars());
	mlx_hook(tutorial.win_ptr, 17, 1L << 0, exit_program, vars());
	// mlx_mouse_hook(tutorial.win_ptr, mouse_hook, vars());
	mlx_loop(tutorial.mlx_ptr);
	return (0);
}

void verLine(int x, int y1, int y2, int color)
{
	static int teste;
	int y;
	for (y = y1; y <= y2; y++)
	{
		teste++;
		// printf("Inside verLine %d\n", teste);
		mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, x, y, color);
	}
}

int	put_image(void)
{
	// mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	// image_mandelbrot(*vars()->img_ptr, 0,0);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
	vars()->img_ptr->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	vars()->posX = 1;
	vars()->posY = 1;
	vars()->dirX = -1;
	vars()->dirY = 0;
	vars()->planeX = 0;
	vars()->planeY = 0.66;

	cub3D();
}
