/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/15 17:32:45 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// Exit the program as failure.
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_data *data = param;

	for (uint32_t i = 0; i < 200; ++i)
	{
		for (uint32_t y = 0; y < 200; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(data->image, i, y, color);
		}
	}
}

void ft_hook_keys(void* param)
{
	t_data *data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	 	mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->image->instances[0].y -= 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->image->instances[0].y += 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->image->instances[0].x -= 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->image->instances[0].x += 40;
}



// Print the window width and height.
static void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int32_t	main(void)
{
	t_data data;

	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_FULLSCREEN, true);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!data.mlx)
		ft_error();
	/* Do stuff */
	// Create and display the image.
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.image || (mlx_image_to_window(data.mlx, data.image, 0, 0) < 0))
		ft_error();
	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(data.image, 0, 0, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!	
	mlx_loop_hook(data.mlx, ft_randomize, &data);
	mlx_loop_hook(data.mlx, ft_hook_keys, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
