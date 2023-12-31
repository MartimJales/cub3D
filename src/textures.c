/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:18:43 by mjales            #+#    #+#             */
/*   Updated: 2023/12/19 18:26:58 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	img_teste(t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(vars()->win->mlx_ptr, \
path, &img->w, &img->h);
	if (!img->img_ptr)
	{
		printf("Error loading the image\n");
		return ;
	}
	img->addr = mlx_get_data_addr(img->img_ptr, \
&img->bpp, &img->line_len, &img->endian);
}
