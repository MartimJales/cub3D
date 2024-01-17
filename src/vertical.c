/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:38 by mjales            #+#    #+#             */
/*   Updated: 2024/01/10 15:14:59 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	vertical_vars(double ra)
{
	vars()->dof = 0;
	vars()->distv = 1000000;
	vars()->vx = vars()->player->x;
	vars()->vy = vars()->player->y;
	vars()->ntan = -tan(ra);
}

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
