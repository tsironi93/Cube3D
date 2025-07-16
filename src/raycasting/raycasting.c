/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:04:35 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/16 16:44:14 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

/*
main raycasting function 
casts a single ray per iteration
- loops through each screen column, calculates where ray hits wall (DDA),
   how tall to draw the wall, and draws that vertical line including floor
   and ceiling
*/
void	raycasting(void *param)
{
	t_data	*data;
	int		screen_x;

	data = (t_data *)param;
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
