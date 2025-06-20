/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:04:35 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/20 17:29:35 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

/*
main raycasting function 
- casts a single ray per iteration
*/
void	raycasting(void *param)
{
	t_data		*data;
	// static bool	debug_printed = false;
	data = (t_data *)param;
	int screen_x;
	// // ***DEBUG FT******
	// if (!debug_printed)
	// {
	// 	debug_map_and_player(data);
	// 	debug_printed = true;
	// }
	// // ***END******
	screen_x = 0;
	while (screen_x < data->width)
	{
		calc_ray_pos_dir(data, data->ray, data->vec, screen_x);
		prepare_dda(data, data->ray, data->vec);
		run_dda_algorithm(data, data->ray, data->vec);
		calc_wall_height(data, data->ray);
		draw_ceiling_floor_wall(data, screen_x);
		screen_x++;
	}
}
