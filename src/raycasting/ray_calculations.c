/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:35:16 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/20 18:12:54 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

/*
setup/calculate ray position and direction for each column at every frame
creates a set of rays fanning out from the player's position to simulate 
the 3D perspective.
-> cast a ray for every pixel of the screens width
deltaDistX: distance ray has to travel from 1 x-side to the next x-side,
deltaDistY: from 1 y-side to the next y-side.
to travel to cross one full tile along the grid
 -> makes sure to always step forward in distance
setup grid stepping distances at per-ray (per column)
fabs: returns absolute value of a double
*/
void	calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec, int screen_x)
{
	ray->camera_x = 2 * screen_x / (double)data->width - 1;

	ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
	ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;

	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

//  *calculate step and initial sideDist*
// calculate side_dist_x & y -> distance to next vertical/horizontal gridline
// calculate stepx, stepy (either +1 or -1)
	//-> which direction ray is stepping in grid
/*
1. Setting the step direction (left/right or up/down).
2. Calculating how far the ray has to travel to hit
the first vertical or horizontal grid line.
// resetting grid position for each ray (NEW)
// since DDA algo modifies these values, so have to start fresh for each ray
// case 1 X-direction: ray going left
// case 2 X-direction: ray going right
// case 3 Y-direction: ray going up
// case 4 Y-direction: ray going down
*/
void	prepare_dda(t_data *data, t_ray *ray, t_vector *vec)
{
	vec->grid_map_x = (int)data->player->player_pos_x;
	vec->grid_map_y = (int)data->player->player_pos_y;
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

/*
- calculate	distance of the ray to the wall
-> to calculate	how high the wall has to be drawn after
- to eliminate fish	eye effect: calc distance from plane to wall,
		NOT player to wall
- dist_camvec_wall: distance btw wall and camera vector
// mininum distance to prevent division by 0 (NEW)
// calculates how tall wall should appear on screen 
(closer walls = larger wall height)
// Calculates where to draw the wall
// Limits to screen bounds
// making sure drawing of line doesnt go off screen
*/
void	calc_wall_height(t_data *data, t_ray *ray)
{
	if (ray->wall_side == EAST_WEST)
		ray->dist_camvec_wall = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->dist_camvec_wall = ray->side_dist_y - ray->delta_dist_y;
	if (ray->dist_camvec_wall < 0.01)
		ray->dist_camvec_wall = 0.01;
	ray->wall_height = (int)data->height / ray->dist_camvec_wall;
	ray->draw_start = (data->height - data->ray->wall_height) / 2;
	ray->draw_end = (data->height + data->ray->wall_height) / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= data->height)
		ray->draw_end = data->height - 1;
}
