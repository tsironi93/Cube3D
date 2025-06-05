/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/05 20:55:53 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// NOTES:
// seperate variables for x and y?
//   playerpos0 -> x (player_pos.x) / player_pos_X
//   playerpos1 -> y (player_pos.y) / player_pos_Y

//  initial player setup (dir, plane, pos) at game start 
// (PLAYER FACES NORTH)
// initialization (all others run in a per-ray, per-frame sense)
void	setup_player(t_data *data, t_vector *vec)
{
	// starting position of player (X,Y)
	// which box of the map we're in
	vec->grid_map_x = data->player_pos[0];
	vec->grid_map_y = data->player_pos[1];
	
	// initial direction vector (X,Y)
	vec->dir_x = 0;
	vec->dir_y = -1;

	// camera FOV plane (X,Y)
	vec->plane_x = 0.66;
	vec->plane_y = 0;
}

// setup/calculate ray position and direction for each column at every frame
// creates a set of rays fanning out 
//    from the player's position to simulate the 3D perspective.
// -> cast a ray for every pixel of the screens width
// initializing part of ray struct
void	calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec, int screen_x)
{
	// int screen_x; // moves across horizontally

	// screen_x = 0;
	// while (screen_x < data->width)
	// {
	ray->camera_x = 2 * screen_x / data->width - 1;
	ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
	ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
		// screen_x++;
	// }
	// 	* derived from pythagoras theorem
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

// check rays for horizontal line X
// check rays for vertical line Y
// deltaDistX: distance ray has to travel from 1 x-side to the next x-side, 
// deltaDistY: from 1 y-side to the next y-side.
// to travel to cross one full tile along the grid 
// -> makes sure to always step forward in distance 
// initializing part of ray struct
// setup grid stepping distances at per-ray (per column)
// fabs: returns absolute value of a double
// void	draw_rays_3d(t_ray *ray)
// {
// 	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
// 	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
// }


//  *calculate step and initial sideDist*
// calculate side_dist_x & y
// -> distance to next vertical/horizontal gridline
// calculate stepx, stepy (either +1 or -1)
// -> which direction ray is stepping in grid
/*
1. Setting the step direction (left/right or up/down).
2. Calculating how far the ray has to travel to hit 
the first vertical or horizontal grid line.
*/
void prepare_dda(t_data *data, t_ray *ray, t_vector *vec)
{
	// case 1 X-direction: ray going left
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
	  	ray->side_dist_x = (data->player_pos[0] - vec->grid_map_x) * ray->delta_dist_x;
	}
	// case 2 X-direction: ray going right
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (vec->grid_map_x + 1.0 - data->player_pos[0]) * ray->delta_dist_x;
	}
	// case 3 Y-direction: ray going up
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player_pos[1] - vec->grid_map_y) * ray->delta_dist_y;
	}
	// case 4 Y-direction: ray going down
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (vec->grid_map_y + 1.0 - data->player_pos[1]) * ray->delta_dist_y;
	}
}

// DDA algo starts
/*
variables
-hit: determines whether or not loop may be ended 
-side: contains if an x-side or y-side (borders btw two squares) of a wall was hit
		-> set to 0, if x-side hit
		-> set to 1, if y-side ht
*/
void run_dda_algorithm(t_ray *ray, t_vector *vec)
{
	bool hit;
	int side;

	hit = false; // no hit (0)
	while (hit == false)
	{
		// goes to next map grid (x-direction or y-direction)
		if (ray->side_dist_x < ray->side_dist_y)
        {
			ray->side_dist_x += ray->delta_dist_x;
          	vec->grid_map_x += ray->step_x;
          	side = 0;
        }
        else
        {
			ray->side_dist_y += ray->delta_dist_y;
          	vec->grid_map_y += ray->step_y;
          	side = 1;
        }
		// TODO: check whether or not the ray has hit a wall		
	}
}


// put this in a loop within the ft
// gameloop starts (raycast inside)
void	raycasting(t_data *data, t_vector *vec)
{
	t_ray ray;
	int screen_x; // moves across horizontally

	screen_x = 0;
	while (screen_x < data->width)
	{
		// init structs (vec & ray)
		calc_ray_pos_dir(data, &ray, vec, screen_x);
		// draw_rays_3d(&ray);
		prepare_dda(data, &ray, vec);
		// TODO: DDA loop to find wall
		run_dda_algorithm(&ray, vec);
		// TODO: calculate wall height (camera plan vector)
		// TODO: draw vertical line (image scaling & transformation for MLX)
		screen_x++;
	}
}
