/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/22 14:52:03 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

// if coordinates are within the map bounds
bool	is_map_coordinates(int x, int y, t_data *data)
{
	if (!(x >= 0 && x < data->map_height))
		return (false);
	if (!(data->map[x] != NULL && y >= 0 && y < (int)ft_strlen(data->map[x])))
		return (false);
	return (true);
}

/*
when walking through wall or ray shoots through wall any other than the first one
*/
bool	inside_of_walls(int x, int y, t_data *data)
{
	if (is_map_coordinates(x, y, data) == false)
		return (false);
	if (data->map[x][y] == '1' || data->map[x][y] == 'F')
		return (true);
	return (false);
}
