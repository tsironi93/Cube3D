/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:59:12 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/20 16:11:03 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	texture_and_colors(t_data *data, char *line, t_map_data ref)
{
	while (ft_isspace(*line))
		line++;
	line = ft_strtrim(line, "\n");
	if (ref == NORTH_TEXTURE)
	{
		data->textures->north_texture = gc_strdup(&data->gc, line);
		printf("line : %ds., line: %s\n", (int)ft_strlen(line), line);
	}
	else if (ref == SOUTH_TEXTURE)
		data->textures->south_texture = gc_strdup(&data->gc, line);
	else if (ref == WEST_TEXTURE)
		data->textures->west_texture = gc_strdup(&data->gc, line);
	else if (ref == EAST_TEXTURE)
		data->textures->east_texture = gc_strdup(&data->gc, line);
	else if (ref == FLOOR_COLOR)
		data->textures->floor_color = ft_split(line, ',');
	else if (ref == CEILING_COLOR)
		data->textures->ceiling_color = ft_split(line, ',');
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
				return (printf(BOLD YELLOW "\n Error found in :%s line %d\n", map[i], i), false);
		}
	}
	printf (BOLD YELLOW "Syntax validation succeeded!!\n" RESET);
	return (true);
}

static void	fetch_map(t_data *data, char *line, char ***map)
{
	static char		*map_buffer[1024];
	static int		i;
	int				j;
	char			*new_line;
	static size_t	max_len;

	j = -1;
	if ((!line && i == 0) || i < 0)
		return ;
	if (!line && i != 0)
	{
		*map = gc_malloc(&data->gc, (i + 1) * sizeof(char *));
		while (++j < i)
		{
			(*map)[j] = gc_malloc(&data->gc, max_len + 1);
			ft_memset((*map)[j], ' ', max_len);
			ft_memcpy((*map)[j], map_buffer[j], ft_strlen(map_buffer[j]));
			(*map)[j][max_len] = '\0';
		}
		(*map)[j] = NULL;
		data->map_height = i;
		i = -1;
	}
	else
	{
		new_line = ft_strtrim(line, "\n");
		if (max_len < ft_strlen(new_line))
			max_len = ft_strlen(new_line);
		map_buffer[i++] = new_line;
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
			continue ;
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
		else
			fetch_map(data, line, &data->map);
	}
}

static void	find_player_pos(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W'
				|| map[i][j] == 'S')
			{
				data->player_pos[0] = i;
				data->player_pos[1] = j;
				return ;
			}
		}
	}
	ft_error(data, "No Player found in the map", false);
}

static char	**clone_map(t_data *data, char **map)
{
	char	**clone;
	int		i;

	i = 0;
	while (map[i])
		i++;
	clone = gc_malloc(&data->gc, (i + 1) * sizeof(char *));
	i = -1;
	while (map[++i])
		clone[i] = gc_strdup(&data->gc, map[i]);
	clone[i] = NULL;
	return (clone);
}

static bool	flood_check(t_data *data, char **map, int y, int x)
{
	char	tile;

	if (y < 0 || x < 0 || !map[y][x])
	{
		ft_error(data, "Map is not surrounded by walls", false);
		return (false);
	}
	tile = map[y][x];
	if (tile == ' ' || tile == '\0')
		ft_error(data, "Map is not surrounded by walls", false);
	if (tile == '1' || tile == 'F')
		return (true);
	map[y][x] = 'F';
	return (flood_check(data, map, y + 1, x)
		&& flood_check(data, map, y - 1, x)
		&& flood_check(data, map, y, x + 1)
		&& flood_check(data, map, y, x - 1));
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
	if (data->textures->north_texture == NULL
		|| data->textures->south_texture == NULL
		|| data->textures->west_texture == NULL
		|| data->textures->east_texture == NULL
		|| data->textures->floor_color == NULL
		|| data->textures->ceiling_color == NULL)
		ft_error(data, "Init error: Missing textures or colors", false);
	fetch_map(data, NULL, &data->map);
	if (!validate_syntax(data->map))
		ft_error(data, "Wrong characters found in the map", false);
	find_player_pos(data, data->map);
	flood_check(data, clone_map(data, data->map), data->player_pos[0],
		data->player_pos[1]);
	close(fd);
}
