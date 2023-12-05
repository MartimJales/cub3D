/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:18:43 by mjales            #+#    #+#             */
/*   Updated: 2023/12/05 01:36:24 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/cub3D.h"

// void img_teste(void)
// {
// 	vars()->teste.img_ptr = mlx_xpm_file_to_image(vars()->win->mlx_ptr, "pics/colorstone.xpm", &vars()->teste.w, &vars()->teste.h);
// 	if (!vars()->teste.img_ptr) {
// 		// Handle the error if the image did not load
// 		printf("Error loading the image\n");
// 		return ;
// 	}
// 	vars()->teste.addr = mlx_get_data_addr(vars()->teste.img_ptr, &vars()->teste.bpp, &vars()->teste.line_len, &vars()->teste.endian);

// 	// for (int i = 0; i < vars()->teste.w; i++)
// 	// {
// 	// 	for (int j = 0; j < vars()->teste.h; j++)
// 	// 	{
// 	// 		int color = get_pixel_img(vars()->teste, i, j);
// 	// 		mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, i, j, color);
// 	// 	}
// 	// }
// }

void img_teste(t_img *img, char *path)
{
	printf("path: %s\n", path);
	img->img_ptr = mlx_xpm_file_to_image(vars()->win->mlx_ptr, path, &img->w, &img->h);
	if (!img->img_ptr) {
		// Handle the error if the image did not load
		printf("Error loading the image\n");
		return ;
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);

	// for (int i = 0; i < img->w; i++)
	// {
	// 	for (int j = 0; j < img->h; j++)
	// 	{
	// 		int color = get_pixel_img(img, i, j);
	// 		mlx_pixel_put(vars()->win->mlx_ptr, vars()->win->win_ptr, i, j, color);
	// 	}
	// }
}
