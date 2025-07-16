/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:50:07 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/16 12:21:02 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

bool	is_all_num_string(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
		{
			if (data->textures->floor_color)
			{
				i = -1;
				while (data->textures->floor_color[++i])
					free(data->textures->floor_color[i]);
				free(data->textures->floor_color);
			}
			ft_error(data, "Invalid ceiling or floor color format", false);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	flood_check(t_data *data, char **map, int y, int x)
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

char	**clone_map(t_data *data, char **map)
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

void	find_player_pos(t_data *data, char **map)
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
