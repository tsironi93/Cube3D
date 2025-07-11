/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:35:16 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/26 23:02:15 by pdrettas         ###   ########.fr       */
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
