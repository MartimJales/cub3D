/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:46 by mjales            #+#    #+#             */
/*   Updated: 2024/01/17 15:37:36 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	create_images(void)
{
	t_img	tmp;

	tmp = new_img(SCREENWIDTH, (int)SCREENHEIGHT / 3, *vars()->win);
	vars()->ceil_img = tmp;
	tmp = new_img(SCREENWIDTH, (int)2 * SCREENHEIGHT / 3, *vars()->win);
	vars()->floor_img = tmp;
	fill_image(vars()->ceil_img, vars()->ccolor);
	fill_image(vars()->floor_img, vars()->fcolor);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

int	get_pixel_img(t_img img, int pixel)
{
	char	*src;
	int		color;

	if (pixel >= 0 && pixel < img.w * img.h)
	{
		src = img.addr + (pixel * (img.bpp / 8));
		color = *(unsigned int *)src;
		return (color);
	}
	return (-1);
}

t_img	new_img(int w, int h, t_win window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_new_image(window.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp), \
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

t_win	new_program(int w, int h, char *str)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}
