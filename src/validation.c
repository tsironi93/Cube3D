/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:59:12 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/14 16:58:18 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	texture_and_colors(t_data *data, char *line, t_map_data ref)
{
	char	*ptr;

	ptr = line;
	while (ft_isspace(*ptr))
		ptr++;
	ptr = ft_strtrim(ptr, "\n");
	if (ref == NORTH_TEXTURE)
		data->textures->north_texture = gc_strdup(&data->gc, ptr);
	else if (ref == SOUTH_TEXTURE)
		data->textures->south_texture = gc_strdup(&data->gc, ptr);
	else if (ref == WEST_TEXTURE)
		data->textures->west_texture = gc_strdup(&data->gc, ptr);
	else if (ref == EAST_TEXTURE)
		data->textures->east_texture = gc_strdup(&data->gc, ptr);
	else if (ref == FLOOR_COLOR)
		data->textures->floor_color = ft_split(ptr, ',');
	else if (ref == CEILING_COLOR)
		data->textures->ceiling_color = ft_split(ptr, ',');
	free(ptr);
}

static bool	validate_syntax(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
				return (printf(BOLD YELLOW "\n Error found in :%s line %d\n",
						map[i], i), false);
		}
	}
	printf (BOLD YELLOW "Syntax validation succeeded!!\n" RESET);
	return (true);
}

static void	fetch_textures(t_data *data, char *line)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "NO",
				ft_strlen(line)) + 2, NORTH_TEXTURE);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "SO",
				ft_strlen(line)) + 2, SOUTH_TEXTURE);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "WE",
				ft_strlen(line)) + 2, WEST_TEXTURE);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "EA",
				ft_strlen(line)) + 2, EAST_TEXTURE);
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "F",
				ft_strlen(line)) + 1, FLOOR_COLOR);
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		texture_and_colors(data, ft_strnstr(line, "C",
				ft_strlen(line)) + 1, CEILING_COLOR);
}

static void	validate_file(int fd, t_data *data)
{
	char	*line;

	line = NULL;
	while (MALAKA)
	{
		if (line)
			free(line);
		line = get_next_line(fd, data);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
			continue ;
		if (ft_strnstr(line, "NO", ft_strlen(line))
			|| ft_strnstr(line, "SO", ft_strlen(line))
			|| ft_strnstr(line, "WE", ft_strlen(line))
			|| ft_strnstr(line, "EA", ft_strlen(line))
			|| ft_strnstr(line, "C", ft_strlen(line))
			|| ft_strnstr(line, "F", ft_strlen(line)))
			fetch_textures(data, line);
		else
			fetch_map(data, line, &data->map);
	}
}

void	init_cube(int ac, char **av, t_data *data)
{
	int		fd;

	data->gc = gc_new();
	if (ac != 2)
		ft_error(data, "Init error: The only parameter in Cube3D is a map",
			false);
	if (ft_strcmp(av[1] + (ft_strlen(av[1]) - 4), ".cub"))
		ft_error(data, "Init error: Invalid map file", false);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error(data, "Init error: Cant open map or file doesnt exist", false);
	data->textures = gc_malloc(&data->gc, sizeof(t_textures));
	ft_bzero(data->textures, sizeof(t_textures));
	validate_file(fd, data);
	error_checks(data);
	fetch_map(data, NULL, &data->map);
	if (!validate_syntax(data->map))
		ft_error(data, "Wrong characters found in the map", false);
	find_player_pos(data, data->map);
	flood_check(data, clone_map(data, data->map), data->player_pos[0],
		data->player_pos[1]);
	close(fd);
}
