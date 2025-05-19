/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:11:03 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/19 13:16:17 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_error(t_data *data, char *error, bool mlx_err)
{
	write(2, BOLD RED, sizeof(BOLD RED) - 1);
	if (error)
		write(2, error, ft_strlen(error));
	if (mlx_err)
		printf("%s", mlx_strerror(mlx_errno));
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
	gc_collect(&data->gc);
	exit(EXIT_FAILURE);
}
