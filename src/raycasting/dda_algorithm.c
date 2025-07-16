/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:29:50 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/16 13:47:00 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

void	advance_to_closest_grid_line(t_ray *ray, t_vector *vec);
void	set_step_direction_x(t_data *data, t_ray *ray, t_vector *vec);
void	set_step_direction_y(t_data *data, t_ray *ray, t_vector *vec);

/*
runs the DDA loop to walk through the map grid until a wall is hit by the ray.
1. repeatedly steps from one grid square to the next until a wall is hit.
2. chooses x or y step depending on which is closer (side_dist_x/y).
note: max_iterations to prevent infinite loops (steps from one end to the other)
	  ex. 10×10 map would have max_iterations = 20
*/
void	run_dda_algorithm(t_data *data, t_ray *ray, t_vector *vec)
{
	bool	ray_hit_wall;
	int		iterations;
	int		max_iterations;

	max_iterations = data->map_height + data->map_width;
	iterations = 0;
	ray_hit_wall = false;
	while (ray_hit_wall == false && iterations < max_iterations)
	{
		iterations++;
		advance_to_closest_grid_line(ray, vec);
		if (!is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data))
			ray_hit_wall = true;
		else if (data->map[vec->grid_map_x][vec->grid_map_y] == '1')
			ray_hit_wall = true;
	}
}

/*
moves the ray one step forward in the map, 
choosing the closest grid edge (x or y) and records the wall direction.
1. moves in x or y direction, whichever is closer
2. updates side_dist for next step
3. sets which wall was hit (N/S/E/W)
*/
void	advance_to_closest_grid_line(t_ray *ray, t_vector *vec)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		vec->grid_map_x += ray->step_x;
		if (ray->step_x > 0)
			ray->wall_side = EAST;
		else
			ray->wall_side = WEST;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		vec->grid_map_y += ray->step_y;
		if (ray->step_y > 0)
			ray->wall_side = SOUTH;
		else
			ray->wall_side = NORTH;
	}
}

/*
sets up initial values for the grid traversal using DDA, 
based on the ray direction & player position.
1. determines which box/grid the player is in
2. calculates whether the ray goes left/right or up/down (step_x, step_y)
3. prepares the distance to the first grid/wall hit (side_dist_x/y) in helper fts. 
*/
void	prepare_dda(t_data *data, t_ray *ray, t_vector *vec)
{
	vec->grid_map_x = (int)data->player->player_pos_x;
	vec->grid_map_y = (int)data->player->player_pos_y;
	set_step_direction_x(data, ray, vec);
	set_step_direction_y(data, ray, vec);
}

// case 1 X-direction: ray going left
// case 2 X-direction: ray going right
void	set_step_direction_x(t_data *data, t_ray *ray, t_vector *vec)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->player_pos_x - vec->grid_map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (vec->grid_map_x + 1.0 - data->player->player_pos_x)
			* ray->delta_dist_x;
	}
}

// case 3 Y-direction: ray going up
// case 4 Y-direction: ray going down
void	set_step_direction_y(t_data *data, t_ray *ray, t_vector *vec)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->player_pos_y - vec->grid_map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (vec->grid_map_y + 1.0 - data->player->player_pos_y)
			* ray->delta_dist_y;
	}
}
