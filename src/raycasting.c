/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/04 15:49:53 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// NOTES:
// seperate variables for x and y?
//   playerpos0 -> x (player_pos.x) / player_pos_X
//   playerpos1 -> y (player_pos.y) / player_pos_Y

// initialization/start (PLAYER FACES NORTH)
void	setup_player(t_data *data, t_vector *vec)
{
	(void) data;
	// starting position of player (X,Y)
	// data->player_pos[0] = //;
	// data->player_pos[1] = //;
	
	// initial direction vector (X,Y)
	vec->dir_x = 0;
	vec->dir_y = -1;

	// camera FOV plane (X,Y)
	vec->plane_x = 0.66;
	vec->plane_y = 0;
}

// calculate ray position and direction
// creates a set of rays fanning out 
//    from the player's position to simulate the 3D perspective.
// -> cast a ray for every pixel of the screens width
void	calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec)
{
	int screen_x; // moves across horizontally

	screen_x = 0;
	while (screen_x < data->width)
	{
		ray->camera_x = 2 * screen_x / data->width - 1;
		ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
		ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
		screen_x++;
	}
}

// check rays for horizontal line X
// check rays for vertical line Y
// deltaDistX: distance ray has to travel from 1 x-side to the next x-side, 
// deltaDistY: from 1 y-side to the next y-side.
// to travel to cross one full tile along the grid
// TODO: declare struct 
void	draw_rays_3d(t_ray *ray)
{


	// * derived from pythagoras theorem
	ray->dist_next_xgrid = abs(1 / ray->ray_dir_x);
	ray->dist_next_xgrid = abs(1 / ray->ray_dir_y);


}

// in gameloop (should be replaced by mlx_loop_hook in main?) -> raycast inside
void	raycasting(t_data *data, t_ray *ray, t_vector *vec)
{
	calc_ray_pos_dir(data, ray, vec);
	draw_rays_3d(ray);

}
