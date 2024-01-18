/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:26:58 by mjales            #+#    #+#             */
/*   Updated: 2024/01/17 15:27:00 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	char_to_int(char chr)
{
	return (chr - '0');
}

int	check_string(char *input_str)
{
	while (*input_str != '\0')
	{
		if (*input_str == '0' || *input_str == '1')
		{
			return (0);
		}
		input_str++;
	}
	return (1);
}

int	is_valid_character(char current_char)
{
	if (char_to_int(current_char) == 0 || char_to_int(current_char) == 1 || \
		current_char == 'N' || current_char == 'S' || \
		current_char == 'E' || current_char == 'W' || \
		current_char == ' ')
		return (1);
	else
		return (0);
}

void	validate_aux(char current_char, int index)
{
	vars()->player->orientation = current_char;
	vars()->player->startx = index;
	vars()->player->starty = vars()->map_height;
}

int	validate_string(char *input_str)
{
	int		index;
	char	current_char;

	index = 0;
	vars()->player->angle = 0;
	while (input_str[index] != '\0')
	{
		current_char = input_str[index];
		if (!is_valid_character(current_char))
			return (1);
		if (current_char == 'N' || current_char == 'S' || \
			current_char == 'E' || current_char == 'W')
		{
			validate_aux(current_char, index);
			current_char = '0';
		}
		if (current_char == ' ')
			current_char = '2';
		vars()->map[vars()->map_height][index] = char_to_int(current_char);
		index++;
	}
	while (index < vars()->map_width)
	{
		vars()->map[vars()->map_height][index] = 2;
		index++;
	}
	return (0);
}
