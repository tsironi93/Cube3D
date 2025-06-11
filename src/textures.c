/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:07:05 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/11 18:57:19 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/raycasting.h"

// first ft
// void calc_wall_hit_pos(t_data *data)
// {
// 	double	wall_x;
	
// 	wall_x = 0;
// 	if (data->ray->wall_side == WEST || data->ray->wall_side == EAST)
// 	wall_x = data->player_pos[1] + data->ray->dist_camvec_wall * data->ray->ray_dir_y;
// 	else if ((data->ray->wall_side == NORTH || data->ray->wall_side == SOUTH))
// 	wall_x = data->player_pos[0] + data->ray->dist_camvec_wall * data->ray->ray_dir_x;
// 	wall_x = wall_x - floor(wall_x); // start from 0
// 	// printf("wall hit pos = %f\n", wall_x);
// 	// TODO: set line x to the current x coordinate of the screen to draw:
// 	// data->line->x = data->ray
// }

// // paint textures/colors (walls, ceiling/floor) on screen
// // second ft
// // THIS IS FOR TEXTURES
// void paint_textures_colors(t_data *data) // line: bus error 
// {
// 	// paint texture if ray hit wall
// 	if (data->map[data->vec->grid_map_x][data->vec->grid_map_y] == '1')
// 		paint_texture_line();
// 	data->line->y0 = 0;
// 	// data->line->y1 = 
	
// }

// void	paint_line(t_root *root, t_line *line, int rgb) // or paint_texture_line
// {
// 	int	y;
// 	int	y_max;

// 	if (line->y0 < line->y1)
// 	{
// 		y = line->y0;
// 		y_max = line->y1;
// 	}
// 	else
// 	{
// 		y = line->y1;
// 		y_max = line->y0;
// 	}
// 	if (y >= 0)
// 	{
// 		while (y < y_max)
// 		{
// 			pixel_on_img(rgb, line->x, y, root->mlx_img);
// 			// or texture_on_img
// 			y++;
// 		}
// 	}
// }

// main (this one is called in raycasting ft?)
// image scaling and texture rendering
// all this shit is for textures (not drawing rays in 2D)
// void textures(t_data *data) // TODO: rename
// {
// 	calc_wall_hit_pos(data);
// 	paint_textures_colors(data);
// 	paint_line(data);
// }
