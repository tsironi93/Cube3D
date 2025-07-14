/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:39:35 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/12 17:55:07 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_ray(t_data *data)
{
	data->ray = gc_malloc(&data->gc, sizeof(t_ray));
	data->ray->camera_x = 0;
	data->ray->delta_dist_x = 0;
	data->ray->delta_dist_y = 0;
	data->ray->dist_camvec_wall = 0;
	data->ray->ray_dir_x = 0;
	data->ray->ray_dir_y = 0;
	data->ray->side_dist_x = 0;
	data->ray->side_dist_y = 0;
	data->ray->step_x = 0;
	data->ray->step_y = 0;
	data->ray->wall_side = 0;
}

static void	init_vec(t_data *data)
{
	data->vec = gc_malloc(&data->gc, sizeof(t_vector));
	data->vec->dir_x = 0;
	data->vec->dir_y = 0;
	data->vec->grid_map_x = 0;
	data->vec->grid_map_y = 0;
	data->vec->plane_x = 0;
	data->vec->plane_y = 0;
}

void	init_structs(t_data *data)
{
	init_ray(data);
	init_vec(data);
}
