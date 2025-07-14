/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:51:58 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/14 13:06:07 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// if player collides with a wall when trying to move
// bool	is_wall_collision(t_data *data, float position_x, float position_y)
// {
// 	if ((data->map[(int)round(position_x)][(int)round(position_y)] == '1')
// 		|| (data->map[(int)position_x][(int)position_y] == '1'))
// 		return (true);
// 	else
// 		return (false);
// }

bool	is_wall_collision(t_data *data, float position_x, float position_y)
{
	if (data->map[(int)position_x][(int)position_y] == '1')
		return (true);
	return (false);
}

// if coordinates are within the map bounds
bool	is_map_coordinates(int x, int y, t_data *data)
{
	if (!(x >= 0 && x < data->map_height))
		return (false);
	if (!(data->map[x] != NULL && y >= 0
			&& y < (int)ft_strlen(data->map[x])))
		return (false);
	return (true);
}

/*
when walking through wall or ray shoots through wall 
any other than the first one
*/
bool	inside_of_walls(int x, int y, t_data *data)
{
	if (is_map_coordinates(x, y, data) == false)
		return (false);
	if (data->map[x][y] == '1' || data->map[x][y] == 'F')
		return (true);
	return (false);
}
