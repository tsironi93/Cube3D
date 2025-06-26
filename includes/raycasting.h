/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:16:57 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/26 21:39:17 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef enum s_wall_side
{
	EAST_WEST,
	NORTH_SOUTH,
	NORTH,
	EAST,
	SOUTH,
	WEST
}			t_wall_side;

typedef struct s_vector
{
	int		grid_map_x;
	int		grid_map_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_vector;

// TODO: rename all variables for readability
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		wall_side;
	double	dist_camvec_wall;
	int		wall_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

//==================================RAYCASTING==================================

// void    setup_player(t_data *data);
// void    raycasting(t_data *data);

#endif
