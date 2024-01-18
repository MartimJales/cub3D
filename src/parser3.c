/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:34:55 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 19:08:15 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	get_width(char *input_str)
{
	int	start_index;
	int	end_index;
	int	width;
	int	i;

	start_index = 0;
	end_index = strlen(input_str) - 1;
	while (start_index <= end_index && input_str[start_index] == ' ')
		start_index++;
	while (end_index >= start_index && input_str[end_index] == ' ')
		end_index--;
	width = 0;
	i = start_index;
	while (i <= end_index)
	{
		width++;
		i++;
	}
	return (width);
}

int	convert_to_int(const char *start, const char *end)
{
	int		length;
	char	number_str[4];

	length = end - start;
	if (length >= 4 || length <= 0)
	{
		printf("Erro: Segmento inválido.\n");
		return (-1);
	}
	ft_strncpy(number_str, start, length);
	number_str[length] = '\0';
	return (atoi(number_str));
}

int	p_string_aux(const char *current_char)
{
	int	value;

	if (*current_char == ',' || *(current_char + 1) == '\0')
	{
		if (*current_char == ',')
			vars()->segment_end = current_char;
		else
			vars()->segment_end = current_char + 1;
		value = convert_to_int(vars()->segment_start, \
vars()->segment_end);
		if (value == -1)
			return (1);
		if (vars()->segment_count == 0)
			vars()->red = value;
		else if (vars()->segment_count == 1)
			vars()->green = value;
		else if (vars()->segment_count == 2)
			vars()->blue = value;
		vars()->segment_start = current_char + 1;
		vars()->segment_count++;
	}
	return (0);
}

int	process_string(char *str)
{
	const char	*current_char;

	init_colors(str + 2);
	current_char = str + 2;
	while (*current_char != '\0')
	{
		p_string_aux(current_char);
		current_char++;
	}
	if (vars()->segment_count != 3)
	{
		free(str);
		exit_program(printf("Erro: Número incorreto de segmentos.\n"));
	}
	return (gen_trgb(255, vars()->red, vars()->green, vars()->blue));
}

int	check_format(const char *nome_arquivo)
{
	const char	*extensao;

	extensao = ft_strrchr(nome_arquivo, '.');
	if (extensao != NULL)
	{
		if (ft_strcmp(extensao, ".cub") == 0)
			return (1);
	}
	return (0);
}
