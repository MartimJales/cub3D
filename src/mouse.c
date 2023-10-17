/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:45:41 by mjales            #+#    #+#             */
/*   Updated: 2023/10/17 11:44:36 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

double	convert_range(double old_value, int max_value)
{
	return (((old_value + old_value) / max_value) - 1.0f);
}

