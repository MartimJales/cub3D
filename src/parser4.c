/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:25 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 16:38:55 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	process_character(char *input_str, int index)
{
	char	current_char;

	current_char = input_str[index];
	if (!is_valid_character(current_char))
		exit(printf("Error: invalid character\n") != 0);
	if (current_char == 'N' || current_char == 'S' || \
		current_char == 'E' || current_char == 'W')
	{
		validate_aux(current_char, index);
		current_char = '0';
	}
	if (current_char == ' ')
		current_char = '2';
	vars()->map[vars()->map_height][index] = char_to_int(current_char);
	return (0);
}

void	fill_map_line(int index)
{
	while (index < MAXSIZE)
	{
		vars()->map[vars()->map_height][index] = 2;
		index++;
	}
}

int	validate_string(char *input_str)
{
	int	index;

	index = 0;
	vars()->player->angle = 0;
	while (input_str[index] != '\0')
	{
		if (process_character(input_str, index) != 0)
			return (1);
		index++;
	}
	fill_map_line(index);
	return (0);
}
