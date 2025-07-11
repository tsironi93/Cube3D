/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:43:35 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/26 21:44:43 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
save old direction
rotate direction vector
rotate camera plane
*/
void	rotate_player(t_data *data, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->vec->dir_x;
	old_plane_x = data->vec->plane_x;
	data->vec->dir_x = data->vec->dir_x * cos(rotation_speed) - data->vec->dir_y
		* sin(rotation_speed);
	data->vec->dir_y = old_dir_x * sin(rotation_speed) + data->vec->dir_y
		* cos(rotation_speed);
	data->vec->plane_x = data->vec->plane_x * cos(rotation_speed)
		- data->vec->plane_y * sin(rotation_speed);
	data->vec->plane_y = old_plane_x * sin(rotation_speed) + data->vec->plane_y
		* cos(rotation_speed);
}

void	move_player_forward(t_data *data)
{
	float	new_position_x;
	float	new_position_y;

	new_position_x = data->player->player_pos_x - data->vec->dir_x * 0.05;
	new_position_y = data->player->player_pos_y - data->vec->dir_y * 0.05;
	if (!is_wall_collision(data, new_position_x, new_position_y))
	{
		data->player->player_pos_x -= data->vec->dir_x * 0.05;
		data->player->player_pos_y -= data->vec->dir_y * 0.05;
	}
}

void	move_player_backward(t_data *data)
{
	float	new_position_x;
	float	new_position_y;

	new_position_x = data->player->player_pos_x + data->vec->dir_x * 0.05;
	new_position_y = data->player->player_pos_y + data->vec->dir_y * 0.05;
	if (!is_wall_collision(data, new_position_x, new_position_y))
	{
		data->player->player_pos_x += data->vec->dir_x * 0.05;
		data->player->player_pos_y += data->vec->dir_y * 0.05;
	}
}

void	move_player_right(t_data *data)
{
	float	new_position_x;
	float	new_position_y;

	new_position_x = data->player->player_pos_x + data->vec->plane_x * 0.05;
	new_position_y = data->player->player_pos_y + data->vec->plane_y * 0.05;
	if (!is_wall_collision(data, new_position_x, new_position_y))
	{
		data->player->player_pos_x += data->vec->plane_x * 0.05;
		data->player->player_pos_y += data->vec->plane_y * 0.05;
	}
}

void	move_player_left(t_data *data)
{
	float	new_position_x;
	float	new_position_y;

	new_position_x = data->player->player_pos_x - data->vec->plane_x * 0.05;
	new_position_y = data->player->player_pos_y - data->vec->plane_y * 0.05;
	if (!is_wall_collision(data, new_position_x, new_position_y))
	{
		data->player->player_pos_x -= data->vec->plane_x * 0.05;
		data->player->player_pos_y -= data->vec->plane_y * 0.05;
	}
}
