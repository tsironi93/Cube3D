/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:29:50 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/20 17:38:35 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

/*
implements the DDA (Digital Differential Analyzer) algorithm 
to find where a ray hits a wall.
- steps through the map grid, one cell at a time, 
  until the ray hits a wall or goes out of bounds.
Where: Which grid cell contains the wall
Distance: How far the ray traveled (via side_dist values)
Wall Side: Whether it's a north/south or east/west facing wall
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
		if (!is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data))
		{
			ray_hit_wall = true;
		}
		else if (data->map[vec->grid_map_x][vec->grid_map_y] == '1')
		{
			ray_hit_wall = true;
		}
	}
}
