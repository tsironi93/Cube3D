/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/16 10:17:46 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int32_t	main(void)
{
	t_data	data;

	data.width = 2880;
	data.height = 1620;
	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_FULLSCREEN, true);
	data.mlx = mlx_init(data.width, data.height, "Cube3D", true);
	if (!data.mlx)
		ft_error();
	/* Do stuff */
	// Create and display the image.
	data.image = mlx_new_image(data.mlx, data.width, data.height);
	if (!data.image || (mlx_image_to_window(data.mlx, data.image, 0, 0) < 0))
		ft_error();
	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(data.image, 0, 0, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!	
	mlx_loop_hook(data.mlx, ft_randomize, &data);
	mlx_loop_hook(data.mlx, ft_hook_keys, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
