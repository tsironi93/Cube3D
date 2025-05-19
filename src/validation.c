/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:59:12 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/19 12:58:18 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	texture_and_colors(t_data *data, char *line, t_map_data ref)
{
	while (ft_isspace(*line))
		line++;
	line = ft_strtrim(line, "\n");
	printf(BOLD YELLOW);
	if (ref == NORTH_TEXTURE)
	{
		printf("NORTH_TEXTURE\t: %s", line);
		data->north_texture = ft_strdup(line);
	}
	if (ref == SOUTH_TEXTURE)
	{
		printf("SOUTH_TEXTURE\t: %s", line);
		data->south_texture = ft_strdup(line);
	}
	if (ref == WEST_TEXTURE)
	{
		printf("WEST_TEXTURE\t: %s", line);
		data->west_texture = ft_strdup(line);
	}
	if (ref == EAST_TEXTURE)
	{
		printf("EAST_TEXTURE\t: %s", line);
		data->east_texture = ft_strdup(line);
	}
	if (ref == FLOOR_COLOR)
	{
		printf("FLOOR_COLOR\t: %s", line);
		data->floor_color = ft_split(line, ',');
	}
	if (ref == CEILING_COLOR)
	{
		printf("CEILING_COLOR\t: %s", line);
		data->ceiling_color = ft_split(line, ',');
	}
	printf(RESET);
}

static bool	validate_syntax(char *line)
{
	static int	i;

	printf(BOLD GREEN "%s", line);
	if (i == 0)
	{
		while (*line)
		{
			if (*line != '1' && *line != ' ' && *line != '\n')
			{
				printf("ERROR in line :%s at position: '%c'\n", line, *line);
				return (false);
			}
			line++;
		}
	}
	else
	{
		while (*line)
		{
			if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S'
				&& *line != 'E' && *line != 'W' && *line != ' '
				&& *line != '\n')
			{
				printf("ERROR in line :%s\n", line);
				return (false);
			}
			line++;
		}
	}
	i++;
	return (true);
}

static void	fetch_map(char *line, char ***map)
{
	static char	*map_buffer[1024];
	static int	i;
	int			j;
	char		*new_line;

	j = -1;
	if ((!line && i == 0) || i < 0)
		return ;
	if (!line && i != 0)
	{
		*map = malloc((i + 1) * sizeof(char *));
		while (++j < i)
			(*map)[j] = ft_strdup(map_buffer[j]);
		(*map)[j] = NULL;
		i = -1;
	}
	else
	{
		new_line = ft_strtrim(line, "\n");
		map_buffer[i] = new_line;
		i++;
	}
}

static void	validate_file(int fd, t_data *data)
{
	char	*line;

	while (MALAKA)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
		{
			free (line);
			continue ;
		}
		while (ft_isspace(*line))
			line++;
		if (ft_strnstr(line, "NO", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "NO",
					sizeof(line)) + 2, NORTH_TEXTURE);
		else if (ft_strnstr(line, "SO", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "SO",
					sizeof(line)) + 2, SOUTH_TEXTURE);
		else if (ft_strnstr(line, "WE", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "WE",
					sizeof(line)) + 2, WEST_TEXTURE);
		else if (ft_strnstr(line, "EA", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "EA",
					sizeof(line)) + 2, EAST_TEXTURE);
		else if (ft_strnstr(line, "F", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "F",
					sizeof(line)) + 1, FLOOR_COLOR);
		else if (ft_strnstr(line, "C", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "C",
					sizeof(line)) + 1, CEILING_COLOR);
		else
			fetch_map(line, &data->map);
		free(line);
	}
}

void	init_cube(int ac, char **av, t_data *data)
{
	int		fd;

	if (ac != 2)
		ft_error("Init error: The only parameter in Cube3D is a map", false);
	if (ft_strcmp(av[1] + (ft_strlen(av[1]) - 4), ".cub"))
		ft_error("Init error: Invalid map file", false);
	data->gc = gc_new();
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error("Init error: Cant open map or file doesnt exist", false);
	validate_file(fd, data);
	if (!validate_syntax(NULL))
		ft_error("Wrong characters found in the map", false);
	printf (BOLD YELLOW "Syntax validation succeeded!!\n" RESET);
	close(fd);
}
