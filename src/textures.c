/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:18:43 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 18:09:58 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	img_teste(t_img *img, char *path, char *line)
{
	if (img->img_ptr)
		mlx_destroy_image(vars()->win->mlx_ptr, img->img_ptr);
	img->img_ptr = mlx_xpm_file_to_image(vars()->win->mlx_ptr, \
path, &img->w, &img->h);
	if (!img->img_ptr)
	{
		free(line);
		exit_program(printf("Error loading the image\n"));
		return ;
	}
	img->addr = mlx_get_data_addr(img->img_ptr, \
&img->bpp, &img->line_len, &img->endian);
}
