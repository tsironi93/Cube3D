/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:35:16 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/16 13:31:26 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

/*
1. calculates the relative horizontal position of the current screen column (camera_x)
2. calculates the direction of the ray 
		vec->dir_x & vec->dir_y:  direction the player is facing
		vec->plane_x & vec->plane_y: a vector perpendicular to the player direction
									(represents 2D "camera plane" (like FOV)
	to avoid fish-eye effect (instead of calculating with players and wall position)
3. calculates how far the ray has to go along the ray direction to move across a grid line
		delta_dist_x & delta_dist_y
note: essential for DDA step where ray moves through the map grid
note: 1e30 is used to avoid division by 0 when ray goes straight vertically/horizontally
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
calculates the height of the wall line based on how far ray traveled 
and figures out which part of the screen it should be drawn on to create 3D effect. 
1. uses the distance to the wall to compute how high the wall appears (close = tall, far = short)
2. calculates where the wall should start and end vertically
3. clamps to screen bounds
note: mininum distance to prevent division by 0 
*/
void	calc_wall_height(t_data *data, t_ray *ray)
{
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		ray->dist_camvec_wall = ray->side_dist_x - ray->delta_dist_x;
	else if (ray->wall_side == SOUTH || ray->wall_side == NORTH)
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
