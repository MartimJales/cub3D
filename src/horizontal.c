/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:25 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 16:14:42 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	horizontal_vars(double ra)
{
	vars()->dof = 0;
	vars()->disth = 1000000;
	vars()->hx = vars()->player->x,
	vars()->hy = vars()->player->y;
	vars()->atan = -1 / tan(ra);
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
