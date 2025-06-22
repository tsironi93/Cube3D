/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:07:20 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/22 14:56:11 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/raycasting.h"

static void	set_player_north(t_vector *vec);
static void	set_player_south(t_vector *vec);
static void	set_player_east(t_vector *vec);
static void	set_player_west(t_vector *vec);

/*
initial player setup for game start.
includes position of player in the map, and the direction he is facing.
direction vector: where player looks (left, right, ...)
camera plane vector: field of view
*/
void	setup_player(t_data *data, t_vector *vec)
{
	char	direction;

	vec->grid_map_x = (int)data->player->player_pos_x;
	vec->grid_map_y = (int)data->player->player_pos_y;

	direction = data->map[vec->grid_map_x][vec->grid_map_y];
	if (direction == 'N')
		set_player_north(vec);
	else if (direction == 'S')
		set_player_south(vec);
	else if (direction == 'E')
		set_player_east(vec);
	else if (direction == 'W')
		set_player_west(vec);
}

static void	set_player_north(t_vector *vec)
{
	vec->dir_x = 0;
	vec->dir_y = -1;
	vec->plane_x = 0.66;
	vec->plane_y = 0;
}

static void	set_player_south(t_vector *vec)
{
	vec->dir_x = 0;
	vec->dir_y = 1;
	vec->plane_x = -0.66;
	vec->plane_y = 0;
}

static void	set_player_east(t_vector *vec)
{
	vec->dir_x = 1;
	vec->dir_y = 0;
	vec->plane_x = 0;
	vec->plane_y = 0.66;
}

static void	set_player_west(t_vector *vec)
{
	vec->dir_x = -1;
	vec->dir_y = 0;
	vec->plane_x = 0;
	vec->plane_y = -0.66;
}
