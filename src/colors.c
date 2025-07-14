/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:16 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/13 12:13:38 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_pixel_from_texture(mlx_texture_t *tex, int x, int y)
{
	int	index;

	if (x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF00FFFF);
	index = (y * tex->width + x) * 4;
	return (((uint32_t)tex->pixels[index] << 24)
		| ((uint32_t)tex->pixels[index + 1] << 16)
		| ((uint32_t)tex->pixels[index + 2] << 8)
		| ((uint32_t)tex->pixels[index + 3]));
}
