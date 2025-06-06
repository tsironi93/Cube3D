/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:15:44 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/06 18:16:00 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_randomize(void *param)
{
	t_data	*data;
	int		i;
	int		j;
	int		color;

	data = param;
	i = -1;
	while (++i < 200)
	{
		j = -1;
		while (++j < 200)
		{
			color = ft_pixel(rand() % 255, rand() % 255, rand() % 255,
					rand() % 255);
			mlx_put_pixel(data->image, i, j, color);
		}
	}
}
