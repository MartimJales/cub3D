/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:29:02 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 18:58:03 by dcordovi         ###   ########.fr       */
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

void	print_map(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 1)
				printf("%d", 1);
			else
				printf("%d", vars()->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
