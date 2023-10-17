/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:29:02 by mjales            #+#    #+#             */
/*   Updated: 2023/10/17 11:44:36 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	map_color(int intensity, int max)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)intensity / max;
	r = (int)(255 * (1 - t) * t * t * t * 6);
	g = (int)(255 * (1 - t) * (1 - t) * t * t * 6);
	b = (int)(255 * (1 - t) * (1 - t) * (1 - t) * t * 6);
	return (gen_trgb(intensity, r, b, g));
}
