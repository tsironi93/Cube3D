/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:16:57 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/16 15:19:04 by itsiros          ###   ########.fr       */
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
}	t_wall_side;

typedef struct s_vector
{
	int		grid_map_x; // which box/grid of the map player is currently in
	int		grid_map_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_vector;

// all variables needed for each ray to cast from the player’s view.
// TODO: rename all variables for readability
typedef struct s_ray
{
    // for ray position & direction
	double	camera_x; // camera space
	double	ray_dir_x;
	double	ray_dir_y;
	//	length of ray from current position to next x or y-side / tile edge
	double	side_dist_x; // how far to the next vertical line (like walking east/west)
	double	side_dist_y; // how far to the next horizontal line (like walking north/south).
	//	length of ray from one x or y-side to next x or y-side
	double	delta_dist_x; // dist_next_xgrid TODO: rename later
	double	delta_dist_y; // dist_next_ygrid
	//	which direction ray is stepping in grid (either +1 or -1)
	int		step_x;
	int		step_y;
	//	if NS (y-side, to 1) or EW (x-side, to 0) wall was hit
	int		wall_side;
	double	dist_camvec_wall;
}	t_ray;

typedef struct s_line
{
	int	x;       // screen x coordinate
	int	y;       // current y position in draw loop
	int	y0;      // starting y position for drawing
	int	y1;      // ending y position for drawing
	int	tex_x;   // texture x coordinate
	int	tex_y;   // texture y coordinate
}	t_line;

//==================================RAYCASTING==================================

// void    setup_player(t_data *data);
// void    raycasting(t_data *data);

#endif
