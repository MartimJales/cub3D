/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:04:27 by mjales            #+#    #+#             */
/*   Updated: 2023/12/20 19:36:39 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	char_to_int(char chr)
{
	return (chr - '0');
}

int	check_string(char	*input_str)
{
	int	start_index;
	int	end_index;

	end_index = strlen(input_str) - 1;
	start_index = 0;
	while (input_str[start_index] == ' ')
		start_index++;
	while (end_index >= 0 && input_str[end_index] == ' ')
		end_index--;
	if (input_str[start_index] == '1' && input_str[end_index] == '1')
		return (0);
	else
		return (1);
}

int	validate_string(char	*input_str)
{
	int		index;
	char	current_char;

	index = 0;
	while (input_str[index] != '\0')
	{
		current_char = input_str[index];
		if (!(char_to_int(current_char) == 0 || \
char_to_int(current_char) == 1 || \
current_char == 'N' || current_char == 'S' || \
current_char == 'E' || current_char == 'W' || \
current_char == ' '))
			return (1);
		if (current_char == 'N' || current_char == 'S' || \
			current_char == 'E' || current_char == 'W')
		{
			vars()->player->orientation = current_char;
			vars()->player->startx = index;
			vars()->player->starty = vars()->map_height;
			current_char = '0';
		}
		if (current_char == ' ')
			current_char = '0';
		vars()->map[vars()->map_height][index] = char_to_int(current_char);
		index++;
	}
	return (0);
}

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

int	process_string(const char *str)
{
	const char	*current_char;
	int			value;

	vars()->red = 0;
	vars()->green = 0;
	vars()->blue = 0;
	vars()->segment_start = str;
	current_char = str;
	vars()->segment_count = 0;
	while (*current_char != '\0')
	{
		if (*current_char == ',' || *(current_char + 1) == '\0')
		{
			if (*current_char == ',')
				vars()->segment_end = current_char;
			else
				vars()->segment_end = current_char + 1;
			value = convert_to_int(vars()->segment_start, \
vars()->segment_end);
			if (value == -1)
				return (0);
			if (vars()->segment_count == 0)
				vars()->red = value;
			else if (vars()->segment_count == 1)
				vars()->green = value;
			else if (vars()->segment_count == 2)
				vars()->blue = value;
			vars()->segment_start = current_char + 1;
			vars()->segment_count++;
		}
		current_char++;
	}
	if (vars()->segment_count != 3)
	{
		printf("Erro: Número incorreto de segmentos.\n");
		return (0);
	}
	return (gen_trgb(255, vars()->red, vars()->green, vars()->blue));
}

char	*ft_strrchr(const char *str, int c)
{
	char	*ultima_ocorrencia;

	ultima_ocorrencia = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			ultima_ocorrencia = (char *)str;
		str++;
	}
	return (ultima_ocorrencia);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;

	buffer = malloc(100000);
	i = 0;
	while ((rd = read(fd, &character, 1)) > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break ;
	}
	buffer[i - 1] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
		return (free(buffer), NULL);
	return (buffer);
}

void	parseline(char *line)
{
	if (*line == '\n')
		return ;
	else if (!ft_strncmp(line, "NO", 2))
		img_teste(&vars()->no, line + 3);
	else if (!ft_strncmp(line, "SO", 2))
		img_teste(&vars()->so, line + 3);
	else if (!ft_strncmp(line, "WE", 2))
		img_teste(&vars()->we, line + 3);
	else if (!ft_strncmp(line, "EA", 2))
		img_teste(&vars()->ea, line + 3);
	else if (!ft_strncmp(line, "F", 1))
		vars()->fcolor = process_string(line + 2);
	else if (!ft_strncmp(line, "C", 1))
		vars()->ccolor = process_string(line + 2);
	else if (!(validate_string(line)) && !(check_string(line)))
	{
		vars()->map_height++;
		if (get_width(line) > vars()->map_width)
			vars()->map_width = get_width(line);
	}
}

void	parser(char *filename)
{
	t_img	tmp;
	char	*line;
	int		fd;

	vars()->map_width = 0;
	vars()->map_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		parseline(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	tmp = new_img(SCREENWIDTH, (int)SCREENHEIGHT / 3, *vars()->win);
	vars()->ceil_img = tmp;
	tmp = new_img(SCREENWIDTH, (int)2 * SCREENHEIGHT / 3, *vars()->win);
	vars()->floor_img = tmp;
	fill_image(vars()->ceil_img, vars()->ccolor);
	fill_image(vars()->floor_img, vars()->fcolor);
}

void	fill_image(t_img img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img.w)
	{
		j = 0;
		while (j < img.h)
		{
			put_pixel_img(img, i, j, color);
			j++;
		}
		i++;
	}
}
