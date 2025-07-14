/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:29:50 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/12 18:34:09 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

void	advance_to_closest_grid_line(t_ray *ray, t_vector *vec);
void	set_step_direction_x(t_data *data, t_ray *ray, t_vector *vec);
void	set_step_direction_y(t_data *data, t_ray *ray, t_vector *vec);

/*
implements the DDA (Digital Differential Analyzer) algorithm 
to find where a ray hits a wall.
continues steppung until hiting a wall or safety limit
- steps through the map grid, one cell at a time, 
  until the ray hits a wall OR goes out of bounds.
Where: Which grid cell contains the wall
Distance: How far the ray traveled (via side_dist values)
Wall Side: Whether it's a north/south or east/west facing wall
TODO: naming of t_vector not vec but more descriptive of a vector
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

void	advance_to_closest_grid_line(t_ray *ray, t_vector *vec)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		vec->grid_map_x += ray->step_x;
		ray->wall_side = EAST_WEST;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		vec->grid_map_y += ray->step_y;
		ray->wall_side = NORTH_SOUTH;
	}
}

/*
1. Setting the step direction (left/right or up/down).
2. Calculating how far the ray has to travel to hit
the first vertical or horizontal grid line.
// resetting grid position for each ray (NEW)
// since DDA algo modifies these values, so have to start fresh for each ray
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
